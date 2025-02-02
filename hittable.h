#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
public:
    // point
    vec3 p;
    // direction
    vec3 normal;
    double t;
};

class hittable {
public:
    // default implementation of the destructor
    virtual ~hittable() = default;

    // virtual hit function for hittable objects
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif