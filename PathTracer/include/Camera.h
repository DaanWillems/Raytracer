#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "ray.h"

class Camera {
public:
	Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
		vec3 u, v, w;

		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;

		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);


		lowerLeftCorner = origin - half_width * u - half_height * v - w;
		horizontal = 2 * half_width*u;
		vertical = 2 * half_height*v;
	}

	ray getRay(float u, float v) {
		return ray(origin, lowerLeftCorner + (u * horizontal) + (v * vertical-origin));
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};