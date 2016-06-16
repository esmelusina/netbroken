#pragma once
#include "vec2.h"
#include "utils.h"


struct Particle
{
    float lifetime = 0,
          lifespan = 0.72f;
    float startRadius = 1,
            endRadius = 4;
    unsigned startColor = 0x4400CC00,
             endColor   = 0xEE000000;
    unsigned startSteps = 3,
               endSteps = 7;
    vec2 pos = {0,0};   
    vec2 vel = {0,0};
    bool alive = false;

    // static methods for dealing with the pool, simplest implementation
    static Particle *pool()         { static Particle pool[1024]; return pool; }
    static void updateAll(float dt) { for(unsigned i = 0; i < 1024; ++i)pool()[i].update(dt); }
    static void drawAll()           { for(unsigned i = 0; i < 1024; ++i)pool()[i].draw(); }


    static void spawn(const Particle &data)
    {
        Particle *p = pool();

        for(unsigned i = 0; i < 1024; ++i)
            if (!p[i].alive)
            {
                p[i] = data;
                p[i].alive = true;
                return;
            }
    }

    void update(float dt)
    {
    lifetime += dt;
    float t = lifetime/lifespan;
    pos += vel * dt;
    alive = t <= 1;
    }


    void draw()
    {
    if(!alive)return;
    float t = lifetime / lifespan;
    drawCircle(pos, lerp(startRadius,endRadius,t),
                    lerp(startSteps,endSteps,t),
                    lerpColor(lerpColor(endColor,startColor,t),0x55555555,t));
    }
};


