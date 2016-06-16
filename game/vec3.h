#pragma once
#include <cmath>
#include "vec2.h"

union vec3
{
    struct { vec2 xy; float z; };
    struct { float x, y;       };
    float v[3];

    float  operator[](unsigned idx) const { return v[idx]; };
    float &operator[](unsigned idx)       { return v[idx]; };
};


inline vec3 operator+(const vec3 &a, const vec3 &b) { return vec3 { a.x + b.x, a.y + b.y, a.z + b.z }; }
inline vec3 operator-(const vec3 &a, const vec3 &b) { return vec3 { a.x - b.x, a.y - b.y, a.z - b.z }; }
inline vec3 operator/(const vec3 &a, float b)       { return vec3 { a.x / b  , a.y / b  , a.z / b   }; }
inline vec3 operator*(const vec3 &a, float b)       { return vec3 { a.x * b  , a.y * b  , a.z * b   }; }
inline vec3 operator*(float a, const vec3 &b)       { return b * a; };

inline vec3 operator-(const vec3 &a) { return a * -1; }

inline vec3 &operator+=(vec3 &a, const vec3 &b) { return a = a + b; }
inline vec3 &operator-=(vec3 &a, const vec3 &b) { return a = a - b; }
inline vec3 &operator/=(vec3 &a, float b)       { return a = a / b; }
inline vec3 &operator*=(vec3 &a, float b)       { return a = a * b; }

inline float dot(const vec3 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

inline float magnitude(const vec3 &a) { return sqrtf(dot(a, a)); }
inline vec3 normal(const vec3 &a)     { return a / magnitude(a); }

inline vec3 cross(const vec3 &a, const vec3 &b)
{
return vec3 {
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
            };
}

inline float angleBetween(const vec3 &aN, const vec3 &bN) { return acosf(dot(aN, bN)); }

inline vec3 lerp(const vec3 &a, const vec3 &b, float t) { return (1 - t) * a + t * b; }


inline vec3 min(const vec3 &a, const vec3 &b) { return vec3{ std::fminf(a.x,b.x), std::fminf(a.y,b.y), std::fminf(a.z,b.z) }; }
inline vec3 max(const vec3 &a, const vec3 &b) { return vec3{ std::fmaxf(a.x,b.x), std::fmaxf(a.y,b.y), std::fmaxf(a.z,b.z) }; }

inline vec3 clamp(const vec3 &val, const vec3 &low, const vec3 &high) { return min(high, max(val, low)); }

inline vec3 snap (const vec3 &val, const vec3 &low, const vec3 &high)
{
    return{ std::fabsf(val.x - low.x) < std::fabsf(high.x - val.x) ? low.x : high.x,
            std::fabsf(val.y - low.y) < std::fabsf(high.y - val.y) ? low.y : high.y,
            std::fabsf(val.z - low.z) < std::fabsf(high.z - val.z) ? low.z : high.z};
}

inline vec3 project(const vec3 &incident, const vec3 &normal) { return dot(incident, normal) * normal; }
inline vec3 reflect(const vec3 &incident, const vec3 &normal) { return 2 * project(incident, normal) - incident; }