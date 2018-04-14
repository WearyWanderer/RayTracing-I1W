// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "Headers\targetver.h"

#include <stdio.h>
#include <tchar.h>

//Define and include implementation for image file type decode/encode
#define STB_IMAGE_IMPLEMENTATION
#include "Headers\stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Headers\stb_image_write.h"