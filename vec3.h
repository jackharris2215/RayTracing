#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

// declare vec3 class
class vec3 {
public:

    // initialize empty array of size 3
    double e[3];

    // constructors, empty and given values
    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // accessor methods, get individual values
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // unary minus operator, create new vec3 object with negated values
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    // subscript operators, get doulbe value and get refernce to double value
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    // ----- METHODS -----

    // increment vector by another vector and return reference
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    // multpiply vector by scalar and return reference
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // divide vector by scalar by using prevous multiply method
    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    // return length of vector (sqrt of sum of squares)
    double length() const {
        // sqrt from cmath
        return std::sqrt(length_squared());
    }

    // return squared length of vector
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

// create point3 alias
// using point3 = vec3;


// Vector Utility Functions

// inline function, << operator, takes in ostream ref and vec3 ref and returns ostream ref
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// vec3 addition, takes two vec3 refs and returns new vec3 object
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// vector subtraction
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// vector multiplication
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// vector multiplaction by double
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

// allowing swapping of parameters, utilizing above multiplaction function
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

// vector division by double, utilizing multiplaction function
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// dot product
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// cross product
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// return new unit vector
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif