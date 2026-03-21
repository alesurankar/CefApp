#pragma once
#include <platform/MyWin.h>

class Graphics
{
public:
	Graphics(HWND hwndOverlay);
	void Clear(float red, float green, float blue) noexcept;
	void Resize(int width, int height);
	void Present();
private:
};