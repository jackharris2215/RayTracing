#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    // constructor takes radius and center
    sphere(const vec3& center, double radius) : center(center), radius(std::fmax(0, radius)) {};
    
    // hit function, will override virtual hitable function in hittable class
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        // equation for sphere
        vec3 oc = center - r.origin();
        double a = r.direction().length_squared();
        double h = dot(r.direction(), oc);
        double c = oc.length_squared() - radius * radius;

        // discriminant
        double discriminant = h * h - a * c;
        if (discriminant < 0) {
            return false;
        }

        double sqrtd = std::sqrt(discriminant);

        auto root = (h - sqrtd) / a;
        if (root < ray_tmin || ray_tmax < root) {
            root = (h + sqrtd) / a;
            if (root < ray_tmin || ray_tmax < root) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    vec3 center;
    double radius;
};

#endif