#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"

#include "hittable.h"


class sphere : public hittable {
    public:
        sphere() {}
        //
        sphere(point3 cen, double r, shared_ptr<material> m)
            : center(cen), radius(r), mat_ptr(m) {};
        // calculate the intersection of the ray and the sphere
        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;
    // define center, radius, and material
    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};


bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center; 
    auto a = r.direction().length_squared(); // dot product of ray direction and itself
    auto half_b = dot(oc, r.direction()); // dot product of ray origin and ray direction
    auto c = oc.length_squared() - radius*radius; // dot product of ray origin and itself

    auto discriminant = half_b*half_b - a*c; // discriminant of the quadratic equation
    if (discriminant < 0) return false; // no intersection
    auto sqrtd = sqrt(discriminant); // square root of the discriminant

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root; // set the time of the intersection
    rec.p = r.at(rec.t); // set the point of the intersection
    vec3 outward_normal = (rec.p - center) / radius; // set the normal of the intersection
    rec.set_face_normal(r, outward_normal); // set the normal of the intersection
    rec.mat_ptr = mat_ptr; // set the material of the intersection

    return true;
}


#endif
