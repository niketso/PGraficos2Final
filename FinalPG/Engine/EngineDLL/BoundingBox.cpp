#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec3 bPos, float height, float width, bool isStc, bool isTrggr) :
	boxPosition(bPos),	
	height(height),
	width(width),
	isStatic(isStc),
	isTrigger(isTrggr)	
{
	
	
}
BoundingBox::~BoundingBox()
{
}
unsigned int BoundingBox::GetX() 
{
	return boxPosition.x;
}
unsigned int BoundingBox::GetY()
{
	return boxPosition.y;
}


void BoundingBox::SetHeight(float h) 
{
	height = h;
}
float BoundingBox::GetHeight()
{
	return height;
}
void BoundingBox::SetWidth(float w) 
{
	width = w;
}
float BoundingBox::GetWidth()
{
	return width;
}
void BoundingBox::SetStatic(bool enable)
{
	isStatic = enable;
}
bool BoundingBox::GetStatic() 
{
	return isStatic;
}
void BoundingBox::SetTrigger(bool enableTrigger)
{
}
bool BoundingBox::GetTrigger()
{
	return isTrigger;
}
void BoundingBox::SetBoxPos(glm::vec3 bpos) 
{
	boxPosition = bpos;
}

glm::vec3 BoundingBox::GetBoxPos() 
{
	return boxPosition;
}




