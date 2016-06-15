

#pragma comment( lib, "wsock32.lib" ) // windows top-level wrapper for winsock
#pragma comment( lib, "ws2_32.lib"  ) // traditional winsock libraries
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

int main(int cargs, char *vargs[])
{
    WSAData data;
    WSAStartup(MAKEWORD(2, 2), &data); // failed if != NO_ERROR

    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // failed on <= 0
   
    sockaddr_in addr; // Internet address intended for use
                      // with sockets

    addr.sin_family           = AF_INET;
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    addr.sin_port             = htons(50000);
    
    bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in)); // failed on < 0
    
    DWORD param = 1;
    ioctlsocket(handle, FIONBIO, &param);   // non-blocking! fails on non-zero

    sockaddr_in out_addr, in_addr;
    int in_len = sizeof(sockaddr_in);
    char out_buffer[40] = "Dinosaur!"; // packet is 40 bytes!
    char  in_buffer[40];

    // targeting my local host
    out_addr.sin_family = AF_INET;
    out_addr.sin_addr.S_un.S_un_b.s_b1 = 127; // 10.15.22.54
    out_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
    out_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
    out_addr.sin_addr.S_un.S_un_b.s_b4 = 1;
    out_addr.sin_port = htons(50000);

    int out_bytes = 
               sendto(handle, out_buffer, 40, 0, (sockaddr*)&out_addr, sizeof(sockaddr_in));

    int in_bytes = 
             recvfrom(handle,  in_buffer, 40, 0, (sockaddr*)& in_addr, &in_len); 

    closesocket(handle);
    WSACleanup();
    return 0;
}