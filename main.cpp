#include "game\Game.h"

#include "netbroke.h"
#include <iostream>

void main()
{
    sfwl::initContext();
    nsfw::initNetworking();

    ShipInput  input1,  input2;
    Ship        ship1,   ship2;
    Player    player1, player2;

    ship2.color = CYAN;

    while (sfwl::stepContext())
    {
        float dt = sfwl::getDeltaTime();

        input1 = player1.getInput(ship1);
        input2 = player2.getInput(ship2);

        ship1.update(dt, input1);
        ship2.update(dt, input2);

        ship1.draw();
        ship2.draw();

        Particle::updateAll(dt);
        Particle::drawAll();
    }

    sfwl::termContext();
    nsfw::termNetworking();
}