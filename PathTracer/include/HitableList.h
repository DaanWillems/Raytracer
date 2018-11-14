#pragma once

#include "Hitable.h"

class HitableList : public Hitable {
public:
	HitableList() = default;
	HitableList(Hitable **l, int n) { list = l; listSize = n; }
	bool hit(const ray& r, float t_min, float t_max, hitRecord& rec) const override;
	Hitable** list;
	int listSize;
};

bool HitableList::hit(const ray& r, float t_min, float t_max, hitRecord& rec) const {
	hitRecord tempRec;
	bool hit = false;
	double closest = t_max;

	for (int i = 0; i < listSize; i++) {
		if (list[i]->hit(r, t_min, closest, tempRec)) {
			hit = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}
	return hit;
}