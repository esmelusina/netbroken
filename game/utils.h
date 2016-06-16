#pragma once
#include "sfwl.h"
#include "mat3.h"

inline float rand01()
{
    return (rand() / (float)RAND_MAX);
}

inline float randN1U1()
{
    return 1.f - 2.f *(rand() / (float)RAND_MAX);
}

inline float lerp(float a, float b, float t)
{
    return (1-t)*a + t*b;
}

inline unsigned inverseColor(unsigned a)
{
    union Color
    {
        unsigned RGBA;
        unsigned char c[4];
    };

    Color A = {a};
    Color C;
    C.c[0] = 255 - A.c[0];
    C.c[1] = 255 - A.c[1];
    C.c[2] = 255 - A.c[2];
    C.c[3] = 255 - A.c[3];

    return C.RGBA;
}

inline unsigned lerpColor(unsigned a, unsigned b, float t)
{
    union Color
    {
        unsigned RGBA;
        unsigned char c[4];
    };

    Color A = {a};
    Color B = {b};
    Color C;
    C.c[0] = lerp(A.c[0]/255.f,B.c[0]/255.f,t)*255.f;
    C.c[1] = lerp(A.c[1]/255.f,B.c[1]/255.f,t)*255.f;
    C.c[2] = lerp(A.c[2]/255.f,B.c[2]/255.f,t)*255.f;
    C.c[3] = lerp(A.c[3]/255.f,B.c[3]/255.f,t)*255.f;

    return C.RGBA;
}

inline void drawCircle(const vec2 &p, float rad, unsigned step, unsigned color)
{
    for(unsigned i = 1; i <= step; ++i)
    {
        vec2 prev = vec2::fromAngle(i * 2*PI/step) * rad;
        vec2 next = vec2::fromAngle((i-1) * 2*PI/step) * rad;
        sfwl::drawLine(prev.x,prev.y,next.x,next.y,color, mat3::translate(p).m);
     }
}