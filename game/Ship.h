#pragma once

#include "mat3.h"
#include "sfwl.h"
#include "Particle.h"
#include "utils.h"
           
#define DEADZONE .25f

struct ShipInput      { float horz, vert; }; // -1 to 1 range, horz turns, vert accelerates

struct Ship
{    
    unsigned UID, color = YELLOW;

    float speed = 320,
       angSpeed = 40;    
    
    float drag = 1.2f,
       angDrag = 8.0f;

    vec2 pos = {400,300},
         vel = {0,0},
         acc = {0,0},
        size = {10,10};

    float angle = 0,
         angVel = 0,
         angAcc = 0;

    float trailTimer = 0;
    float emissionRate = 0.02f;

    void update(float dt, const ShipInput &i = { 0, 0 })
    { 
        // particle emission
        trailTimer-=dt;
        if(std::fabsf(i.vert) > 0 && trailTimer < 0.f)
        {
            trailTimer = emissionRate;
            Particle bob;
            bob.startColor = color;
            bob.endColor   = inverseColor(color);
            bob.pos = pos - vec2::fromAngle(angle) * 6.f;
            bob.vel = normal(bob.pos - pos) * 8;
            Particle::spawn(bob);
        }

        // integrate angular stuff
        angAcc  = i.horz * angSpeed;        
        angVel += (angAcc - angVel*angDrag) * dt;
        angle  += angVel * dt;

        // integrate position stuff
        acc  = i.vert * vec2::fromAngle(angle) * speed;
        vel += (acc - vel*drag) * dt ;
        pos += vel * dt;

        // HOW 'BOUT 'DEM APPLES (magic numbers for bounds checking/looping)
       if(pos.x < -20) pos.x = 815;
       if(pos.x > 820) pos.x = -15;
       if(pos.y < -12) pos.y = 608;
       if(pos.y > 612) pos.y = -8;
    }

    void draw()
    {
        //calculate global transform
        mat3 m = mat3::translate(pos) * mat3::scale(size) * mat3::rotate(angle);

        // draw inline
        sfwl::drawLine(  2.4f,   0 ,   0,  .7f,  WHITE,  m.m);
        sfwl::drawLine(  2.4f,   0 ,   0, -.7f,  WHITE,  m.m);
        sfwl::drawLine(  0, -.7f, -.6f,   0,  WHITE,  m.m);
        sfwl::drawLine(  0,  .7f, -.6f,   0,  WHITE,  m.m);
        
        // draw outline
        sfwl::drawLineGradient(  3,  0,  0,  1,  inverseColor(color), color,  m.m);
        sfwl::drawLineGradient(  3,  0,  0, -1,  inverseColor(color), color, m.m);
        sfwl::drawLine(  0, -1, -1,  0,  color,  m.m);
        sfwl::drawLine(  0,  1, -1,  0,  color,  m.m);
    }

    void lerpPhysics(const Ship &o, float t)
    {
        pos    = lerp(pos,    o.pos,    t);
        vel    = lerp(vel,    o.vel,    t);
        angle  = lerp(angle,  o.angle,  t);
        angVel = lerp(angVel, o.angVel, t);
    }
};

