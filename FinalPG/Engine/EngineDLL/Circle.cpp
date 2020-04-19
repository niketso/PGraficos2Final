#include "Circle.h"



Circle::Circle(Renderer *render, float rdio, int trCant):Shape(render)
{
	triangleCant = trCant;
	radius = rdio;
	vtxCount = triangleCant * 3;
	 degrees = 360.0f / triangleCant;
	angle = 0.0f;
		
	vertex =  new float[vtxCount] {};
	glm::vec3 vec;

	for (int i = 0; i < vtxCount; i+=3)
	{
		vec = glm::vec3(cos(angle),sin(angle),0) * radius;
		vertex[i] = vec.x;
		vertex[i + 1] = vec.y;
		vertex[i + 2] = vec.z;
		angle += degrees * PI / 180.0f;

	}
	SetVertices(vertex, triangleCant);

	
	SetColorVertices(vertex, triangleCant);


}

Circle::~Circle()
{
	delete[] vertex;
}
void Circle::Draw() 
{
	DrawMesh(GL_TRIANGLE_FAN);
}
