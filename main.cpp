
#include "netbroke.h"


int main(int cargs, char *vargs[])
{
    nsfw::initNetworking();

    nsfw::Socket mysocket;
    mysocket.open(50000);
 
    nsfw::Address out_addr(127,0,0,1,50000);
    nsfw::Address in_addr;

    nsfw::Packet out_pack {0,0, "Dinosaurs!"};
    nsfw::Packet in_pack;
    
    mysocket.send(out_pack, out_addr );
    mysocket.recv( in_pack, in_addr );

    mysocket.close();
    nsfw::termNetworking();
}
