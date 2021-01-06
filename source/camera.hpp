#pragma once

#include "ray.hpp"

constexpr float PI32 = 3.14159265359f;

vec3 randomUnitInDisk();

struct camera
{
    camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fov, float aspecRatio, float aperture, float focusDist){
        lensRadius = aperture / 2.0f;
        float theta = fov * PI32 / 180.0f;
        float halfHeight = tanf(theta / 2.0f);
        float halfWidth = aspecRatio * halfHeight;
        origin = lookFrom;
        w = normalise(lookFrom - lookAt);
        u = normalise(vec3Cross(up, w));
        v = vec3Cross(w, u);
        lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
        horizontal = 2.0f * halfWidth * focusDist * u;
        vertical = 2.0f * halfHeight * focusDist * v;
    }
    ray getRay(float s, float t){
        vec3 rd = lensRadius * randomUnitInDisk();
        vec3 offset = u * rd.x + v * rd.y;
        return ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
    }
    vec3 origin;
    vec3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lensRadius;
};