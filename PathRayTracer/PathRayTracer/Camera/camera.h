#pragma once

#ifndef CAMERAH
#define CAMERAH

#include "../stdafx.h"

struct screenCoords
{
public:
	vec3 lower_left_corner;
	vec3 vertical_coords;
	vec3 horizontal_coords;

	screenCoords(vec3 l_f_c, vec3 v_c, vec3 h_c) : lower_left_corner(l_f_c), vertical_coords(v_c), horizontal_coords(h_c) {};
};

class camera
{
public:
	camera() : screen(screenCoords(vec3(-2.0f, -1.0f, -1.0f), vec3(0.0f, 2.0f, 0.0f), vec3(4.0f, 0.0f, 0.0f))), origin(vec3(0.0f,0.0f,0.0f))
	{
	}

	ray get_ray(float u, float v) { return ray(origin,  screen.lower_left_corner +
														u * screen.horizontal_coords + 
														v * screen.vertical_coords -
														origin); };

	vec3 origin;
	screenCoords screen;
};


#endif