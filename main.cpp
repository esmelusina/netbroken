#include "game\Game.h"

#include "netbroke.h"
#include <iostream>

void main()
{
    sfwl::initContext();
    nsfw::initNetworking();

    ShipInput  input1,  input2, input3;
    Ship        ship1,   ship2,   ship3;
    
    Player    player1;
    AI        player2;
    AI        player3;

    ship2.color = CYAN;
    ship3.color = GREEN;

    // Open up a socket
    // input and output address objects
    // Send one of my ships's inputs across the network
    // Recieve input for one of my ships
    nsfw::Socket mysocket;

    mysocket.open(50000);
    nsfw::Address inaddr, outaddr(127,0,0,1,50000);


    while (sfwl::stepContext())
    {
        float dt = sfwl::getDeltaTime();

        input1 = player1.getInput(ship1);
        input2 = player2.getInput(ship2);
        input3 = player3.getInput(ship3);

        mysocket.send((char*)&input3, sizeof(ShipInput), outaddr);
        mysocket.recv((char*)&input3, sizeof(ShipInput),  inaddr);

        ship1.update(dt, input1);
        ship2.update(dt, input2);
        ship3.update(dt, input3);

        ship1.draw();
        ship2.draw();
        ship3.draw();

        Particle::updateAll(dt);
        Particle::drawAll();
    }

    mysocket.close();
    sfwl::termContext();
    nsfw::termNetworking();
}