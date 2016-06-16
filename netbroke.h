#pragma once

#pragma comment( lib, "wsock32.lib" ) // windows top-level wrapper for winsock - 'WSA' functions
#pragma comment( lib, "ws2_32.lib"  ) // traditional socket libraries

#include <WinSock2.h>   // for wsock32.lib
#include <WS2tcpip.h>   // for ws2_32.lib

#include <cstring>

namespace nsfw
{
    // necessary prerequisites for working with windows networking
    bool initNetworking() { WSAData data; return WSAStartup(MAKEWORD(2, 2), &data) == 0; }
    bool termNetworking() {               return WSACleanup()                      == 0; }

    //convert string of format: "127.1.1.0:50000" to sockaddr_in
    sockaddr_in stoa(const char *src)
    {        
        sockaddr_in dst;

        union { char values[4]; unsigned ui; } IP; // this solves endianess
        unsigned short port;
        
        const char *ptr = src; 
        // Many ways to do this!
        IP.values[0] = atoi(ptr);   ptr += strcspn(ptr, ".") + 1;
        IP.values[1] = atoi(ptr);   ptr += strcspn(ptr, ".") + 1;
        IP.values[2] = atoi(ptr);   ptr += strcspn(ptr, ".") + 1;
        IP.values[3] = atoi(ptr);   ptr += strcspn(ptr, ":") + 1;        
        port         = atoi(ptr);
        
        dst.sin_family = AF_INET;   //IPv4 -options include bluetooth, IR, etc.
        dst.sin_addr.S_un.S_addr = IP.ui; // IP address as single integer
        dst.sin_port = htons(port); //Port number. lookup MSB vs LSB!
        return dst;
    }

    struct Packet
    {
        unsigned header;
        float timestamp;
        char bytes[1500];
    };

    /*
        Manages communication over IPv4.
    */
    class Socket
    {
        int handle = 0;
    public:
        ~Socket() { close(); }
        
        bool isOpen() const { return handle > 0; }
        
        bool open(unsigned short port = 0)
        {            
            sockaddr_in addr;
            addr.sin_family           = AF_INET;
            addr.sin_addr.S_un.S_addr = INADDR_ANY;
            addr.sin_port             = htons(port);            
            DWORD param = 1;

            handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
            bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in));
            ioctlsocket(handle, FIONBIO, &param);
            return true;
        }
        bool close()
        {
            if (!isOpen())
            closesocket(handle);
            handle = 0;
            return true;
        }

        // Packet, address
        bool send(const char *data, int dlen, const sockaddr_in &addr)
        {
            return sendto(handle, data, dlen, 0, (sockaddr*)&addr, sizeof(sockaddr_in)) == dlen;
        }
        bool recv(char *data, int dlen, sockaddr_in &addr)
        {
            int in_len = sizeof(sockaddr_in);
            return recvfrom(handle, data, dlen, 0, (sockaddr*)& addr, &in_len) == dlen;
        }
    };
}

//sendto(handle, out_buffer, 40, 0, (sockaddr*)&out_addr, sizeof(sockaddr_in));   // failed to send if retval != packet_size
//recvfrom(handle, in_buffer, 40, 0, (sockaddr*)& in_addr, &in_len);             // no data if retval <= 0