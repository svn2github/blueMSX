/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Eth.c,v $
**
** $Revision: 1.10 $
**
** $Date: 2006-08-31 23:48:10 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
******************************************************************************
*/

#define USE_PACKET32


#include "ArchEth.h"
#include "Win32Eth.h"
#include "Language.h"


#ifdef USE_PACKET32
#else
#define WPCAP
#define HAVE_REMOTE
#include "pcap.h"
#endif
#include "Packet32.h"
#include "NtDDNdis.h"

#include <stdio.h>

#ifndef USE_PACKET32

struct bpf_hdr 
{
	struct timeval	bh_tstamp;	///< The timestamp associated with the captured packet. 
								///< It is stored in a TimeVal structure.
	UINT	bh_caplen;			///< Length of captured portion. The captured portion <b>can be different</b>
								///< from the original packet, because it is possible (with a proper filter)
								///< to instruct the driver to capture only a portion of the packets.
	UINT	bh_datalen;			///< Original length of packet
	USHORT		bh_hdrlen;		///< Length of bpf header (this struct plus alignment padding). In some cases,
								///< a padding could be added between the end of this structure and the packet
								///< data for performance reasons. This filed can be used to retrieve the actual data 
								///< of the packet.
};

static char errbuf[PCAP_ERRBUF_SIZE];

#endif


static LPADAPTER (*pcapPacketOpenAdapter)     (PCHAR);
static VOID      (*pcapPacketCloseAdapter)    (LPADAPTER);
static BOOLEAN   (*pcapPacketSetHwFilter)     (LPADAPTER, ULONG);
static BOOLEAN   (*pcapPacketGetAdapterNames) (PTSTR, PULONG);
static BOOLEAN   (*pcapPacketSendPacket)      (LPADAPTER, LPPACKET, BOOLEAN);
static BOOLEAN   (*pcapPacketReceivePacket)   (LPADAPTER, LPPACKET, BOOLEAN);
static BOOLEAN   (*pcapPacketSetBuff)         (LPADAPTER, int);
static BOOLEAN   (*pcapPacketSetReadTimeout)  (LPADAPTER, int);
static LPPACKET  (*pcapPacketAllocatePacket)  (void);
static VOID      (*pcapPacketInitPacket)      (LPPACKET, PVOID, UINT);
static VOID      (*pcapPacketFreePacket)      (LPPACKET);
static BOOLEAN   (*pcapPacketGetNetInfoEx)    (PCHAR, npf_if_addr*, PLONG);
static BOOLEAN   (*pcapPacketRequest)         (LPADAPTER, BOOLEAN, PPACKET_OID_DATA);


static UInt8 InvalidMac[] = { 0, 0, 0, 0, 0, 0 };

typedef struct {
    int currIf;
    int ifCount;

#ifdef USE_PACKET32
    ADAPTER* pcapHandle;
    PACKET*  pkSend;
    PACKET*  pkRecv;
    UInt32   packetOffset;
    UInt32   packetLenth;
#else
    pcap_t *pcapHandle;
#endif

    UInt8 defaultMac[6];

    struct {
        UInt8 macAddress[6];
        char  devName[512];
        char  description[128];
    } devList[32];
} EthIf;

static EthIf ethIf;

static int parseMac(UInt8* macAddr, char* macStr) {
    int m[6];
    int i;

    if (sscanf(macStr, "%x:%x:%x:%x:%x:%x", m+0,m+1,m+2,m+3,m+4,m+5) != 6) {
        memset(macAddr, 0, 6);
        return 0;
    }

    for (i = 0; i < 6; i++) {
        if (m[i] < 0 || m[i] > 255) {
            memset(macAddr, 0, 6);
            return 0;
        }
        macAddr[i] = (UInt8)m[i];
    }

    return 1;
}


static char* iptos(UInt32 address)
{
	static char buffer[32];
    UInt8* p = (UInt8*)&address;

	sprintf(buffer, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);

	return buffer;
}

