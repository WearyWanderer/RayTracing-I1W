#pragma once
#ifndef RAYH
#define RAYH

#include <random>

#include "vec3.h"

class ray
{
public:
	ray() {}
	ray(const vec3& a, const vec3& b) { A = a; B = b; }

	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_param(float t) const { return A + t*B; }

	vec3 A;
	vec3 B;

	static vec3 random_in_unit_sphere(std::default_random_engine *engine, std::uniform_real_distribution<float> randomFloat)
	{
		vec3 p;
		do 
		{
			p = 2.0f * vec3(randomFloat(*engine), randomFloat(*engine), randomFloat(*engine)) - vec3(1.0f, 1.0f, 1.0f);
		} while (p.squared_length() >= 1.0f);
		return p;
	}
};

#endif