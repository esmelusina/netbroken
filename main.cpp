#include "game\Game.h"

#include "netbroke.h"
#include <iostream>


void main()
{
    sfwl::initContext();
    nsfw::initNetworking();

    ShipInput si1;
    Ship      ship1;
    Player    player1;

    while (sfwl::stepContext())
    {
        float dt = sfwl::getDeltaTime();

        si1 = player1.getInput(ship1);
        ship1.update(dt, si1);
        ship1.draw();

        Particle::updateAll(dt);
        Particle::drawAll();
    }


    sfwl::termContext();
    nsfw::termNetworking();
}