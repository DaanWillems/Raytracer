#pragma once
#include "material.h"

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		float r1 = rand() / (RAND_MAX + 1.0);
		float r2 = rand() / (RAND_MAX + 1.0);
		float r3 = rand() / (RAND_MAX + 1.0);
		p = 2.0*vec3(r1, r2, r3) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

class lambertian: public material
{
public:
	lambertian(const vec3& a): albedo(a) {}
	virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const override
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};
