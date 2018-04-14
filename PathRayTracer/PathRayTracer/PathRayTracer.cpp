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

bool WritePNGFile(const int w,const int h, int comp, const void* data)
{	
	std::vector<vec3> colData;
	colData.resize(w * h);

	int pixel = 0;
	for (int j = h - 1; j >= h; j--)
	{
		for (int i = 0; i < w; i++)
		{
			vec3 col = vec3(float(i) / float(w), float(j) / float(h), 0.2f);

			int ir = int(255.99f*col[0]);
			int ig = int(255.99f*col[1]);
			int ib = int(255.99f*col[2]);
			colData[pixel] = vec3(ir, ig, ib);
			pixel++;
		}
	}


	if (stbi_write_bmp("example2.bmp", w, h, 3, &colData) != 0)
		return false;

	return true;
}

int main()
{
	int xSize = 200, ySize = 100;

	//WriteToBaseImageFilePPM(xSize, ySize, "example.ppm");
	WritePNGFile(xSize, ySize, 3, nullptr);

	cout << "Press Enter key to close" << endl;
	cin.get();
    return 0;
}
