#pragma once

#include "ray.hpp"

struct hitInfo
{
    float t;
    vec3 point;
    vec3 normal;
};

struct hitable
{
    virtual bool32 hit(const ray &r, float tMin, float tMax, hitInfo &info) const = 0;
};