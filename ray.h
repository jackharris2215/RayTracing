#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    // empty constructor 
    ray() {}

    // constructor with origin and direction, set orig and dir
    ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    // accessor methods, modify
    const vec3& origin() const  { return orig; }
    const vec3& direction() const { return dir; }

    // return point at t along ray
    vec3 at(double t) const {
        return orig + t*dir;
    }

private:
    // declare private variables
    vec3 orig;
    vec3 dir;
};

#endif