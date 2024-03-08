#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class ray {
    public:
        ray() {}
        //constructor
        ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction), tm(0)
        {}
        // time is added to ray class
        ray(const point3& origin, const vec3& direction, double time)
            : orig(origin), dir(direction), tm(time)
        {}
        //getters
        point3 origin() const  { return orig; }
        vec3 direction() const { return dir; }
        double time() const    { return tm; }
        //returns point at parameter t
        point3 at(double t) const {
            return orig + t*dir;
        }

    public:
        point3 orig; //origin
        vec3 dir; //direction
        double tm; //time
};

#endif
