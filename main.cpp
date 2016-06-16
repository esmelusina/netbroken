#include "game\Game.h"

#include "netbroke.h"
#include <iostream>

void main()
{
    sfwl::initContext();
    nsfw::initNetworking();

    ShipInput  input1, input2,  input3 = {0,0};
    Ship        ship1,   ship2,  ship3;
    
    Player    player1;
    AI        player2;
    //AI        player3;

    ship1.color = 0x7700FF;
    ship2.color = CYAN;
    ship3.color = GREEN;

    nsfw::Socket mysocket;

    mysocket.open(50000);
    nsfw::Address inaddr, outaddr(10,15,22,61,50000);
                                                        
    struct PACKET { float time; ShipInput input; Ship state; };
    PACKET in_data, out_data;

    while (sfwl::stepContext())
    {
        float dt = sfwl::getDeltaTime();

        input1 = player1.getInput(ship1);
        input2 = player2.getInput(ship2);

        ship1.update(dt, input1);
        ship2.update(dt, input2);
        ship3.update(dt, input3);

        ship1.draw();
        ship2.draw();
        ship3.draw();

        Particle::updateAll(dt);
        Particle::drawAll();       


        out_data = { sfwl::getTime(), input1, ship1 };       

        mysocket.send((char*)&out_data, sizeof(PACKET), outaddr); // use input1!
                
        float latest = 0;

        while (mysocket.recv((char*)&in_data, sizeof(PACKET), inaddr))
        {
            mysocket.send((char*)&out_data, sizeof(PACKET), inaddr);
            if(latest < in_data.time)
            {                
                latest = in_data.time;
                input3 = in_data.input;
                ship3  = in_data.state;
            }
        } 
    }

    mysocket.close();
    sfwl::termContext();
    nsfw::termNetworking();
}