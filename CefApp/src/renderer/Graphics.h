#pragma once
#include <platform/MyWin.h>

class Graphics
{
public:
	Graphics(HWND hwndOverlay);
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawTestTriangle();
	void EndFrame();
private:
};