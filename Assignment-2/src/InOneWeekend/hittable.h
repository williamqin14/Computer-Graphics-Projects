#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class material;

// stores the information about the point of intersection
struct hit_record {
    point3 p; // point of intersection
    vec3 normal; // normal of the intersection
    shared_ptr<material> mat_ptr; // material of the intersection
    double t; // time of the intersection
    bool front_face; // true if the ray is outside the object
    
    // set the normal of the intersection
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};


class hittable {
    public:
        // calculate the intersection of the ray and the object
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif
