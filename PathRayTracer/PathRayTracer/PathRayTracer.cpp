#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Headers\stb_image_write.h"

using namespace std;

void WriteToBaseImageFilePPM(int width, int height, const char* filename)
{
	ofstream fileStream;
	fileStream.open(filename);

	fileStream << "P3\n" << width << " " << height << "\n255\n";

	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			vec3 col = vec3(float(i) / float(width), float(j) / float(height), 0.2f);

			int ir = int(255.99f*col[0]);
			int ig = int(255.99f*col[1]);
			int ib = int(255.99f*col[2]);
			fileStream << ir << " " << ig << " " << ib << "\n";
		}
	}

	fileStream.close();
}

bool WriteBMPFile(const int w,const int h, int comp, const void* data)
{	
	if (stbi_write_bmp("example.bmp", w, h, 3, data) == 0)
		return false;

	return true;
}

vec3 color(const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

struct screenCoords
{
public:
	vec3 lower_left_corner;
	vec3 vertical_coords;
	vec3 horizontal_coords;

	screenCoords(vec3 l_f_c,vec3 v_c,vec3 h_c) : lower_left_corner(l_f_c), vertical_coords(v_c), horizontal_coords(h_c){};
};

int main()
{
	int w = 200, h = 100;

	screenCoords screen = screenCoords(vec3(-2.0f, -1.0f, -1.0f), vec3(0.0f,2.0f,0.0f), vec3(4.0f,0.0f,0.0f));
	vec3 camera_origin = vec3(0.0f, 0.0f, 0.0f);

	unsigned char* colDataRaw = new unsigned char[(w*h) * 3];
	int pix = 0;
	for (int j = h - 1; j >= 0; j--)
	{
		for (int i = 0; i < w; i++)
		{
			float u = (float)i / (float)w, v = (float)j / (float)h;
			ray r(camera_origin, screen.lower_left_corner + u * screen.horizontal_coords + v * screen.vertical_coords);
			
			vec3 pixelCol = color(r);

			int ir = int(255.99f*pixelCol[0]);
			int ig = int(255.99f*pixelCol[1]);
			int ib = int(255.99f*pixelCol[2]);

			colDataRaw[pix] = ir;
			colDataRaw[pix + 1] = ig;
			colDataRaw[pix + 2] = ib;
			pix += 3;
		}
	}

	//WriteToBaseImageFilePPM(xSize, ySize, "example.ppm");
	WriteBMPFile(w, h, 3, &colDataRaw[0]);

	cout << "Press Enter key to close" << endl;
	cin.get();
    return 0;
}
