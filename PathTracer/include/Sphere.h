#pragma once

#include "Hitable.h"

class Sphere : public Hitable {
public:
	Sphere() = default;
	Sphere(vec3 cen, float r) : center{ cen }, radius{ r } {};
	bool hit(const ray& r, float t_min, float t_max, hitRecord& rec) const override;
	vec3 center;
	float radius;
};

bool Sphere::hit(const ray& r, float t_min, float t_max, hitRecord& rec) const {
	vec3 rd = unit_vector(r.direction);
	vec3 ro = r.origin;

	float t = dot((center - ro), rd);
	vec3 p = ro + rd * t;
	vec3 l = center - p;
	float y = l.length();
	float x = sqrt((radius*radius) - (y * y));
	float t1 = t - x;
	if (y < radius && t1 > t_min && t < t_max) {
		rec.t = t - x;
		rec.p = r.pointAtParameter(rec.t);
		rec.normal = (rec.p - center)/radius;
		return true;
	}
	return false;
}