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
    bool front_face;

    // set_face_normal function
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        //outward normal should be unit
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    // default implementation of the destructor
    virtual ~hittable() = default;

    // virtual hit function for hittable objects
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif 