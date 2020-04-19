#pragma once
#include "Exports.h"
#include <vector>
using namespace std;
class ENGINEDLL_API SpriteSheet
{
private:	
	float *uvArrays;
	vector<float*> * uvVector;
	int textureH;
	int textureW;

public:
	SpriteSheet(int columns, int rows);
	~SpriteSheet();
	float* GetFrame(int index);
	int GetSize();
	
};

