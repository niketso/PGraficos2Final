#pragma once
#include "Exports.h"

#include <stdio.h>
#include <stdlib.h>


struct BMPheader
{
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char  * data;
};

static class ENGINEDLL_API Importer
{
	
public:
	
	static BMPheader LoadBMP(const char* BMPname);
	static bool RightBMPFormat(unsigned char  BMPheader[], FILE * BMPfile);
};

