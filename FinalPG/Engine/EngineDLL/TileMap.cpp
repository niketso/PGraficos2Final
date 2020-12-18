#include "TileMap.h"
//Cargar el tilemap.
//Crear tilemap entero.
//crear buffer que mustre solo la la parte del mapa que se necesita en pantalla.

TileMap::TileMap(Renderer* _renderer, float _tilemapWidth, float _tilemapHeight, const char* _filename,
	int _cantTilesX, int _cantTilesY, float _tileOffset, float _tileSize,
	vector<int>* _colliderTiles) : Sprite(_renderer) {

	filename = _filename;
	tilemapWidth = _tilemapWidth;     //tamño del tilemap ancho
	tilemapHeight = _tilemapHeight;	  //tamño del tilemap alto
	cantTilesX = _cantTilesX;			//cant de tiles textura en x
	cantTilesY = _cantTilesY;			//cant de tiles en textura en y
	tileOffset = _tileOffset;			//Cargar el tile desde una mejor posicion
	tileSize = _tileSize;				//tamaño del cada tile
	vtxCount = _tilemapWidth * _tilemapHeight * 4 * 3;    //
	cantUVvertex = _tilemapWidth * _tilemapHeight * 4 * 2 ; //


	mapIds = new vector<int>();
	LoadMapIDs(_filename);	//carga los numeros.
	tilesWithCollider = _colliderTiles; //cargo los tiles que tienen colisiones
	tilesColliderData = new vector<TileColliderData>(); //
	int aux = 0;

	//se calcula la posicion del los vertices con respecto al offset.
	for (int i = 0; i < _tilemapHeight; i++) {
		for (int j = 0; j < _tilemapWidth; j++)
		{

			int col = j * tileSize;	 						
			int row = i * tileSize;
			//xyz
			
			vertexPos.push_back(-tileOffset + col);			
			vertexPos.push_back(tileOffset - row);
			vertexPos.push_back(0.0f);
			
			vertexPos.push_back(-tileOffset + col);
			vertexPos.push_back((tileOffset - tileSize) - row);
			vertexPos.push_back(0.0f);
			
			vertexPos.push_back(-(tileOffset - tileSize) + col);
			vertexPos.push_back((tileOffset - tileSize) - row);
			vertexPos.push_back(0.0f);
			
			vertexPos.push_back(-(tileOffset - tileSize) + col);
			vertexPos.push_back(tileOffset - row);
			vertexPos.push_back(0.0f);

			
			//cargas la info del tile que tiene collider
			if (tilesWithCollider != NULL )
			{
				for (int k = 0; k < tilesWithCollider->size(); k++)
				{
					if (mapIds->at(aux) == tilesWithCollider->at(k))
					{
						TileColliderData colliderAux;

						colliderAux.positionY = (tileOffset - row) - tileSize;
						colliderAux.positionX = (-tileOffset + col);
						colliderAux.layer = k;
						colliderAux.height = tileSize;
						colliderAux.width = tileSize;
						tilesColliderData->push_back(colliderAux);
					}
				}


			}			
			aux++;
		}
	}
	//	Guardas la direccion del array de vertices
	float* p = &vertexPos[0];
	
	txtreUVvertex = new float[cantUVvertex];

	LoadUVs();

	SetTilemapVertex(p, vtxCount);

	SetTextures(txtreUVvertex, cantUVvertex);
}

TileMap::~TileMap() {

}

void TileMap::SetTextures(float* vertex, int cant) {

	UVBufferId = render->GenBuffer(vertex, sizeof(float)* cant);
}

void TileMap::LoadTexture(const char* name) {
	header = Importer::LoadBMP(name);
	textureBufferId = render->GenTextureBuffer(header.width, header.height, header.data);
	material->BindTexture("myTextureSampler",textureBufferId);
}

void TileMap::DrawMesh(int typeDraw) {
	render->LoadIdentityMatrix();
	render->SetWorldMatrix(WorldMatrix);

	
	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty("WVP", render->GetWvp());
		material->BindTexture("myTextureSampler", textureBufferId);
	}

	render->BeginDraw(0);
	render->BindBuffer(bufferId, 0,3);
	render->BeginDraw(1);
	render->BindBuffer(UVBufferId, 1,2);
	render->DrawBuffer(vtxCount, typeDraw);
	render->EndDraw(0);
	render->EndDraw(1);
}

void TileMap::Draw() {
	DrawMesh(PRIMITIVE_QUAD);
}

void TileMap::LoadMapIDs(const char* _file) {
	string buffer;
	ifstream tileFile(_file);

	while (getline(tileFile, buffer, ',')) {
		mapIds->push_back(stoi(buffer));
	}
}

void TileMap::LoadUVs() {
	//divido la textura de tiles por la cantidad de tiles.
	float textureW = 1 / cantTilesX;
	float textureH = 1 / cantTilesY;

	int idIndex = 0;
	//parte de la textura va a cada tile.
	for (int i = 0; i < cantUVvertex; i = i + 8) {
		txtreUVvertex[i] = 0.0f;
		txtreUVvertex[i + 1] = 1.0f;

		txtreUVvertex[i + 2] = 0.0f;
		txtreUVvertex[i + 3] = 1.0f - textureH;

		txtreUVvertex[i + 4] = textureW;
		txtreUVvertex[i + 5] = 1.0f - textureH;

		txtreUVvertex[i + 6] = textureW;
		txtreUVvertex[i + 7] = 1.0f;

		int row = 0;
		int column = mapIds->at(idIndex);

		while (column >= cantTilesX) {
			column -= cantTilesX;
			row++;
		}

		txtreUVvertex[i] += textureW * column;
		txtreUVvertex[i + 1] -= textureH * row;

		txtreUVvertex[i + 2] += textureW * column;
		txtreUVvertex[i + 3] -= textureH * row;

		txtreUVvertex[i + 4] += textureW * column;
		txtreUVvertex[i + 5] -= textureH * row;

		txtreUVvertex[i + 6] += textureW * column;
		txtreUVvertex[i + 7] -= textureH * row;

		idIndex++;
	}
}

//todos los vertices del tilemap
//separar funcion
void TileMap::SetTilemapVertex(float* _vertex, int _cant) {
	bufferId = render->GenBuffer(_vertex, sizeof(float) * _cant);	
}


int TileMap::NextTileIsCollider(float _playerTranslationX, float _playerTranslationY, float _playerHeight, float _playerWidht) {

	for (int i = 0; i < tilesColliderData->size(); i++) {
		if (((_playerTranslationX + (_playerWidht / 2)) >= tilesColliderData->at(i).positionX) &&
			((_playerTranslationX - (_playerWidht / 2))	<= tilesColliderData->at(i).positionX + tilesColliderData->at(i).width) &&
			(_playerTranslationY + (_playerHeight / 2)  >= tilesColliderData->at(i).positionY) &&
			(_playerTranslationY - (_playerHeight / 2) <= tilesColliderData->at(i).positionY + tilesColliderData->at(i).height))
		{
			return tilesColliderData->at(i).layer;
		}
	}
	return -1;
}


