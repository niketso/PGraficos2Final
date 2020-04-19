#include "Importer.h"



BMPheader Importer::LoadBMP(const char * BMPname) 
{
	unsigned char header[54]; 
	
	FILE * file;
	 fopen_s(&file,BMPname, "rb");
	 BMPheader hed;

	if (RightBMPFormat(header, file))
	{
		hed.dataPos = *(int*)&(header[0x0A]);
		hed.imageSize = *(int*)&(header[0x22]);
		hed.width = *(int*)&(header[0x12]);
		hed.height = *(int*)&(header[0x16]);
		
	}

	if (hed.imageSize == 0)    hed.imageSize = hed.width * hed.height * 3;
	if (hed.dataPos == 0)      hed.dataPos = 54;

	hed.data = new unsigned char[hed.imageSize];

	fseek(file, hed.dataPos, 0);
	fread(hed.data, 1, hed.imageSize, file);
	fclose(file);

	return hed;
	
}

bool Importer::RightBMPFormat(unsigned char  BMPheader[], FILE * BMPfile)
{	
	if (!BMPfile)
	{
		printf("Image could not be opened\n");
		return 0;
	}

	if (fread(BMPheader, 1, 54, BMPfile) != 54)
	{ 
		printf("Not a correct BMP file\n");
		return false;
	}

	if (BMPheader[0] != 'B' || BMPheader[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}


}
