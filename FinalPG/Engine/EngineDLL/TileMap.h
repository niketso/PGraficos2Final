#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Exports.h"
#include "Tile.h"
#include "Sprite.h"
#include "CollisionManager.h"
using namespace std;

/*
	pasos:
	1-Recibir archivo de tilemap e interpretarlo.
	2-Cargar archivo en vector q almacena el tilemap entero.
	3-cargar el vector de vista con el vector de Tilemap.
	4-Mostrar el vector de vista.
	5-poder actiualizar el vector de vista frame a frame.
*/
struct TileColliderData {
	float positionX;
	float width;
	float positionY;
	float height;
	int layer;
};

class ENGINEDLL_API TileMap : public Sprite
{
private:

	const char* filename;
	int tilemapWidth;
	int tilemapHeight;
	int cantUVvertex;
	float cantTilesX;
	float cantTilesY;
	float tileOffset;
	float tileSize;

	//cuantos tipos de tiles tengo
	vector<int>* mapIds;
	//tiles con colision
	vector<int> * tilesWithCollider;
	//posicion de tiles
	vector<float> vertexPos;

	vector<TileColliderData>* tilesColliderData;
public:
	TileMap(Renderer* _renderer, float _tilemapWidth, float _tilemapHeight, const char* _filename,
		int _cantTilesX, int _cantTilesY, float _tileOffset, float _tileSize, vector<int>* _colliderTiles);

	~TileMap();
	void Draw() override;
	void DrawMesh(int _drawType);
	void SetTextures(float* vertex, int cant);
	void LoadTexture(const char* name);
	void LoadUVs();
	void LoadMapIDs(const char* file);
	void SetTilemapVertex(float* vertex, int cant);
	int NextTileIsCollider(float _playerTranslationX, float _playerTranslationY, float _playerHight, float _playerWidht);

	

};