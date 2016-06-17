#include "game\Game.h"

#include "netbroke.h"
#include <iostream>
#include <vector>
#include <unordered_map>

void main()
{
    sfwl::initContext();
    nsfw::initNetworking();
 
    bool server = true;

    // Replaced with Arrays
    Player localPlayer;
    std::vector<Ship>                ships;
    std::vector<ShipInput>           inputs;
    std::unordered_map<unsigned long, size_t> connections;

    // Initialize local player
    ships.emplace_back();
    inputs.emplace_back();
    ships[0].color = 0x7700FF;

    nsfw::Socket mysocket;

    mysocket.open(50000);

    nsfw::Address inaddr, outaddr(10,15,22,54,50000);                                   
    unsigned long MYIP = outaddr.getIPH();
    
    connections[MYIP] = 0;
    struct PACKET { unsigned long keyIP; float time; ShipInput input; Ship state; };
    PACKET in_data, out_data;

    while (sfwl::stepContext())
    {
        float dt = sfwl::getDeltaTime();
     // use loops now!   
        inputs[0] = localPlayer.getInput(ships[0]);
        
        for (size_t i = 0; i < ships.size(); ++i)
        {
            ships[i].update(dt, inputs[i]);
            ships[i].draw();
        }

        Particle::updateAll(dt);
        Particle::drawAll();                   

        if (!server)
        {
            out_data = { 0, sfwl::getTime(), inputs[0], ships[0] };
            mysocket.send((char*)&out_data, sizeof(PACKET), outaddr);
        }

        while (mysocket.recv((char*)&in_data, sizeof(PACKET), inaddr))
        {         
            unsigned long tIP = server? inaddr.getIPH() : in_data.keyIP;

            if (connections.count(tIP) == 0)
            {
                connections[tIP] = ships.size();
                ships.emplace_back();
                inputs.emplace_back();
            }

            size_t current  = connections[tIP];            
            inputs[current] = in_data.input;
            ships[current]  = in_data.state;
            
            if(server)
                for each(auto c in connections)
                    if(c.first != tIP)
                    {
                        out_data = {c.first, sfwl::getTime(), inputs[c.second], ships[c.second]};
                        mysocket.send((char*)&out_data, sizeof(PACKET), inaddr);
                    }
        }
    }


    mysocket.close();
    sfwl::termContext();
    nsfw::termNetworking();
}