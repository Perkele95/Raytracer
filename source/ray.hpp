#pragma once

#include "mp_maths.h"
typedef int32_t bool32;
// Ray definition: point(t) = origin + direction * t;
struct ray
{
    ray() {};
    ray(const vec3 &rayOrigin, const vec3 &rayDirection) {
        origin = rayOrigin;
        direction = rayDirection;
    }
    vec3 getPoint(float t){
        return origin + direction * t;
    }
    vec3 getPoint(float t) const {
        return origin + direction * t;
    }

    vec3 origin, direction;
};