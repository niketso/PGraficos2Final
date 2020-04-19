#include "Tile.h"

Tile::Tile(Renderer * render, int columns, int rows):Sprite (render,columns,rows)
{
	textures = new vector<int>();
}


Tile::~Tile()
{
	delete textures;
}

void Tile::AddTexture(const char * bmpname)
{
	header = Importer::LoadBMP(bmpname);	
	textureBufferId = render->GenTextureBuffer(header.width, header.height, header.data);
	material->BindTexture("myTextureSampler", textureBufferId);
	textures->push_back(textureBufferId);
	
}

void Tile::ChangeTexture(int i) 
{
	textureBufferId = textures->at(i);
	render->UpdateTexture(textures->at(i));
	material->BindTexture("myTextureSampler", textureBufferId);
	
}




