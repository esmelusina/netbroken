#include "game\Game.h"

#include "netbroke.h"
#include <iostream>

int mainServer(int cargs, char *vargs[])
{
    nsfw::initNetworking();

    nsfw::Socket mysocket;
    mysocket.open(50000);
 
    nsfw::Address out_addr("10.15.22.54:50000");
    nsfw::Address in_addr;

    char out_pack[256] {"Message Recieved!"};
    char in_pack[256];
    
    mysocket.send(out_pack, 256, out_addr );
    bool ignoreFirst = true;
    // 10.15.22.54 : 50000
    while (true)
    {
        while (mysocket.recv(in_pack, 256, in_addr))
        {
            if(!ignoreFirst) mysocket.send(out_pack, 256, in_addr);
            
            ignoreFirst = false;

            char buff[256];
            in_addr.toString(buff,256);
            std::cout << in_pack << "  (" << buff << ")" << std::endl;
        } 

    }

    mysocket.close();
    nsfw::termNetworking();
}
