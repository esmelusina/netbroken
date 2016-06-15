

#pragma comment( lib, "wsock32.lib" ) // windows top-level wrapper for winsock
#pragma comment( lib, "ws2_32.lib"  ) // traditional winsock libraries

#include <WinSock2.h>
#include <WS2tcpip.h>

int main(int cargs, char *vargs[])
{
    WSAData data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != NO_ERROR)
        exit(0);

    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   



    closesocket(handle);
    WSACleanup();
    return 0;
}