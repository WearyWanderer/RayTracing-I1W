#pragma once

#include "../stdafx.h"
#include "../Hitables/hitable.h"

vec3 reflect(const vec3& v, const vec3& n) { return v - 2 * dot(v, n) * n; }

#ifndef MATERIALH
#define MATERIALH

class material 
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

	vec3 albedo;
};

#endif // !MATERIALH

#ifndef LAMBERTIANH
#define LAMBERTIANH

class lambertian : public material 
{
public:
	lambertian(const vec3& a) { albedo = a; }

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

class metal : public material
{
public:
	metal(const vec3& a) { albedo = a; }

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;

		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

#endif // !METALH
