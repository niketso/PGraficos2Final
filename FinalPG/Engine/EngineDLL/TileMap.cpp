#include "TileMap.h"


TileMap::TileMap(const char * file, int wdwW, int wdwH , Renderer * render, Material *material) 
{
	LoadTileMap(file);

	
	scrollX = 0;

	levelH = 0;
	levelW = 0;


	this->render = render;
	this->material = material;

	
	LastCameraPos = CurrentCameraPos = DeltaCameraPos = glm::vec3(0, 0, 0);

	int tileW = 64;
	int tileH = 64;
	//+4 es las columnas
	viewW = (wdwW / tileW) + 4;                 
	viewH = (wdwH / tileH) + 4;

	levelX	= viewH;

	
	viewMatrix = new vector<vector<int>*>(viewW);
	for (int i = 0; i < viewW; i++)
		viewMatrix->at(i) = new vector<int>(viewH);

	tileMatrix = new vector<vector<Tile*>*>(viewW);
	for (int i = 0; i < viewW; i++)
		tileMatrix->at(i) = new vector<Tile*>(viewH);

	ChargeTile();
	LoadTiles();		
}

TileMap::~TileMap()
{
			
	for (int i = 0; i < levelW; i++) {
		delete levelMatrix->at(i);
	}
	delete levelMatrix;
	
	for (int i = 0; i < viewW; i++) {
		delete viewMatrix->at(i);
	}
	delete viewMatrix;

	for (int i = 0; i < viewW; i++) {
		for (int j = 0; j < viewH; j++) {
			delete tileMatrix->at(i)->at(j);
		}
		delete tileMatrix->at(i);
	}
}

void TileMap::LoadTileMap(const char * file)
{
	string buffer;
	ifstream tileFile(file);

	levelW = 1;
	levelH = 1;

	getline(tileFile, buffer);
	//el tipo de archivo .csv contiene -1 comas y 0.El for saltea la coma. 
	for (int i = 0; i < buffer.length(); i++) {
		if (buffer[i] == ',')
			levelW++;
	}
	while (getline(tileFile, buffer)) {
		levelH++;
	}
		
	tileFile.clear();
	//Esta linea hace que el archivo vuelva al principio
	tileFile.seekg(0, std::ios::beg);

	//vector de mundo.
	levelMatrix = new vector<vector<int>*>(levelW);

	for (int i = 0; i < levelW; i++) {
		levelMatrix->at(i) = new vector<int>(levelH);
	}

	if (tileFile.is_open()) {
		for (int i = 0; i < levelW; i++) {

			getline(tileFile, buffer);
			int levelW = 0;

			for (int j = 0; j < buffer.length(); j++) {
				
				switch (buffer[j]) {
				case '0':
					levelMatrix->at(i)->at(levelW) = 1;
					levelW++;
					break;

				case '1':
					levelMatrix->at(i)->at(levelW) = 0;
					levelW++;
					break;
				}
			}
		}
	}
	tileFile.close();
}


void TileMap::DrawTileMap()
{
	for (int w = 0; w < viewW; w++)
	{
		for (int h = 0; h < viewH; h++)
		{
			tileMatrix->at(w)->at(h)->Draw();
		}
	}
}

void TileMap::ChargeTile() 
{
	for (int w = 0; w < viewW; w++)
	{
		for (int h = 0; h < viewH; h++)
		{
			//set de datos.
			tileMatrix->at(w)->at(h) = new Tile(render, 1, 1);
			tileMatrix->at(w)->at(h)->SetMaterial(material);
			tileMatrix->at(w)->at(h)->AddTexture("Empty.bmp");
			tileMatrix->at(w)->at(h)->AddTexture("Land.bmp");
			
		}
	}
}

void TileMap::UpdateTileMap()
{
	int posx;
	int posy = 9;

	//Update X
	for (int i = 0; i < viewW; i++) {
		for (int j = 1; j < viewH; j++) {
			viewMatrix->at(i)->at(j - 1) = viewMatrix->at(i)->at(j);
		}
	}
	for (int i = 0; i < viewW; i++) {
		int pos = levelMatrix->at(i)->at(levelX);
		// update de posicion en y.
		viewMatrix->at(i)->at(viewH - 1) = pos;
	}
	//volver a dibujar
	posx = 12;
	for (int j = 0; j < viewW; j++) {
		if (viewMatrix->at(j)->at(viewH - 1) == 0) {
			tileMatrix->at(j)->at(lastPosX)->ChangeTexture(0);
					
		}
		if (viewMatrix->at(j)->at(viewH - 1) == 1) {
			tileMatrix->at(j)->at(lastPosX)->ChangeTexture(1);			
			
		}
		//cambiar la posicion.
		tileMatrix->at(j)->at(lastPosX)->SetPos(posx + render->GetCameraPos().x, posy, 0);
		posy -= 2;
	}
	if (lastPosX < viewH - 1) lastPosX++;
	else lastPosX = 0;
}

void TileMap::LoadTiles() {
	//posiciones iniciales de donde se va empezar a dibujar.
	
	int posx = -10;
	int posy = 9;

	lastPosX = 0;
	

	for (int w = 0; w < viewW; w++) {
		posx = -12;
		for (int h = 0; h < viewH; h++) {										
				viewMatrix->at(w)->at(h) = levelMatrix->at(w)->at(h);
				//Dependiendo del dato que nos llega se determina si es fondo o mapa.
				if (viewMatrix->at(w)->at(h) == 0) {
					tileMatrix->at(w)->at(h)->ChangeTexture(0);
					
				}
				if (viewMatrix->at(w)->at(h) == 1) {
					tileMatrix->at(w)->at(h)->ChangeTexture(1);
					
				}			
				posx += 2;
				tileMatrix->at(w)->at(h)->SetPos(posx, posy ,0);
		}
		posy -= 2;
	}
}

void TileMap::Update() 
{
	CurrentCameraPos = render->GetCameraPos();
	DeltaCameraPos = CurrentCameraPos - LastCameraPos;
	LastCameraPos = CurrentCameraPos;
	
	scrollX += DeltaCameraPos.x;
	if (scrollX >= 2) {
		if (levelX < levelW - 1)levelX++;
		UpdateTileMap();
		scrollX = 0;
	}
	else
		if (scrollX <= -2) {
			if (levelX < 0)levelX--;
			UpdateTileMap();
			scrollX = 0;
		}
	
}



