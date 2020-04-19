#include "Triangle.h"
Triangle::Triangle(Renderer *render) :Shape(render)
{
	
	vertex = new float[9]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	
	SetVertices(vertex, 3);
	
	clrvertex = new float[9]
	{
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f
	};

	SetColorVertices(clrvertex, 3);
	 
}
 Triangle::~Triangle()
{
	 delete[] vertex;
	 delete[] clrvertex;
}
void  Triangle::Draw() 
 {
	 DrawMesh(GL_TRIANGLES);
 }
