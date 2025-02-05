#include <iostream>

#include "color.h"
#include "vec3.h"
#include "ray.h"

// does ray intersect with sphere
double hit_sphere(const vec3& center, double radius, const ray& r) {
    // a,b,c are extrapolated from equation for sphere centered at an arbitrary point
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;
    // using a,b,c... can solve for discriminant (# of solutions in quadratic equation)
    // if discriminant is greater than 0, there are two solutions (ray intersects sphere)

    if (discriminant < 0) {
        return -1.0;
    } else { ;
        return (h - std::sqrt(discriminant)) / a;
    }

}

color ray_color(const ray& r) {
    // create a sphere with radius, and give it the current ray
    double t = hit_sphere(vec3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return color(N.x()+1, N.y()+1, N.z()+1)*0.5;
    }
    // no sphere is hit, get y value and determine color
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0)*(1.0-a) + color(0.5, 0.7, 1.0)*a;
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // calculate image height
    int image_height = int(image_width / aspect_ratio);

    // viewport and camera settings
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = vec3(0, 0, 0);

    // viewport point at bottom left and top right
    auto viewport_w = vec3(viewport_width, 0, 0);
    auto viewport_h = vec3(0, -viewport_height, 0);

    // delta vectors for pixel increment
    auto pixel_delta_w = viewport_w / image_width;
    auto pixel_delta_h = viewport_h / image_height;

    // very upper left of viewport
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_w/2 - viewport_h/2;
    // center of top left pixel (pixel 0,0)
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_w + pixel_delta_h);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //iterate through pixels in image height and width
    for (int j = 0; j < image_height; j++) {
        // logging progress
        // std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            // get pixel center of nth pixel
            vec3 pixel_center = pixel00_loc + (i * pixel_delta_w) + (j * pixel_delta_h);
            // find ray direction relative to camera center
            vec3 ray_direction = pixel_center - camera_center;
            // create new ray object starting at camera center
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r); 
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}