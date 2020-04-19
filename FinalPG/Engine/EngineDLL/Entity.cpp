#include "Entity.h"

Entity::Entity(Renderer *renderPTR)
{
	render = renderPTR;
	WorldMatrix = glm::mat4(1.0f);
	TranslateMatrix = glm::mat4(1.0f);
	RotMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::mat4(1.0f);
	pivotPosition = glm::vec3(0.0f);

	pos[0] = pos[1] = pos[2] = 0.0f;
	rot[0] = rot[1] = rot[2] = 0.0f;
	scale[0] = scale[1] = scale[2] = 1.0f;
	
	

}
void Entity::SetPos(float x, float y,float z) 
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;

	if(bBox)
	bBox->SetBoxPos(pos);

	TranslateMatrix = glm::translate(glm::mat4(1.0f), pos);
	UpdateWorldMatrix();
}
void Entity::SetRot(float x, float y, float z)
{
	rot[0] = x;
	rot[1] = y;
	rot[2] = z;

	RotMatrix = glm::rotate(glm::mat4(1.0f), x, glm::vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), y, glm::vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), z, glm::vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}
void Entity::SetScale(float x, float y, float z)
{
	scale[0] = x;
	scale[1] = y;
	scale[2] = z;

	ScaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	UpdateWorldMatrix();
}
void Entity::UpdateWorldMatrix() 
{
	WorldMatrix = TranslateMatrix  * RotMatrix * ScaleMatrix;
}
glm::vec3 Entity::GetPos() 
{
	return pos;
}
glm::vec3 Entity::GetRot()
{
	return rot;
}
glm::vec3 Entity::GetScale()
{
	return scale;
}

void Entity::Translate(float x, float y, float z) 
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;

	bBox->SetBoxPos(pos);

	TranslateMatrix = glm::translate(glm::mat4(1.0f), pos);
	UpdateWorldMatrix();
}
void Entity::Rotate(float x, float y, float z) 
{
	rot[0] += x;
	rot[1] += y;
	rot[2] += z;

	RotMatrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), rot[1], glm::vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= glm::rotate(glm::mat4(1.0f), rot[2], glm::vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}

void Entity::SetBoundingBox(glm::vec3 bPos, float h, float w, bool isStc, bool isTrggr)
{
	bBox = new BoundingBox(bPos, h, w, isStc, isTrggr);		
}

float Entity::GetX()
{
	return pos.x;
}
float Entity::GetY()
{
	return pos.y;
}
glm::vec2 Entity::GetPivot()
{
	return pivotPosition;
}
float Entity::GetHeight()
{
	return height;
}
float Entity::GetWidth()
{
	return width;
}

BoundingBox* Entity::GetBoundingBox()
{
	return bBox;
}



