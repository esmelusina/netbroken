
#include "netbroke.h"


int main(int cargs, char *vargs[])
{
    nsfw::initNetworking();

    nsfw::Socket mysocket;
    mysocket.open(50000);
 
    nsfw::Address out_addr(127,0,0,1,50000);
    nsfw::Address in_addr;

    char out_pack[40] {"Dinosaurs!"};
    char in_pack[40];
    
    mysocket.send(out_pack, 40, out_addr );
    mysocket.recv( in_pack, 40, in_addr );

    mysocket.close();
    nsfw::termNetworking();
}
