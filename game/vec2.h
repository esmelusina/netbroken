#pragma once
#include <cmath>

union vec2
{
    struct { float x, y; };
    float v[2];

    float  operator[](unsigned idx) const { return v[idx]; };
    float &operator[](unsigned idx)       { return v[idx]; };
    static vec2 fromAngle(float a) { return {cos(a),sin(a)}; }
};


inline vec2 operator+(const vec2 &a, const vec2 &b) { return vec2 { a.x + b.x, a.y + b.y }; }
inline vec2 operator-(const vec2 &a, const vec2 &b) { return vec2 { a.x - b.x, a.y - b.y }; }
inline vec2 operator/(const vec2 &a, float b)       { return vec2 { a.x / b  , a.y / b   }; }
inline vec2 operator*(const vec2 &a, float b)       { return vec2 { a.x * b  , a.y * b   }; }
inline vec2 operator*(float a, const vec2 &b)       { return b * a; };

inline vec2 operator-(const vec2 &a) { return a * -1; }

inline vec2 &operator+=(vec2 &a, const vec2 &b) { return a = a + b; }
inline vec2 &operator-=(vec2 &a, const vec2 &b) { return a = a - b; }
inline vec2 &operator/=(vec2 &a, float b)       { return a = a / b; }
inline vec2 &operator*=(vec2 &a, float b)       { return a = a * b; }

inline float dot(const vec2 &a, const vec2 &b) { return a.x*b.x + a.y*b.y; }

inline float magnitude(const vec2 &a) { return sqrtf(dot(a, a)); }
inline vec2 normal(const vec2 &a)     { return a / magnitude(a); }


inline vec2 perp(const vec2 &a, bool left = true) { return vec2 { (1-2*left) * a.y, (2*left-1) * a.x }; }

inline float angle(const vec2 &a)                { return atan2f(a.y, a.x); }

inline float cross(const vec2 &a, const vec2 &b) { return dot(a,perp(b)); }

inline float angleBetween(const vec2 &aN, const vec2 &bN) { return acosf(dot(aN, bN)); }

inline vec2 lerp(const vec2 &a, const vec2 &b, float t) { return (1 - t) * a + t * b; }


inline vec2 min(const vec2 &a, const vec2 &b) { return vec2{ std::fminf(a.x,b.x), std::fminf(a.y,b.y) }; }
inline vec2 max(const vec2 &a, const vec2 &b) { return vec2{ std::fmaxf(a.x,b.x), std::fmaxf(a.y,b.y) }; }

inline vec2 clamp(const vec2 &val, const vec2 &low, const vec2 &high) { return min(high, max(val, low)); }

inline vec2 snap (const vec2 &val, const vec2 &low, const vec2 &high)
{
    return{ std::fabsf(val.x - low.x) < std::fabsf(high.x - val.x) ? low.x : high.x,
            std::fabsf(val.y - low.y) < std::fabsf(high.y - val.y) ? low.y : high.y };
}

inline vec2 project(const vec2 &incident, const vec2 &normal) { return dot(incident, normal) * normal; }
inline vec2 reflect(const vec2 &incident, const vec2 &normal) { return 2 * project(incident, normal) - incident; }
