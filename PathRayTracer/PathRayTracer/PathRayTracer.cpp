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

bool WriteBMPFile(const char* filename, const int w,const int h, int comp, const void* data)
{	
	if (stbi_write_bmp(filename, w, h, 3, data) == 0)
		return false;

	return true;
}

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + ray::random_in_unit_sphere(); //Get a random ray bounce target
		return 0.5f * color(ray(rec.p, target-rec.p), world); //Normalise to 0 to 1 range, from -1 to -1
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

vec3 colorNormals(const ray& r, hitable *world)
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
	int w = 1600, h = 800, samplesPerPixel = 100;

#pragma region Camera Setup
	camera cam;
#pragma endregion

#pragma region World Setup
	hitable *list[3]; //create array for our hitable_list
	list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
	list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);
	list[2] = new sphere(vec3(1.0f, 0.0f, -1.5f), 0.5f);

	hitable *world = new hitable_list(list, 3); //create our list which fully represents our 'world' of hitable objects
#pragma endregion

	int byteCount = (w*h) * 3;
	int progressCount = 0;
	int lastProgressCount = 0;
	unsigned char* colDataRaw = new unsigned char[byteCount];
	int index = 0;

	for (int j = h - 1; j >= 0; j--)
	{
		for (int i = 0; i < w; i++)
		{
			vec3 pixelCol(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < samplesPerPixel; s++)
			{
				float u = (float)(i + RandomModule::instance().GetRandomUnitFloat()) / (float)w, v = (float)(j + RandomModule::instance().GetRandomUnitFloat()) / (float)h;
				ray r = cam.get_ray(u, v);
				pixelCol += color(r, world);
			}
			pixelCol /= samplesPerPixel;
			pixelCol = vec3(sqrt(pixelCol[0]), sqrt(pixelCol[1]), sqrt(pixelCol[2]));
			int ir = int(255.99f*pixelCol[0]);
			int ig = int(255.99f*pixelCol[1]);
			int ib = int(255.99f*pixelCol[2]);

			colDataRaw[index] = ir;
			colDataRaw[index + 1] = ig;
			colDataRaw[index + 2] = ib;
			index += 3;
			progressCount = std::floor((index * 100.0f) / byteCount);
			if (progressCount > lastProgressCount)
			{
				lastProgressCount = progressCount;
				cout << "Path-Tracing Progress: " << progressCount << endl;
			}
		}
	}

	WriteBMPFile("earlydiffuse.bmp", w, h, 3, &colDataRaw[0]);

	cout << "Press Enter key to close" << endl;
	cin.get();
    return 0;
}
