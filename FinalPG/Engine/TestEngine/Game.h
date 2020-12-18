#include "../EngineDLL/Gamebase.h"
#include "../EngineDLL/Triangle.h"
#include "../EngineDLL/Rectangle.h"
#include "../EngineDLL/Circle.h"
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Importer.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDLL/CollisionManager.h"
#include "../EngineDLL/TileMap.h"
#include "../EngineDLL/Input.h"
#include <iostream>
class Game : public Gamebase {
private:
	int i;
	float textTime;
	bool gameFinish = false;
	Input * inp;
	Material * mat1;
	Sprite  * spr1;
	TileMap *tmp1;
	Sprite * youwon;
	Sprite * youLost;
	Sprite * obstacle01;
	Sprite * obstacle02;
	Sprite * obstacle03;
	Sprite * obstacle04;
	Sprite * obstacle05;
	Sprite * obstacle06;
	Sprite * obstacle07;
	Sprite * obstacle08;
	Sprite * obstacle09;
	vector<int> * colliderTiles = new vector<int>();
	bool ResolveCollisions();
	void YouWon();
	void YouLose();
	
public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};