static char* mactos(UInt8* mac)
{
	static char buffer[32];

    sprintf(buffer, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	return buffer;
}

static int getMacAddress(char* devName, UInt8* macAddress)
{
    int rv = 0;

    LPADAPTER lpAdapter = pcapPacketOpenAdapter(devName);
    if (lpAdapter) {
        UInt8 data[128];
        PACKET_OID_DATA* oidData = (PACKET_OID_DATA*)data;
        oidData->Oid = OID_802_3_CURRENT_ADDRESS;
        oidData->Length = 6;
        if (pcapPacketRequest(lpAdapter, 0, oidData)) {
            memcpy(macAddress, oidData->Data, 6);
            rv = 1;
        }
        pcapPacketCloseAdapter(lpAdapter);
    }

    return rv;
}

static int getIpAddress(char* devName)
{
	npf_if_addr addrBuf[16];
    Int32 addrSize = 16;
    
    if (!pcapPacketGetNetInfoEx(devName, addrBuf, &addrSize)) {
        return 0;
    }

    while (addrSize--) {
        struct sockaddr* addr = (struct sockaddr *)&addrBuf[addrSize].IPAddress;

        if (addr->sa_family == AF_INET) {
            return ((struct sockaddr_in*)addr)->sin_addr.s_addr;
        }
    }
    return 0;
}

void ethIfCleanup(Properties* properties)
{
    properties->ports.Eth.ethIndex = ethIf.currIf;
}

int  ethIfGetCount()
{
    return ethIf.ifCount;
}

int ethIfIsActive(int index)
{
    return index == ethIf.currIf;
}

char* ethIfGetName(int index)
{
    if (index < ethIf.ifCount) {
        return ethIf.devList[index].description;
    }

    return langTextUnknown();
}

void ethIfSetActive(int index)
{
    ethIf.currIf = index;

    if (ethIf.currIf > ethIf.ifCount) {
        ethIf.currIf = 0;
    }
}

void archEthGetMacAddress(UInt8* macAddr) 
{ 
    if (memcmp(ethIf.defaultMac, InvalidMac, 6) != 0) {
        memcpy(macAddr, ethIf.defaultMac, 6);
    }
    else {
        memcpy(macAddr, ethIf.devList[ethIf.currIf].macAddress, 6);
    }
    macAddr[1] ^= 0xd8;

    printf("MAC: %s\n", mactos(macAddr));
}

#ifdef USE_PACKET32

static int loadPacketLibrary()
{
     
    HINSTANCE hPacket = LoadLibrary("PACKET.DLL");
    if (hPacket == NULL) {
        return 0;
    }
    pcapPacketOpenAdapter     = (LPADAPTER (*)(PCHAR))                               GetProcAddress(hPacket, "PacketOpenAdapter");
    pcapPacketCloseAdapter    = (VOID      (*)(LPADAPTER))                           GetProcAddress(hPacket, "PacketCloseAdapter");
    pcapPacketSetHwFilter     = (BOOLEAN   (*)(LPADAPTER, ULONG))                    GetProcAddress(hPacket, "PacketSetHwFilter");
    pcapPacketGetAdapterNames = (BOOLEAN   (*)(PTSTR, PULONG))                       GetProcAddress(hPacket, "PacketGetAdapterNames");
    pcapPacketSendPacket      = (BOOLEAN   (*)(LPADAPTER, LPPACKET, BOOLEAN))        GetProcAddress(hPacket, "PacketSendPacket");
    pcapPacketReceivePacket   = (BOOLEAN   (*)(LPADAPTER, LPPACKET, BOOLEAN))        GetProcAddress(hPacket, "PacketReceivePacket");
    pcapPacketSetBuff         = (BOOLEAN   (*)(LPADAPTER, int))                      GetProcAddress(hPacket, "PacketSetBuff");
    pcapPacketSetReadTimeout  = (BOOLEAN   (*)(LPADAPTER, int))                      GetProcAddress(hPacket, "PacketSetReadTimeout");
    pcapPacketAllocatePacket  = (LPPACKET  (*)(void))                                GetProcAddress(hPacket, "PacketAllocatePacket");
    pcapPacketInitPacket      = (VOID      (*)(LPPACKET, PVOID, UINT))               GetProcAddress(hPacket, "PacketInitPacket");
    pcapPacketFreePacket      = (VOID      (*)(LPPACKET))                            GetProcAddress(hPacket, "PacketFreePacket");
    pcapPacketGetNetInfoEx    = (BOOLEAN   (*)(PCHAR, npf_if_addr*, PLONG))          GetProcAddress(hPacket, "PacketGetNetInfoEx");
    pcapPacketRequest         = (BOOLEAN   (*)(LPADAPTER, BOOLEAN, PPACKET_OID_DATA))GetProcAddress(hPacket, "PacketRequest");

    return pcapPacketOpenAdapter     != NULL &&
           pcapPacketCloseAdapter    != NULL &&
           pcapPacketSetHwFilter     != NULL &&
           pcapPacketGetAdapterNames != NULL &&
           pcapPacketSendPacket      != NULL &&
           pcapPacketReceivePacket   != NULL &&
           pcapPacketSetBuff         != NULL &&
           pcapPacketSetReadTimeout  != NULL &&
           pcapPacketAllocatePacket  != NULL &&
           pcapPacketInitPacket      != NULL &&
           pcapPacketFreePacket      != NULL &&
           pcapPacketGetNetInfoEx    != NULL &&
           pcapPacketRequest         != NULL;
}

void ethIfInitialize(Properties* properties)
{
    UInt32 nameLen;

    ethIf.ifCount = 1;

    strcpy(ethIf.devList[0].description, langTextNone());
    memcpy(ethIf.devList[0].macAddress, InvalidMac, 6);

    if (loadPacketLibrary()) {
	    pcapPacketGetAdapterNames(NULL, &nameLen);
        if (nameLen > 0) {
            char* nameStr = malloc(nameLen);

	        if (pcapPacketGetAdapterNames(nameStr, &nameLen)) {
                char* devName;

                for (devName = nameStr; *devName; devName += strlen(devName) + 1) {
                    if (!getMacAddress(devName, ethIf.devList[ethIf.ifCount].macAddress)) {
                        continue;
                    }

                    sprintf(ethIf.devList[ethIf.ifCount].description, "[%s]  - %s",
                            mactos(ethIf.devList[ethIf.ifCount].macAddress), iptos(getIpAddress(devName)));
                    strcpy(ethIf.devList[ethIf.ifCount].devName, devName);

                    if (++ethIf.ifCount == 32) {
                        break;
                    }
                }
            }
            free(nameStr);
        }
    }

    ethIf.currIf = properties->ports.Eth.ethIndex;
    if (ethIf.currIf >= ethIf.ifCount) {
        ethIf.currIf = 0;
    }

    parseMac(ethIf.defaultMac, properties->ports.Eth.macAddress);
}

void archEthCreate() 
{
    if (ethIf.currIf == 0) {
        return;
    }

    ethIf.pcapHandle = pcapPacketOpenAdapter(ethIf.devList[ethIf.currIf].devName);
    if (ethIf.pcapHandle != NULL) {
        pcapPacketSetHwFilter(ethIf.pcapHandle, NDIS_PACKET_TYPE_PROMISCUOUS);
        pcapPacketSetBuff(ethIf.pcapHandle, 128000);
        pcapPacketSetReadTimeout(ethIf.pcapHandle, -1);

        ethIf.pkSend = pcapPacketAllocatePacket();
        ethIf.pkRecv = pcapPacketAllocatePacket();

        if (ethIf.pkSend == NULL || ethIf.pkRecv == NULL) {
            archEthDestroy();
        }
    }
}

void archEthDestroy() 
{
    if (ethIf.pcapHandle == NULL) {
        return;
    }

    if (ethIf.pkSend) {
        pcapPacketFreePacket(ethIf.pkSend);
    }
    if (ethIf.pkRecv) {
        pcapPacketFreePacket(ethIf.pkRecv);
    }

    pcapPacketCloseAdapter(ethIf.pcapHandle);

    ethIf.pcapHandle = NULL;
}

int archEthSendPacket(UInt8* buffer, UInt32 length) 
{
    if (ethIf.pcapHandle == NULL) {
        return 0;
    }

    pcapPacketInitPacket(ethIf.pkSend, (char*)buffer, length);
    return pcapPacketSendPacket(ethIf.pcapHandle, ethIf.pkSend, TRUE) != 0;
}

int archEthRecvPacket(UInt8** buffer, UInt32* length) 
{
    static UInt8 buf[65536];

    if (ethIf.pcapHandle == NULL) {
        return 0;
    }

    if (ethIf.packetOffset >= ethIf.packetLenth) {
        ethIf.packetOffset = 0;
        ethIf.packetLenth = 0;

        pcapPacketInitPacket(ethIf.pkRecv, (char*)buf, sizeof(buf));
        if (pcapPacketReceivePacket(ethIf.pcapHandle, ethIf.pkRecv, TRUE)) {
            ethIf.packetLenth = ethIf.pkRecv->ulBytesReceived;
        }
    }

    if (ethIf.packetOffset < ethIf.packetLenth) {
        UInt8* packetStart = (UInt8*)ethIf.pkRecv->Buffer + ethIf.packetOffset;
        struct bpf_hdr* hdr = (struct bpf_hdr*)packetStart;
        *buffer = packetStart + hdr->bh_hdrlen;
        *length = hdr->bh_caplen;
        ethIf.packetOffset += Packet_WORDALIGN(hdr->bh_hdrlen + hdr->bh_caplen);
        return 1;
    }

    return 0;
}

#else

void ethIfInitialize(Properties* properties)
{
    pcap_if_t *alldevs;

    ethIf.ifCount = 1;

    strcpy(ethIf.devList[0].description, langTextNone());
    memcpy(ethIf.devList[0].macAddress, InvalidMac, 6);

    if (pcap_findalldevs(&alldevs, errbuf) != -1) {
        pcap_if_t *dev;

        for (dev = alldevs; dev != NULL; dev = dev->next) {
            UInt32 ipAddress = 0;
            pcap_addr_t* a;

            if (!getMacAddress(dev->name, ethIf.devList[ethIf.ifCount].macAddress)) {
                continue;
            }

            for (a = dev->addresses; a != NULL && ipAddress == 0; a = a->next) {
                if (a->addr->sa_family == AF_INET) {
                    ipAddress = ((struct sockaddr_in*)a->addr)->sin_addr.s_addr;
                }
            }

            sprintf(ethIf.devList[ethIf.ifCount].description, "[%s]  - %s",
                    mactos(ethIf.devList[ethIf.ifCount].macAddress), iptos(ipAddress));
            strcpy(ethIf.devList[ethIf.ifCount].devName, dev->name);

            if (++ethIf.ifCount == 32) {
                break;
            }
        }
        pcap_freealldevs(alldevs);
    }

    ethIf.currIf = properties->ports.Eth.ethIndex;
    if (ethIf.currIf >= ethIf.ifCount) {
        ethIf.currIf = 0;
    }

    parseMac(ethIf.defaultMac, properties->ports.Eth.macAddress);
}

void archEthCreate() 
{
    if (ethIf.currIf == 0) {
        return;
    }

    ethIf.pcapHandle = pcap_open_live(ethIf.devList[ethIf.currIf].devName, 65536, 
                                        PCAP_OPENFLAG_PROMISCUOUS, 0, errbuf);
    if (ethIf.pcapHandle != NULL) {
        pcap_setnonblock(ethIf.pcapHandle, 1, errbuf);
    }
}

void archEthDestroy() 
{
    if (ethIf.pcapHandle == NULL) {
        return;
    }

    pcap_close(ethIf.pcapHandle);

    ethIf.pcapHandle = NULL;
}

int archEthSendPacket(UInt8* buffer, UInt32 length) 
{
    if (ethIf.pcapHandle == NULL) {
        return 0;
    }

    return pcap_sendpacket(ethIf.pcapHandle, buffer, length) == 0;
}

int archEthRecvPacket(UInt8** buffer, UInt32* length) 
{
    static UInt8 buf[65536];
    struct pcap_pkthdr* header;

    if (ethIf.pcapHandle == NULL) {
        return 0;
    }

    if (pcap_next_ex(ethIf.pcapHandle, &header, buffer) > 0) {
        *length = header->len;
        return 1;
    }

    return 0;
}

#endif

