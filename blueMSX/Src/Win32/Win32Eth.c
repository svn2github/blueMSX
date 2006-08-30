/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Eth.c,v $
**
** $Revision: 1.5 $
**
** $Date: 2006-08-30 17:30:27 $
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
#include "Properties.h"

#define WPCAP
#define HAVE_REMOTE
#include "pcap.h"

#include <stdio.h>

static char errbuf[PCAP_ERRBUF_SIZE];
static pcap_t *pcapHandle = NULL;
static UInt8 macAddress[6];
static char devName[512];

static UInt8 InvalidMac[] = { 0, 0, 0, 0, 0, 0 };


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

void win32EthGetDevice()
{
    int ethIndex;
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int i = 0;

    // Clear globals
    devName[0] = 0;
    memset(macAddress, 0, sizeof(macAddress));

    // Get config from properties
    ethIndex = propGetGlobalProperties()->ports.Eth.ethIndex;
    parseMac(macAddress, propGetGlobalProperties()->ports.Eth.macAddress);

    printf("Prop Addr = %s\n", propGetGlobalProperties()->ports.Eth.macAddress);
    printf("Mac address %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
        macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);

    if (memcmp(macAddress, InvalidMac, 6) == 0) {
        return;
    }

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        return;
    }
    

    for(d=alldevs; d; d=d->next)
    {
        if (!d->description) {
            continue;
        }

        printf("%d. %s\n", ++i, d->name);
        printf(" (%s)\n", d->description);

        if (ethIndex == i) {
            strcpy(devName, d->name);
            printf("Using device: %s\n", devName);
        }
     }

    pcap_freealldevs(alldevs);
    
    printf("Set MAC Address = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", 
        macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}

void archEthCreate() 
{
    win32EthGetDevice();

    pcapHandle = pcap_open_live(devName, 65536, PCAP_OPENFLAG_PROMISCUOUS, 0, errbuf);
    if (pcapHandle != NULL) {
        pcap_setnonblock(pcapHandle, 1, errbuf);
    }
}

void archEthDestroy() 
{
    if (pcapHandle == NULL) {
        return;
    }

    pcap_close(pcapHandle);

    pcapHandle = NULL;
}

int archEthSendPacket(UInt8* buffer, UInt32 length) {
    int i;
#if 0
    printf("Sending to %.2x:%.2x:%.2x:%.2x:%.2x:%.2x from %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
        buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6],
        buffer[7], buffer[8], buffer[9], buffer[10], buffer[11]);

#if 0
    for (i = 0; i < length; i++) {
        printf("%.2x ", buffer[i]);
        if (i % 16 == 15) printf("\n");
    }
    printf("\n");
#endif
#endif
    if (pcapHandle == NULL) {
        return 0;
    }

    return pcap_sendpacket(pcapHandle, buffer, length) == 0;
}

int archEthRecvPacket(UInt8** buffer, UInt32* length) 
{
    struct pcap_pkthdr* header;

    if (pcapHandle == NULL) {
        return 0;
    }

    while(pcap_next_ex(pcapHandle, &header, buffer) > 0){
        UInt8 * b = *buffer;
#if 0
        printf("Received to %.2x:%.2x:%.2x:%.2x:%.2x:%.2x from %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
            b[0], b[1], b[2], b[3], b[4], b[5], b[6],
            b[7], b[8], b[9], b[10], b[11]);
#endif
        *length = header->len;
        return 1;
    }
    return 0;
}

void archEthGetMacAddress(UInt8* macAddr) 
{ 
    parseMac(macAddr, propGetGlobalProperties()->ports.Eth.macAddress);
}
