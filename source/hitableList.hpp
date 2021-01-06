#pragma once

#include "hitable.hpp"

struct hitableList : hitable
{
    hitableList() {};
    hitableList(hitable **l, int32_t size) : list(l), listSize(size) {};
    virtual bool32 hit(const ray &r, float tMin, float tMax, hitInfo &info) const;

    hitable **list;
    int32_t listSize;
};

bool32 hitableList::hit(const ray &r, float tMin, float tMax, hitInfo &info) const{
    hitInfo tempInfo;
    bool32 result = false;
    float closestSoFar = tMax;
    for(int32_t i = 0; i < listSize; i++){
        if(list[i]->hit(r, tMin, closestSoFar, tempInfo)){
            result = true;
            closestSoFar = tempInfo.t;
            info = tempInfo;
        }
    }
    return result;
}