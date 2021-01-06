#pragma once

#include "hitable.hpp"

inline float randFloat();
vec3 randomInUnitSphere();

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2.0f * vec3Dot(v, n) * n;
}

bool32 refract(const vec3 &v, const vec3 &n, float niOverNt, vec3 &refracted)
{
    vec3 uv = normalise(v);
    float dt = vec3Dot(uv, n);
    float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);
    if(discriminant > 0){
        refracted = niOverNt * (uv - n * dt) - n * sqrtf(discriminant);
        return true;
    }
    return false;
}

float schlick(float cosine, float refractionIndex)
{
    float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
    r0 *= r0;
    return r0 + (1.0f - r0) * powf(1.0f - cosine, 5);
}

struct material
{
    virtual bool32 scatter(const ray &rayIn, const hitInfo &info, vec3 &attenuation, ray &scattered) const = 0;
};

struct lambertian : material
{
    lambertian(const vec3 &a) : albedo(a) {};
    virtual bool32 scatter(const ray &rayIn, const hitInfo &info, vec3 &attenuation, ray &scattered) const{
        vec3 target = info.normal + randomInUnitSphere();
        scattered = ray(info.point, target);
        attenuation = albedo;
        return true;
    }
    vec3 albedo;
};

struct metal : material
{
    metal(const vec3 &a, float f) : albedo(a), fuzz(f) {};
    virtual bool32 scatter(const ray &rayIn, const hitInfo &info, vec3 &attenuation, ray &scattered) const{
        vec3 reflected = reflect(normalise(rayIn.direction), info.normal);
        scattered = ray(info.point, reflected + fuzz * randomInUnitSphere());
        attenuation = albedo;
        return vec3Dot(scattered.direction, info.normal) > 0;
    }
    vec3 albedo;
    float fuzz;
};

struct dielectric : material
{
    dielectric(float ri) : refractionIndex(ri) {};
    virtual bool32 scatter(const ray &rayIn, const hitInfo &info, vec3 &attenuation, ray &scattered) const{
        vec3 reflected = reflect(rayIn.direction, info.normal);
        attenuation = vec3{1.0f, 1.0f, 1.0f};

        vec3 outwardNormal;
        vec3 refracted;
        float niOverNt;
        float reflectProb;
        float cosine;
        if(vec3Dot(rayIn.direction, info.normal) > 0){
            outwardNormal = -info.normal;
            niOverNt = refractionIndex;
            cosine = refractionIndex * vec3Dot(rayIn.direction, info.normal) / vec3Length(rayIn.direction);
        }
        else{
            outwardNormal = info.normal;
            niOverNt = 1.0f / refractionIndex;
            cosine = -vec3Dot(rayIn.direction, info.normal) / vec3Length(rayIn.direction);
        }
        if(refract(rayIn.direction, outwardNormal, niOverNt, refracted)){
            reflectProb = schlick(cosine, refractionIndex);
        }
        else{
            reflectProb = 1.0f;
        }
        if(randFloat() < reflectProb)
            scattered = ray(info.point, reflected);
        else
            scattered = ray(info.point, refracted);
        return true;
    }
    float refractionIndex;
};