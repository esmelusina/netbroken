#include "game\Game.h"

#include "netbroke.h"
#include <iostream>
#include <vector>
#include <unordered_map>

void main()
{
    sfwl::initContext();
    nsfw::initNetworking();
    
    Player localPlayer;
    std::vector<Ship>                ships;
    std::vector<ShipInput>           inputs;
    std::unordered_map<unsigned long, size_t> connections;

    ships.emplace_back();
    inputs.emplace_back();

    ships[0].color = 0x7700FF;

    nsfw::Socket mysocket;

    mysocket.open(50000);
    nsfw::Address inaddr, outaddr(10,15,22,61,50000);
                                                        
    struct PACKET { float time; ShipInput input; Ship state; };
    PACKET in_data, out_data;

    while (sfwl::stepContext())
    {
        float dt = sfwl::getDeltaTime();
        
        inputs[0] = localPlayer.getInput(ships[0]);
        
        for (size_t i = 0; i < ships.size(); ++i)
        {
            ships[i].update(dt, inputs[i]);
            ships[i].draw();
        }

        Particle::updateAll(dt);
        Particle::drawAll();       


        out_data = { sfwl::getTime(), inputs[0], ships[0] };       

        mysocket.send((char*)&out_data, sizeof(PACKET), outaddr); // use input1!
                

        while (mysocket.recv((char*)&in_data, sizeof(PACKET), inaddr))
        {
            mysocket.send((char*)&out_data, sizeof(PACKET), inaddr);
            // Asset a new player!
            if (connections.count(inaddr.getIPH()) == 0)
            {
                connections[inaddr.getIPH()] = ships.size();
                ships.emplace_back();
                inputs.emplace_back();
            }

            size_t current = connections[inaddr.getIPH()];            
            inputs[current] = in_data.input;
            ships[current]  = in_data.state;
        }
    }

    mysocket.close();
    sfwl::termContext();
    nsfw::termNetworking();
}