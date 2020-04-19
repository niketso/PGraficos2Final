#include "CollisionManager.h"
#include <math.h>


CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager()
{	
	for (int i = 0; i < (int)Layers::count; i++) 
	{		
		CollisionGroups.push_back(new list<Entity*>());						
	}			
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddCollisionEntity(Entity* e , Layers lyr)
{
	
	 CollisionGroups[lyr]->push_back(e); 
	 

}

void CollisionManager::CollisionBoxDetector() 
{
	for (int i = 0; i < (int)Layers::count; i++)
	{
		for (int j = i+1; j < (int)Layers::count; j++)
		{
			if (i == Layers::map || j == Layers::map)
			{
				continue;
			}
			CheckCollisionsBetweenLayers(CollisionGroups[i] ,CollisionGroups[j]);                                           
		}
	}
}

void CollisionManager::CheckCollisionsBetweenLayers( list<Entity*> *layerA, list<Entity*> *layerB)
{
	
	for (list<Entity*>::iterator i = layerA->begin(); i != layerA->end(); ++i) {
		for (list<Entity*>::iterator j = layerB->begin(); j != layerB->end(); ++j) {
			CollisionBoxResolver(*i, *j); 
			
		}
	}
	
}

void CollisionManager::CollisionBoxResolver(Entity* A, Entity* B)
{
	//calcular la matematica.
	glm::vec2 Diff = ( A->GetBoundingBox()->GetBoxPos() - B->GetBoundingBox()->GetBoxPos());
	//valor absoluto.	
	glm::vec2 module = abs(Diff);	
			
	if (module.x <= (A->GetBoundingBox()->GetWidth() + B->GetBoundingBox()->GetWidth() )/2.0f && module.y <= (A->GetBoundingBox()->GetHeight() + B->GetBoundingBox()->GetHeight())/2.0f)
	{
		//frenar al las entidades
		//A->Translate(0, 0, 0);
		//B->Translate(0, 0, 0);
		
		//Penetracion
		float xP = ((A->GetBoundingBox()->GetWidth()/2.0f) + (B->GetBoundingBox()->GetWidth() / 2.0f)) - module.x;
		float yP = ((A->GetBoundingBox()->GetHeight()/2.0f) + (B->GetBoundingBox()->GetHeight() / 2.0f)) - module.y;

		if (xP > yP)
		{
			//cout << yP  <<endl;
			//vertical
			if (A->GetBoundingBox()->GetStatic())
			{
				if (A->GetY() >= B->GetY())
				{
					B->SetPos(B->GetX(), B->GetY() + (yP), 0.0f);
				}
				else 
				{
					B->SetPos(B->GetX(), B->GetY() - (yP), 0.0f);
				}
							
			}
			else if (B->GetBoundingBox()->GetStatic())
			{
				if (A->GetY() >= B->GetY()) 
				{
					A->SetPos(A->GetX(), A->GetY() + (yP), 0.0f);
				}
				else 
				{
					A->SetPos(A->GetX(), A->GetY() - (yP), 0.0f);
				}
				
			}
			else 
			{
				A->SetPos(A->GetX(),A->GetY() + (yP / 2.0f) , 0.0f);
				B->SetPos(B->GetX(), B->GetY() - (yP / 2.0f), 0.0f);
			}
			

		}
		else 
		{
			//cout << xP << endl;
			//horizontal
			
			if (A->GetBoundingBox()->GetStatic())
			{
				if (A->GetX() >= B->GetX()) 
				{
					B->SetPos(B->GetX() + (xP), B->GetY(), 0.0f);
				}
				else
				{
					B->SetPos(B->GetX() - (xP), B->GetY(), 0.0f);
				}
				
			}
			else if (B->GetBoundingBox()->GetStatic())
			{
				if (A->GetX() >= B->GetX()) 
				{
					A->SetPos(A->GetX() + (xP), A->GetY(), 0.0f);
				}
				else 
				{
					A->SetPos(A->GetX() - (xP), A->GetY(), 0.0f);
				}
				
			}
			else
			{
				A->SetPos(A->GetX() + (xP /2.0f), A->GetY(),0.0f);
				B->SetPos(B->GetX() - (xP /2.0f), B->GetY(),0.0f);
				
			}
			//falta determinar de que lado viene
		}
		 
	}
}




