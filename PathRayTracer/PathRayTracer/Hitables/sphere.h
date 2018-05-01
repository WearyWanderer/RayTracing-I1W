#pragma once

#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable
{
public:
	sphere() {}
	sphere(vec3 cen, float r) : center(cen), radius(r) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
};


bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction()), b = dot(oc, r.direction()), c = dot(oc, oc) - radius*radius;

	float discriminant = b*b - a*c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin) //If t is within the interval
		{
			rec.t = temp; //Return hit record of t, point at t and normal at t
			rec.p = r.point_at_param(temp);
			rec.normal = (rec.p - center) / radius; //This is the calc for normal form a sphere, will not be same for all geometry
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp; //Return hit record of t, point at t and normal at t
			rec.p = r.point_at_param(temp);
			rec.normal = (rec.p - center) / radius; //This is the calc for normal form a sphere, will not be same for all geometry
			return true;
		}
	}
	return false;
}

#endif