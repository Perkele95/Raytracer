#pragma once

#include "hitable.hpp"

struct sphere : hitable
{
    sphere() {};
    sphere(vec3 cen, float r) : centre(cen), radius(r) {};
    virtual bool32 hit(const ray &r, float tMin, float tMax, hitInfo &info) const;

    vec3 centre;
    float radius;
};

bool32 sphere::hit(const ray &r, float tMin, float tMax, hitInfo &info) const{
    vec3 oc = r.origin - centre;
    float a = vec3Dot(r.direction, r.direction);
    float b = vec3Dot(oc, r.direction);
    float c = vec3Dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if(discriminant > 0){
        float discriminantSqrt = sqrtf(discriminant);
        float temp = (-b - discriminantSqrt) / a;
        if(temp < tMax && temp > tMin){
            info.t = temp;
            info.point = r.getPoint(temp);
            info.normal = (info.point - centre) / radius;
            return true;
        }
        temp = (-b + discriminantSqrt) / a;
        if(temp < tMax && temp > tMin){
            info.t = temp;
            info.point = r.getPoint(temp);
            info.normal = (info.point - centre) / radius;
            return true;
        }
    }
    return false;
}