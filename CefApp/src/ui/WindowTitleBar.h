#pragma once
#include <platform/MyWin.h>
#include <memory>

class WindowTitleBar
{
public:
	WindowTitleBar(HWND hwndParent);
	~WindowTitleBar();
	void OnSize(int parentWidth);
	void RaiseHandle() noexcept;
public:
	int handleX = 0;
private:
	HWND hWnd_ = nullptr;
	HWND hwndParent_ = nullptr;
};