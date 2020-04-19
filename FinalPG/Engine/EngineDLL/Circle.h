#pragma once
#include "Shape.h"
#define PI 3.14159265359f
class  ENGINEDLL_API Circle :public Shape
{
private:
	float radius;
	float angle;
	float degrees;
	int triangleCant;
public:
	Circle(Renderer *render,float rdio,int trCant);
	~Circle();
	void Draw() override;
};

