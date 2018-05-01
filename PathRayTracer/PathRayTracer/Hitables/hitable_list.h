#pragma once

#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable_list() {}
	hitable_list(hitable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float tmix, float tmax, hit_record& rec) const;
	hitable **list;
	int list_size;
};

bool hitable_list::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
	hit_record tempRec;
	bool hitAnything = false;

	float closestHit = tmax;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, tmin, closestHit, tempRec))
		{
			hitAnything = true;
			closestHit = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

#endif