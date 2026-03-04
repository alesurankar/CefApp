#pragma once
#include "Graphics.h"
#include "../platform/MyTimer.h"


struct HWND__; // forward-declare
using HWND = HWND__*;

class Renderer
{
public:
	Renderer(HWND hwndOverlay);
	void Tick()
	{
		const float c = sin(timer.Peek()) / 2.0f + 0.5f;
		gfx.ClearBuffer(c, c, 1.0f);
		gfx.DrawTestTriangle();
		gfx.EndFrame();
	}
private:
	Graphics gfx;
	MyTimer timer;
};