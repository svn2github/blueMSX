/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Eth.c,v $
**
** $Revision: 1.9 $
**
** $Date: 2006-08-31 19:51:27 $
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
#include "ArchEth.h"
#include "Win32Eth.h"
#include "Language.h"

#define WPCAP
#define HAVE_REMOTE
#include "pcap.h"
#include "Packet32.h"
#include "NtDDNdis.h"

#include <stdio.h>

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

static UInt8 InvalidMac[] = { 0, 0, 0, 0, 0, 0 };

#define USE_PACKET32

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

    LPADAPTER lpAdapter = PacketOpenAdapter(devName);
    if (lpAdapter) {
        UInt8 data[128];
        PACKET_OID_DATA* oidData = (PACKET_OID_DATA*)data;
        oidData->Oid = OID_802_3_CURRENT_ADDRESS;
        oidData->Length = 6;
        if (PacketRequest(lpAdapter, 0, oidData)) {
            memcpy(macAddress, oidData->Data, 6);
            rv = 1;
        }
        PacketCloseAdapter(lpAdapter);
    }

    return rv;
}

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


void archEthCreate() 
{
    if (ethIf.currIf == 0) {
        return;
    }

#ifdef USE_PACKET32
    ethIf.pcapHandle = PacketOpenAdapter(ethIf.devList[ethIf.currIf].devName);
    if (ethIf.pcapHandle != NULL) {
        PacketSetHwFilter(ethIf.pcapHandle, NDIS_PACKET_TYPE_PROMISCUOUS);
        PacketSetBuff(ethIf.pcapHandle, 128000);
        PacketSetReadTimeout(ethIf.pcapHandle, -1);

        ethIf.pkSend = PacketAllocatePacket();
        ethIf.pkRecv = PacketAllocatePacket();

        if (ethIf.pkSend == NULL || ethIf.pkRecv == NULL) {
            archEthDestroy();
        }
    }
#else
    ethIf.pcapHandle = pcap_open_live(ethIf.devList[ethIf.currIf].devName, 65536, 
                                        PCAP_OPENFLAG_PROMISCUOUS, 0, errbuf);
    if (ethIf.pcapHandle != NULL) {
        pcap_setnonblock(ethIf.pcapHandle, 1, errbuf);
    }
#endif
}

void archEthDestroy() 
{
    if (ethIf.pcapHandle == NULL) {
        return;
    }

#ifdef USE_PACKET32
    if (ethIf.pkSend) {
        PacketFreePacket(ethIf.pkSend);
    }
    if (ethIf.pkRecv) {
        PacketFreePacket(ethIf.pkRecv);
    }

    PacketCloseAdapter(ethIf.pcapHandle);
#else
    pcap_close(ethIf.pcapHandle);
#endif

    ethIf.pcapHandle = NULL;
}

int archEthSendPacket(UInt8* buffer, UInt32 length) 
{
    if (ethIf.pcapHandle == NULL) {
        return 0;
    }

#ifdef USE_PACKET32
    PacketInitPacket(ethIf.pkSend, (char*)buffer, length);
    return PacketSendPacket(ethIf.pcapHandle, ethIf.pkSend, TRUE) != 0;

#else
    return pcap_sendpacket(ethIf.pcapHandle, buffer, length) == 0;
#endif
}

int archEthRecvPacket(UInt8** buffer, UInt32* length) 
{
    static UInt8 buf[65536];
    struct pcap_pkthdr* header;

    if (ethIf.pcapHandle == NULL) {
        return 0;
    }

#ifdef USE_PACKET32
    if (ethIf.packetOffset >= ethIf.packetLenth) {
        ethIf.packetOffset = 0;
        ethIf.packetLenth = 0;

        PacketInitPacket(ethIf.pkRecv, (char*)buf, sizeof(buf));
        if (PacketReceivePacket(ethIf.pcapHandle, ethIf.pkRecv, TRUE)) {
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
#else
    if (pcap_next_ex(ethIf.pcapHandle, &header, buffer) > 0) {
        *length = header->len;
        return 1;
    }
#endif

    return 0;
}

void archEthGetMacAddress(UInt8* macAddr) 
{ 
    if (memcmp(ethIf.defaultMac, InvalidMac, 6) != 0) {
        memcpy(macAddr, ethIf.defaultMac, 6);
    }
    else {
        memcpy(macAddr, ethIf.devList[ethIf.currIf].macAddress, 6);
    }
//    macAddr[1] ^= 0xd8;

    printf("MAC: %s\n", mactos(macAddr));
}
