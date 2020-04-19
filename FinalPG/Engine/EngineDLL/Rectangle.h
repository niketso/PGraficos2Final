#pragma once
#include "Shape.h"
#include "Material.h"
class ENGINEDLL_API Rectangle :public Shape
{		
public:
	Rectangle(Renderer *render);
	~Rectangle();
	void Draw() override;
};

