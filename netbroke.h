#pragma once

#pragma comment( lib, "wsock32.lib" ) // windows top-level wrapper for winsock - 'WSA' functions
#pragma comment( lib, "ws2_32.lib"  ) // traditional socket libraries

#include <WinSock2.h>   // for wsock32.lib
#include <WS2tcpip.h>   // for ws2_32.lib

#include <cstring>

namespace nsfw
{
    bool initNetworking() { WSAData data; return WSAStartup(MAKEWORD(2, 2), &data) == 0; }
    bool termNetworking() {               return WSACleanup()                      == 0; }

    //format: "127.1.1.0:50000"
    sockaddr_in stoa(const char *src, size_t len)
    {
        
        union { char values[4]; unsigned ui; } IP; // this solves endianess
        unsigned short port;
        sockaddr_in dst;
        const char *ptr = src; 

        IP.values[0] = atoi(ptr); ptr += strcspn(ptr, ".") + 1;
        IP.values[1] = atoi(ptr); ptr += strcspn(ptr, ".") + 1;
        IP.values[2] = atoi(ptr); ptr += strcspn(ptr, ".") + 1;
        IP.values[3] = atoi(ptr); ptr += strcspn(ptr, ":") + 1;
        port         = atoi(ptr);
        
        dst.sin_family = AF_INET;
        dst.sin_addr.S_un.S_addr = IP.ui;
        dst.sin_port = htons(port);
        return dst;
    }
}