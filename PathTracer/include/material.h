#pragma once

#include "ray.h"
#include "Hitable.h"

class material
{
public:
	virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};
