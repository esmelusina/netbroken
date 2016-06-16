#pragma once
#include "Ship.h"

struct Controller
{
    virtual ShipInput getInput(const Ship &self)
    {
        return ShipInput{0,0};
    };
};



struct Player : public Controller
{
    char up    = 'W',
         down  = 'S',
         left  = 'A',
         right = 'D';

    ShipInput getInput(const Ship &self)
    {
        return ShipInput{sfwl::getKey(left)*1.f - sfwl::getKey(right)*1.f,
                         sfwl::getKey(up  )*1.f - sfwl::getKey(down )*1.f};
    }
};

struct AI : Controller
{
    vec2 next;
    
    AI() {next = {800 * rand01(), 600 * rand01()};}

    ShipInput getInput(const Ship &self)
    {
        ShipInput res = {0,0};
        vec2 pos = self.pos;
        vec2 dir = normal(next - pos);
        vec2 cur = vec2::fromAngle(self.angle);
   
        res.horz = cross(dir,cur);
        res.vert = dot(dir,cur);

        if (magnitude(next - self.pos) < 48)
            next = {800 * rand01(), 600 * rand01()};

        if (_DEBUG)
        {
            sfwl::drawBox(next.x, next.y, 4, self.color);
        }

        return res;
    }
};