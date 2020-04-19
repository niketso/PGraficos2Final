#pragma once
#include "Shape.h"
#include "Material.h"
class ENGINEDLL_API Triangle : public Shape
{
	
public:
	Triangle(Renderer *render);	
	~Triangle();
	void Draw() override;
	
};

