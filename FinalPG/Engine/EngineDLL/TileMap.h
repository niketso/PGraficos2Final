#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Exports.h"
#include "Tile.h"
#include "CollisionManager.h"
using namespace std;


class ENGINEDLL_API TileMap
{
private:
	Sprite * layers;
	Material * material;
	Renderer * render;

	vector<vector<int>*> * viewMatrix;
	vector<vector<int>*> * levelMatrix;
	vector<vector<Tile*>*> * tileMatrix;
	//camera
	glm::vec3 LastCameraPos;
	glm::vec3 CurrentCameraPos;
	glm::vec3 DeltaCameraPos;

	int levelH;
	int levelW;

	int levelX;

	int viewH;
	int viewW;

	int lastPosX;
	int scrollX;
	
	
	

	
public:
	/*
	pasos:
	1-Recibir archivo de tilemap e interpretarlo.
	2-Cargar archivo en vector q almacena el tilemap entero.
	3-cargar el vector de vista con el vector de Tilemap.
	4-Mostrar el vector de vista.
	5-poder actiualizar el vector de vista frame a frame.

	*/
	TileMap(const char * file,int wdwW,int wdwH,Renderer * render,Material * material);
	~TileMap();

	void ChargeTile();
	void DrawTileMap();
	void UpdateTileMap();
	void LoadTileMap(const char * file);
	void LoadTiles();
	void Update();
};

