#include "Gamebase.h"
#include <GLFW/glfw3.h>

Gamebase::Gamebase() {

}
Gamebase::~Gamebase() {
}
bool Gamebase::Start() {
	cout << "Gamebase::Start()" << endl;
	lastFrame = 0;
	window = new Window();
	if (!window->Start(800, 600, " "))
		return false;

	render = new Renderer();
	if (!render->Start(window))
		return false;
	render->ClearColor(0.0f, 0.0f, 4.0f, 0.0f);
	return OnStart();
}
void Gamebase::Loop() {
	
	bool loop = true;
	while (loop && !window->ShouldClose()) {

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		loop = OnUpdate();
		render->ClearScreen();
		OnDraw();
		render->SwapBuffers();
		window->PollEvents();
	}
}
bool Gamebase::Stop() {
	cout << "Gamebase::Stop()" << endl;
	OnStop();
	render->Stop();
	window->Stop();

	delete render;
	delete window;
	return true;
}


