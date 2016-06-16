#pragma once
#include "vec3.h"


union mat3
{
    vec3  c[3];
    float m[9];
    float mm[3][3];

    vec3  operator[](unsigned idx) const { return c[idx]; }
    vec3 &operator[](unsigned idx)       { return c[idx]; }

    static constexpr mat3 zero()     { return mat3{0,0,0,0,0,0,0,0,0}; }
    static constexpr mat3 identity() { return mat3{1,0,0, 0,1,0, 0,0,1}; }

    float det() const { return dot(c[0], cross(c[1],c[2])); }
    
    mat3 inverse() const;

    mat3 transpose() const 
    {
      return mat3
        {m[0],m[3],m[6],
         m[1],m[4],m[7],
         m[2],m[5],m[8]};
    }

    static mat3 translate(const vec2 &xy)
    {
        mat3 r = identity();
        r.c[2] = vec3{xy.x, xy.y, 1};
        return r;
    }
    static mat3 rotate(float a)
    {
        mat3 r = identity();

        r.c[0] = vec3{cos(a) , sin(a) , 0};
        r.c[1] = vec3{-sin(a) , cos(a) , 0};

        return r;
    }
    static mat3 scale(vec2 xy)
    {
        mat3 r = identity();
        r.mm[0][0] = xy.x;
        r.mm[1][1] = xy.y;
        return r;
    }
};

inline vec3 operator*(const mat3 &a_a, const vec3 &b)
{
    mat3 a = a_a.transpose();
    return vec3 { dot(a[0],b), dot(a[1],b), dot(a[2],b)};
}

inline mat3 operator*(const mat3 &a_a, float b)
{
    mat3 a = a_a.transpose();
    mat3 res = mat3::zero();
    for (unsigned i = 0; i < 3; ++i)
            res[i] *= b;
    return res;
}


inline mat3 mat3::inverse() const
{
        return mat3 { cross(c[1],c[2]), cross(c[2],c[0]), cross(c[0],c[1]) }.transpose() * (1/det());
}


inline mat3 operator*(const mat3 &_A, const mat3 &B)
{
    //A can now access rows as vector3
    mat3 r, A = _A.transpose();

    //for (size_t i = 0; i < 3; ++i)
    //    r.c[i] = Vector3(dot(A.c[0], B.c[i]), dot(A.c[1], B.c[i]), dot(A.c[2], B.c[i]));

    // Filling out columns for r here:
    r.c[0] = vec3{dot(A.c[0], B.c[0]), dot(A.c[1], B.c[0]), dot(A.c[2], B.c[0])};
    r.c[1] = vec3{dot(A.c[0], B.c[1]), dot(A.c[1], B.c[1]), dot(A.c[2], B.c[1])};
    r.c[2] = vec3{dot(A.c[0], B.c[2]), dot(A.c[1], B.c[2]), dot(A.c[2], B.c[2])};

    return r;
}