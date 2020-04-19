#include "Animation.h"

Animation::Animation(int columns, int rows):
	inicialFrame(0),
	currentFrame(0),
	lastFrame(0),
	timePerFrame(0.1f),
	currentTime(0.0f)
	
{
	sprsht = new SpriteSheet(columns, rows);
}

Animation::~Animation()
{
	delete sprsht;
}

void Animation::SetAnimation(int initF, int finalF, float timePerF)
{
	//me fijo que los valores que resiva sean posibles.
	if (initF >= 0 && finalF < sprsht->GetSize() && timePerF > 0)
	{
		inicialFrame = initF;
		lastFrame = finalF;
		timePerFrame = timePerF;
	}
	
}

float * Animation::UpdateAnimation(float deltaTime) 
{
	currentTime += deltaTime;
	if (currentTime >= timePerFrame)
	{
		if (currentFrame < lastFrame) 
		{
			currentFrame++;
		}
		else 
		{
			currentFrame = inicialFrame;
		}
		
		currentTime = 0.0f;
	}

	return sprsht->GetFrame(currentFrame);
	
}

