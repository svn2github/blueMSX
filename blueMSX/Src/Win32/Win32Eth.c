/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Eth.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-08-28 05:42:06 $
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

#define WPCAP
#define HAVE_REMOTE
#include "pcap.h"

#include <stdio.h>

static char errbuf[PCAP_ERRBUF_SIZE];
static pcap_t *pcapHandle = NULL;

static char devName[512];
void win32EthGetDeviceList()
{
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int i = 0;

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        return;
    }

    strcpy(devName, alldevs->name);
    
    for(d=alldevs; d; d=d->next)
    {
        if (!d->description) {
            continue;
        }

        printf("%d. %s\n", ++i, d->name);
        printf(" (%s)\n", d->description);
     }

    pcap_freealldevs(alldevs);
}

void archEthCreate() 
{
    win32EthGetDeviceList();

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
    printf("Sending to %.2x:%.2x:%.2x:%.2x:%.2x:%.2x from %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
        buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6],
        buffer[7], buffer[8], buffer[9], buffer[10], buffer[11]);

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
        printf("RECEIVED PACKET len:%d\n", header->len);
        *length = header->len;
        return 1;
    }
    return 0;
}

void archEthGetMacAddress(UInt8* macAddress) 
{ 
    memcpy(macAddress, "\0ABCDE", 6); 
}
