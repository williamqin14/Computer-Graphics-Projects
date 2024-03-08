#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"


struct hit_record;


class material {
    public:
        // Returns true if the ray is scattered
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;
};


class lambertian : public material {
    public:
        // albedo is the color of the object
        lambertian(const color& a) : albedo(a) {}

        // Returns true if the ray is scattered
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    public:
        color albedo;
};


class metal : public material {
    public:
        // specify the color of the object and the fuzziness of the reflection
        metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        // calculate the reflected ray and return true if the ray is scattered
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color albedo;
        double fuzz;
};


// Schlick's approximation for reflectance.
// See https://en.wikipedia.org/wiki/Schlick%27s_approximation
double reflectance(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

class dielectric : public material {
    public:
        dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            attenuation = color(1.0, 1.0, 1.0); // no attenuation
            double refraction_ratio = rec.front_face ? (1.0/ir) : ir; // Snell's law

            vec3 unit_direction = unit_vector(r_in.direction()); // unit vector of the ray
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0); // cos(theta) = dot(-unit_direction, rec.normal)
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta); // sin(theta)^2 + cos(theta)^2 = 1

            bool cannot_refract = refraction_ratio * sin_theta > 1.0; // total internal reflection
            vec3 direction; 
            // if cannot refract or reflectance > random_double(), reflect the ray
            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else // refract the ray
                direction = refract(unit_direction, rec.normal, refraction_ratio);
            // create the scattered ray
            scattered = ray(rec.p, direction);
            return true;
        }

    public:
        double ir; // Index of Refraction

    private:
        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
};


#endif
