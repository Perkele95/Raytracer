#pragma once

#include <stdint.h>
#include <math.h>
#include <fstream>

// ---------------------
// Vectors
// ---------------------

struct vec3
{
    float x, y, z;
};

// Extra functions to add vectors to io streams
inline std::istream& operator>>(std::istream &is, vec3 &t)
{
    is >> t.x >> t.y >> t.z;
    return is;
}
inline std::ostream& operator<<(std::ostream &os, const vec3 &t)
{
    os << t.x << " " << t.y << " " << t.z;
    return os;
}
// --------------------------------------

inline vec3 operator*(float a, vec3 b)
{
    vec3 result;

    result.x = a * b.x;
    result.y = a * b.y;
    result.z = a * b.z;

    return result;
}

inline vec3 operator*(vec3 b, float a)
{
    return a * b;
}

inline vec3 operator/(float a, vec3 b)
{
    vec3 result;

    result.x = b.x / a;
    result.y = b.y / a;
    result.z = b.z / a;

    return result;
}

inline vec3 operator/(vec3 b, float a)
{
    return a / b;
}

inline vec3& operator*=(vec3 &a, float b)
{
    a = b * a;

    return a;
}

inline vec3& operator/=(vec3 &a, float b)
{
    a = b / a;

    return a;
}

inline vec3& operator*=(vec3 &a, vec3 b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;

    return a;
}

inline vec3& operator/=(vec3 &a, vec3 b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;

    return a;
}


inline vec3 operator+(vec3 a)
{
    vec3 result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;

    return result;
}

inline vec3 operator+(vec3 a, vec3 b)
{
    vec3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline vec3 operator+(float b, vec3 a)
{
    vec3 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3 operator+(vec3 a, float b)
{
    vec3 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3& operator+=(vec3 &a, vec3 b)
{
    a = a + b;

    return a;
}

inline vec3 operator-(vec3 a, vec3 b)
{
    vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline vec3 operator-(vec3 a, float b)
{
    vec3 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3 operator-(float b, vec3 a)
{
    vec3 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3& operator-=(vec3 &a, vec3 b)
{
    a = a - b;

    return a;
}

inline float vec3Length(vec3 vec)
{
    float result = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return result;
}

inline float vec3SquaredLength(vec3 vec)
{
    float result = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
    return result;
}

inline vec3 normalise(vec3 vec)
{
    float length = vec3Length(vec);
    vec3 result;

    result.x = vec.x / length;
    result.y = vec.y / length;
    result.z = vec.z / length;

    return result;
}

inline float vec3Dot(vec3 a, vec3 b)
{
    float result = a.x * b.x + a.y * b.y + a.z * b.z;

    return result;
}

inline vec3 vec3Cross(vec3 a, vec3 b)
{
    vec3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}