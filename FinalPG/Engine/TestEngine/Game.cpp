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
	
	mat1 = new Material();
	unsigned int programID = mat1->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");		

	spr1 = new Sprite(render,8,4);	
	spr2 = new Sprite(render, 1, 1);
	//tmp1 = new TileMap("Tile.csv",800, 600, render, mat1);
	spr1->SetMaterial(mat1);
	spr2->SetMaterial(mat1);
		spr1->LoadTexture("Doom.bmp");
		spr2->LoadTexture("sample2.bmp");
	
	
	spr1->SetAnimation(0, 23, 0.5f);
	
	
	spr1->SetBoundingBox(spr1->GetPos(), 2.0f, 2.0f, false, false);
	spr2->SetBoundingBox(spr1->GetPos(), 2.0f, 2.0f, false, false);
	
	colManager->AddCollisionEntity(spr1 , player);
	colManager->AddCollisionEntity(spr2, enemy);

	spr1->SetPos(-5,0,0);
	spr1->SetPos(5,0,0);
	
	cout << "Game::OnStart()" << endl;
	return true;
}
bool Game::OnStop() {

	delete spr1;
	delete spr2;
	cout << "Game::OnStop()" << endl;
	return false;
}
bool Game::OnUpdate() {
	i++;
	//movX
	spr1->Translate(-0.5f * deltaTime ,0.0f,0.0f);
	spr2->Translate(0.5f * deltaTime, 0.0f, 0.0f);
	//movY
	//spr1->Translate(0.0f,1.0f * deltaTime, 0.0f);
	//spr2->Translate(-4.0f * deltaTime, 0.0f,0.0f);
	//render->TranslateCamera(glm::vec3 (deltaTime*2.0f, 0.f, 0.f));
	spr1->UpdateAnimation(deltaTime);
	//tmp1->Update();
	CollisionManager::Instance()->CollisionBoxDetector();
	//cout << "Game::OnUpdate(): " << i << endl;
	
	return true;
}

void Game::OnDraw()
{
	//tmp1->DrawTileMap();
	spr1->Draw();
	spr2->Draw();
		
	//cout << "Game::OnDraw(): " << i << endl;
}

