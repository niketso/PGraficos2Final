#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Importer.h"
#include "Animation.h"

class ENGINEDLL_API Sprite:public Shape
{
protected:
	BMPheader header;
	const char* file;
	bool shouldDisposeTexture;
	unsigned int textureBufferId;
	unsigned int UVBufferId;
	float *txtreUVvertex;
	int textreVtxCount;

	Animation  *anim;
	
	
public:
	Sprite(Renderer * render, int columns, int rows);
	~Sprite();
	void SetTextureVertices(float* vertices, int count);
	void LoadTexture(const char* name);
	void DisposeTexture();
	void Draw() override;
	void DrawMesh(int drawType) override;
	void SetAnimation(int initF, int finalF, float timePerF);
	void UpdateAnimation(float deltaTime);
};

