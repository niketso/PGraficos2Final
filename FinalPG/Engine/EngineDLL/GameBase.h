#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "TypeDef.h"

#include <iostream>
using namespace std;
class ENGINEDLL_API Gamebase {
private:
	double currentFrame;
	double lastFrame;
	Window* window;
public:
	Gamebase();
	~Gamebase();
	bool Start();
	bool Stop();
	void Loop();
protected:
	double deltaTime;
	Renderer * render;
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual void OnDraw() = 0;
};

