#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Headers\stb_image_write.h"

#include "Hitables\hitable_list.h"
#include "Hitables\sphere.h"
#include "Camera\camera.h"

using namespace std;

bool WriteBMPFile(const int w,const int h, int comp, const void* data)
{	
	if (stbi_write_bmp("example.bmp", w, h, 3, data) == 0)
		return false;

	return true;
}

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0f, FLT_MAX, rec))
	{
		return 0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1); //Normalise to 0 to 1 range, from -1 to -1
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	int w = 800, h = 400, samplesPerPixel = 100;

#pragma region Camera Setup
	camera cam;
#pragma endregion

#pragma region World Setup
	hitable *list[2]; //create array for our hitable_list
	list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
	list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);

	hitable *world = new hitable_list(list, 2); //create our list which fully represents our 'world' of hitable objects
#pragma endregion

#pragma region Random Setup
	default_random_engine randEngine;
	uniform_real_distribution<float> randomFloat(0.0f,1.0f);
#pragma endregion

	unsigned char* colDataRaw = new unsigned char[(w*h) * 3];
	int pix = 0;
	for (int j = h - 1; j >= 0; j--)
	{
		for (int i = 0; i < w; i++)
		{
			vec3 pixelCol(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < samplesPerPixel; s++)
			{
				float u = (float)(i + randomFloat(randEngine)) / (float)w, v = (float)(j + randomFloat(randEngine)) / (float)h;
				ray r = cam.get_ray(u, v);
				pixelCol += color(r, world);
			}
			pixelCol /= samplesPerPixel;

			int ir = int(255.99f*pixelCol[0]);
			int ig = int(255.99f*pixelCol[1]);
			int ib = int(255.99f*pixelCol[2]);

			colDataRaw[pix] = ir;
			colDataRaw[pix + 1] = ig;
			colDataRaw[pix + 2] = ib;
			pix += 3;
		}
	}

	WriteBMPFile(w, h, 3, &colDataRaw[0]);

	cout << "Press Enter key to close" << endl;
	cin.get();
    return 0;
}
