#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Material.h"
#include <vector>
class ENGINEDLL_API Tile : public Sprite
{
private:
	vector<int> * textures;
	BMPheader header;
public:
	Tile(Renderer * render,int columns, int rows);
	void AddTexture(const char * bmpname);
	void ChangeTexture(int i);
	~Tile();

};

