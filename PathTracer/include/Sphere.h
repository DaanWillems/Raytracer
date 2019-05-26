#pragma once

#include "Hitable.h"

class Sphere : public Hitable {
public:
	Sphere() = default;
	Sphere(vec3 cen, float r, material* mat) : center{ cen }, radius{ r }, mat_ptr{ mat }  {};
	bool hit(const ray& r, float t_min, float t_max, hitRecord& rec) const override;
	vec3 center;
	float radius;
	material *mat_ptr;
};

bool Sphere::hit(const ray& r, float t_min, float t_max, hitRecord& rec) const {
	// vec3 rd = unit_vector(r.direction);
	// vec3 ro = r.origin;
	//
	// float t = dot((center - ro), rd);
	// vec3 p = ro + rd * t;
	// vec3 l = center - p;
	// float y = l.length();
	// float x = sqrt((radius*radius) - (y * y));
	// float t1 = t - x;
	// if (y < radius && t1 > t_min && t < t_max) {
	// 	rec.t = t - x;
	// 	rec.p = r.pointAtParameter(rec.t);
	// 	rec.normal = (rec.p - center)/radius;
	// 	rec.mat_ptr = mat_ptr;
	// 	return true;
	// }
	// return false;
	vec3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = dot(oc, r.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if(temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}