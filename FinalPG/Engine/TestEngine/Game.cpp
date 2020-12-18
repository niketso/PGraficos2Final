#include "Game.h"
Game::Game()
{
	i = 0;	
}
Game::~Game()
{
}
bool Game::OnStart() {
	CollisionManager* colManager = CollisionManager::Instance();

	inp = new Input(window);
	textTime = 3.0f;
	
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");		

	spr1 = new Sprite(render,8,4);
	youwon = new Sprite(render, 1, 1);
	youLost = new Sprite(render, 1, 1);
	obstacle01 = new Sprite(render, 1, 1);
	obstacle02 = new Sprite(render, 1, 1);
	obstacle03 = new Sprite(render, 1, 1);
	obstacle04 = new Sprite(render, 1, 1);
	obstacle05 = new Sprite(render, 1, 1);
	obstacle06 = new Sprite(render, 1, 1);
	obstacle07 = new Sprite(render, 1, 1);
	obstacle08 = new Sprite(render, 1, 1);
	obstacle09 = new Sprite(render, 1, 1);
	//spr2 = new Sprite(render, 1, 1);

	colliderTiles->push_back(0);
	colliderTiles->push_back(1);
	colliderTiles->push_back(2);
	tmp1 = new TileMap(render, 74.0f, 21.0f, "Map1.csv", 2, 3,10.5,1, colliderTiles);
	tmp1->SetMaterial(mat1);
	tmp1->LoadTexture("All.bmp");

	spr1->SetMaterial(mat1);
	spr1->LoadTexture("Doom.bmp");	
	spr1->SetAnimation(0, 23, 0.5f);
	spr1->SetBoundingBox(spr1->GetPos(), 2.0f, 2.0f, false, false);
	colManager->AddCollisionEntity(spr1 , player);
	spr1->SetPos(-8,0,0);

	youwon->SetMaterial(mat1);
	youLost->SetMaterial(mat1);
	youwon->LoadTexture("youwon.bmp");
	youLost->LoadTexture("youlost.bmp");


		obstacle01->SetMaterial(mat1);
		obstacle02->SetMaterial(mat1);
		obstacle03->SetMaterial(mat1);
		obstacle04->SetMaterial(mat1);
		obstacle05->SetMaterial(mat1);
		obstacle06->SetMaterial(mat1);
		obstacle07->SetMaterial(mat1);
		obstacle08->SetMaterial(mat1);
		obstacle09->SetMaterial(mat1);

		obstacle01->LoadTexture("Sample2.bmp");
		obstacle02->LoadTexture("Sample2.bmp");
		obstacle03->LoadTexture("Sample2.bmp");
		obstacle04->LoadTexture("Sample2.bmp");
		obstacle05->LoadTexture("Sample2.bmp");
		obstacle06->LoadTexture("Sample2.bmp");
		obstacle07->LoadTexture("Sample2.bmp");
		obstacle08->LoadTexture("Sample2.bmp");
		obstacle09->LoadTexture("Sample2.bmp");


		obstacle01->SetBoundingBox(obstacle01->GetPos(), 2.0f, 2.0f, true, false);
		obstacle02->SetBoundingBox(obstacle02->GetPos(), 2.0f, 2.0f, true, false);
		obstacle03->SetBoundingBox(obstacle03->GetPos(), 2.0f, 2.0f, true, false);
		obstacle04->SetBoundingBox(obstacle04->GetPos(), 2.0f, 2.0f, true, false);
		obstacle05->SetBoundingBox(obstacle05->GetPos(), 2.0f, 2.0f, true, false);
		obstacle06->SetBoundingBox(obstacle06->GetPos(), 2.0f, 2.0f, true, false);
		obstacle07->SetBoundingBox(obstacle07->GetPos(), 2.0f, 2.0f, true, false);
		obstacle08->SetBoundingBox(obstacle08->GetPos(), 2.0f, 2.0f, true, false);
		obstacle09->SetBoundingBox(obstacle09->GetPos(), 2.0f, 2.0f, true, false);


		colManager->AddCollisionEntity(obstacle01,enemy);
		colManager->AddCollisionEntity(obstacle02,enemy);
		colManager->AddCollisionEntity(obstacle03,enemy);
		colManager->AddCollisionEntity(obstacle04,enemy);
		colManager->AddCollisionEntity(obstacle05,enemy);
		colManager->AddCollisionEntity(obstacle06,enemy);
		colManager->AddCollisionEntity(obstacle07,enemy);
		colManager->AddCollisionEntity(obstacle08,enemy);
		colManager->AddCollisionEntity(obstacle09,enemy);

		obstacle01->SetPos(5.0f ,0.0f, 0.0f);
		obstacle02->SetPos(15.0f ,-7.0f, 0.0f);
		obstacle03->SetPos(20.0f ,5.0f, 0.0f);
		obstacle04->SetPos(35.0f ,0.0f, 0.0f);
		obstacle05->SetPos(40.0f ,-5.0f, 0.0f);
		obstacle06->SetPos(45.0f ,5.0f, 0.0f);
		obstacle07->SetPos(50.0f ,0.0f, 0.0f);
		obstacle08->SetPos(55.0f ,-5.0f, 0.0f);
		obstacle09->SetPos(60.0f ,5.0f, 0.0f);
							    




	
	cout << "Game::OnStart()" << endl;
	return true;
}

