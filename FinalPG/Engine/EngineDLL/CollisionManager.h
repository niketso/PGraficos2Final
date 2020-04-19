#pragma once
#include "Exports.h"
#include "Entity.h"
#include "BoundingBox.h"
#include "Definitions.h"
#include <vector>
#include <list>
using namespace std;

class  ENGINEDLL_API CollisionManager
{
private:
	static CollisionManager* instance;

	vector<list<Entity*>*> CollisionGroups;
	
public:
	CollisionManager();
	~CollisionManager();
	void AddCollisionEntity(Entity* e, Layers lyr);
	void CollisionBoxDetector();
	void CheckCollisionsBetweenLayers( list<Entity*> *layerA,  list<Entity*> *layerB);	
	void CollisionBoxResolver(Entity* A, Entity* B);
	
	static CollisionManager* Instance()
	{
		if (instance == NULL)
		{
			instance = new CollisionManager();
		}
		return instance;
	}

	/*CollisionManager(CollisionManager const&) = delete;
	void operator = (CollisionManager const&) = delete;*/
};

