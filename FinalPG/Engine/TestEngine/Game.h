#include "../EngineDLL/Gamebase.h"
#include "../EngineDLL/Triangle.h"
#include "../EngineDLL/Rectangle.h"
#include "../EngineDLL/Circle.h"
#include "../EngineDLL/Material.h"
#include "../EngineDLL/Importer.h"
#include "../EngineDLL/Sprite.h"
#include "../EngineDLL/CollisionManager.h"
#include "../EngineDLL/TileMap.h"
#include <iostream>
class Game : public Gamebase {
private:
	int i;
	
	Material * mat1;
	Sprite  * spr1;
	Sprite * spr2;
	
	//TileMap *tmp1;
	
public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};