bool Game::ResolveCollisions() 
{
	int result = tmp1->NextTileIsCollider(spr1->GetPos().x, spr1->GetPos().y, 2.0f, 2.0f);
	
	switch (result)
	{
		case -1:
			return true;
		case 0:
			//cout << "choque_con 0" << endl;
			YouWon();
			break;
		case 1:
			YouLose();
			//cout << "choque_con 1" << endl;
			break;
		case 2:
			YouLose();
			//cout << "choque_con 2" << endl;
			break;
	}
	return false;

}

void Game::YouWon()
{
	cout << "You Won" << endl;
	gameFinish = true;
	youwon->SetPosS(render->GetCameraPos().x, 0.0f,0.0f);
	if (textTime>0.0f)
	{
		youwon->Draw();
		textTime -= deltaTime;
	}
	else
	{
		window->Stop();
	}
}

void Game::YouLose()
{	cout << "You Lost" << endl;
gameFinish = true;
	youLost->SetPosS(render->GetCameraPos().x, 0.0f, 0.0f);
	if (textTime > 0.0f)
	{
		
		youLost->Draw();
		textTime -= deltaTime;
	}
	else
	{
		window->Stop();
	}
	
}

bool Game::OnStop() {

	delete spr1;
	delete youwon;
	delete youLost;
	delete tmp1;
	delete obstacle01;
	delete obstacle02;
	delete obstacle03;
	delete obstacle04;
	delete obstacle05;
	delete obstacle06;
	delete obstacle07;
	delete obstacle08;
	delete obstacle09;
	cout << "Game::OnStop()" << endl;
	return false;
}
bool Game::OnUpdate() {
	i++;
	CollisionManager::Instance()->CollisionBoxDetector();
	
	if (ResolveCollisions())
	{
		spr1->Translate(5.0f * deltaTime, 0.0f, 0.0f);
	}

	if (ResolveCollisions())
	{
		if (inp->IsKeyPressed(87))										//w		
		{
			spr1->Translate(0.0f, 5.0f * deltaTime, 0.0f);
		}
	}
											                                       
	if (ResolveCollisions())
	{
		if (inp->IsKeyPressed(83))                                     //s
		{
			spr1->Translate(0.0f, -5.0f * deltaTime, 0.0f);
		}
	}
			
	if (!gameFinish)
	{
		render->TranslateCamera(glm::vec3(deltaTime*5.0f, 0.f,0.0f));
	}
	spr1->UpdateAnimation(deltaTime);

	

	//cout << "Game::OnUpdate(): " << i << endl;
	
	return true;
}

void Game::OnDraw()
{
	tmp1->Draw();
	
	
	if (!gameFinish) {
		spr1->Draw();
		obstacle01->Draw();
		obstacle02->Draw();
		obstacle03->Draw();
		obstacle04->Draw();
		obstacle05->Draw();
		obstacle06->Draw();
		obstacle07->Draw();
		obstacle08->Draw();
		obstacle09->Draw();
	}
	else {
		//render->ClearScreen();
		youwon->Draw();
		youLost->Draw();
	}
			
	//cout << "Game::OnDraw(): " << i << endl;
}

