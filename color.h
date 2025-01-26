#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class color {
public:
    double e[3];

    color(double r, double g, double b){
        e[0] = r;
        e[1] = g;
        e[2] = b;
    }

    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    double r() const { return e[0]; }
    double g() const { return e[1]; }
    double b() const { return e[2]; }

    color& operator*(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
};

inline color operator+(const color& u, const color& v) {
    return color(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

// defining function in header because it will only be referenced by one file
void write_color(std::ostream& out, const color& pixel_color) {

    // translate 0-1 to 0-255 (.999 to avoid rounding errors)
    int rbyte = int(255.999 * pixel_color.r());
    int gbyte = int(255.999 * pixel_color.g());
    int bbyte = int(255.999 * pixel_color.b());

    // push to output stream
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif