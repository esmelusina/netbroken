

#pragma comment( lib, "wsock32.lib" ) // windows top-level wrapper for winsock - 'WSA' functions
#pragma comment( lib, "ws2_32.lib"  ) // traditional socket libraries

#include <iostream>
#include <WinSock2.h>   // for wsock32.lib
#include <WS2tcpip.h>   // for ws2_32.lib

#include "netbroke.h"

int main(int cargs, char *vargs[])
{
    auto d = nsfw::stoa("126.0.0.1:234", 14);


    WSAData data;
    WSAStartup(MAKEWORD(2, 2), &data); // failed if != NO_ERROR

    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // failed on <= 0
   
    sockaddr_in addr; // Internet address intended for use
                      // With Sockets

    addr.sin_family           = AF_INET;
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    addr.sin_port             = htons(50000);
    
    bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in)); // failed on < 0
    
    DWORD param = 1;
    ioctlsocket(handle, FIONBIO, &param);   // non-blocking! fails on != 0

    sockaddr_in out_addr, in_addr;
    int in_len = sizeof(sockaddr_in);
    char out_buffer[40] = "I see you!"; // packet is 40 bytes!
    char  in_buffer[40];

    // targeting my local host
    out_addr.sin_family = AF_INET;
    out_addr.sin_addr.S_un.S_un_b.s_b1 = 127; // 10.15.22.54
    out_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
    out_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
    out_addr.sin_addr.S_un.S_un_b.s_b4 = 1;
    out_addr.sin_port = htons(50000);

    // Send packet immediately to ourself
    sendto(handle, out_buffer, 40, 0, (sockaddr*)&out_addr, sizeof(sockaddr_in));   // failed to send if retval != packet_size
    recvfrom(handle,  in_buffer, 40, 0, (sockaddr*)& in_addr, &in_len);             // no data if retval <= 0
   
    // Echo server- sends out_buffer to anybody that sends any data to us
    //while (true)
    //{
    //    while (recvfrom(handle,  in_buffer, 40, 0, (sockaddr*)&in_addr, &in_len) > 0)
    //             sendto(handle, out_buffer, 40, 0, (sockaddr*)&in_addr, sizeof(sockaddr_in));
    //}

    closesocket(handle);
    WSACleanup();
    return 0;
}