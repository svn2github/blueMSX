/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Eth.c,v $
**
** $Revision: 1.8 $
**
** $Date: 2006-08-30 23:39:09 $
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




static char errbuf[PCAP_ERRBUF_SIZE];

static UInt8 InvalidMac[] = { 0, 0, 0, 0, 0, 0 };


typedef struct {
    int currIf;
    int ifCount;

    pcap_t *pcapHandle;

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
            pcap_addr_t* a;

            for (a = dev->addresses; a != NULL; a = a->next) {
                if (a->addr->sa_family == AF_INET) {
                    if (!getMacAddress(dev->name, ethIf.devList[ethIf.ifCount].macAddress)) {
                        continue;
                    }
                    sprintf(ethIf.devList[ethIf.ifCount].description, "%s    [%s]", 
                        iptos(((struct sockaddr_in*)a->addr)->sin_addr.s_addr),
                        mactos(ethIf.devList[ethIf.ifCount].macAddress));
                    strcpy(ethIf.devList[ethIf.ifCount].devName, dev->name);

                    ethIf.ifCount++;
                    break;
                }
            }

            if (ethIf.ifCount == 32) {
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
    if (ethIf.currIf > 0) {
        ethIf.pcapHandle = pcap_open_live(ethIf.devList[ethIf.currIf].devName, 65536, 
                                          PCAP_OPENFLAG_PROMISCUOUS, 0, errbuf);
        if (ethIf.pcapHandle != NULL) {
            pcap_setnonblock(ethIf.pcapHandle, 1, errbuf);
        }
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
    struct pcap_pkthdr* header;

    if (ethIf.pcapHandle == NULL) {
        return 0;
    }

    while(pcap_next_ex(ethIf.pcapHandle, &header, buffer) > 0){
        UInt8 * b = *buffer;
        *length = header->len;
        return 1;
    }
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
}
