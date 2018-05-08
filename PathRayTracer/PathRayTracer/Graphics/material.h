#pragma once

#include "../stdafx.h"
#include "../Hitables/hitable.h"

#ifndef MATERIALH
#define MATERIALH

class material 
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

#endif // !MATERIALH

#ifndef LAMBERTIANH
#define LAMBERTIANH

class lambertian : public material 
{
public:
	lambertian(const vec3& a) : albedo(a) {}

	vec3 albedo;

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 target = rec.p + rec.normal + ray::random_in_unit_sphere(); //project from position along normal with some random dir from unity sphere
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};

#endif // !LAMBERTIANH

#ifndef METALH
#define METALH

class metal 
{
public:

};

#endif // !METALH
