#include "Shape.h"



Shape::Shape(Renderer* render): Entity(render)
{
	material = NULL;
	vertex = NULL;
	clrvertex = NULL;
	
	bufferId = -1;
	colorBufferId = -1;
	
}
Shape::~Shape()
{
	Dispose();
	DisposeColor();
	
}
void Shape::SetVertices(float* vertices, int count) 
{
	vtxCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);
}
void Shape::SetColorVertices(float* vertices, int count) 
{
	colorVtxCount = count;
	shouldDisposeColor = true;
	colorBufferId = render->GenColorBuffer(vertices, sizeof(float)* count * 3);
}


void Shape::SetMaterial(Material* material)
{
	this->material = material;
}

void Shape::DrawMesh(int drawType) 
{
	render->LoadIdentityMatrix();
	render->SetWorldMatrix(WorldMatrix);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty("WVP", render->GetWvp());
	}
	render->BeginDraw(0);
	render->BeginDraw(1);
	render->BindBuffer(bufferId, 0);	
	render->BindColorBuffer(colorBufferId, 1);
	render->DrawBuffer(vtxCount,drawType);
	render->EndDraw(0);
	render->EndDraw(1);
}
void Shape::Dispose() 
{
	if (shouldDispose)
	{
		render->DestroyBuffer(bufferId);			
		shouldDispose = false;
	}
}
void Shape::DisposeColor()
{
	if (shouldDisposeColor)
	{		
		render->DestroyBuffer(colorBufferId);		
		shouldDispose = false;
	}
}

