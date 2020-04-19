#pragma once
#include "Exports.h"
#include "Definitions.h"
#include <iostream>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
using namespace std;

class ENGINEDLL_API BoundingBox
{
private:
glm::vec3 boxPosition;
 float height;
 float width;
 bool isStatic;
 bool isTrigger;

public:
	BoundingBox(glm::vec3 bPos,float height, float width,bool isStc, bool isTrggr);
	~BoundingBox();
	unsigned int GetX();
	unsigned int GetY();
	void SetBoxPos(glm::vec3 bpos);
	glm::vec3 GetBoxPos();
	void SetHeight(float h);
	void SetWidth(float w);
	float GetHeight();
	float GetWidth();
	void SetStatic(bool enable);
	bool GetStatic();
	void SetTrigger(bool enableTrigger);
	bool GetTrigger();

	
	
};

