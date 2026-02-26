#pragma once
#include "../platform/MyWin.h"
#include "OverlayWindow.h"
#include <string>
#include <memory>
#include "../cef/config/MyCefConfig_base.h"


class MyCefClient;

HWND CreateMainWindow(HINSTANCE hInstance);
void CleanupMainWindow(HINSTANCE hInstance);

class MainWindow
{
public:
	enum class FadeAction
	{
		None,
		Close,
		Minimize,
		Maximize,
		Restore
	};
	inline static MainWindow* GetWindow(HWND hWnd) 
	{ 
		return reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)); 
	}
	inline void AttachHWND(HWND hWnd) { hWnd_ = hWnd; }
	inline void RaiseHandle() noexcept
	{ 
		if (hHandle_) 
			SetWindowPos(hHandle_, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); 
	}
	inline OverlayWindow* GetOverlay() const { return overlay_.get(); }
	inline void DestroyOverlayWindow() { if (overlay_) overlay_.reset(); }

	void CreateBrowser();
	bool HasBrowserWindow() const;
	void OnSize(WPARAM wParam);
	void SetBrowserHWND(HWND hWndBrowser);
	void RequestClose();
	void StartFade(FadeAction action);
	void CreateOverlayWindow();
public:
	static constexpr int FADE_STEPS = 15;
	static constexpr int TIMER_FADE = 1;
	int fadeStep = 0;
	bool isMinimized_ = false;
	bool isMaximized_ = false;
	FadeAction fadeAction_ = FadeAction::None;
private:
	HWND hWnd_ = nullptr;
	HWND hHandle_ = nullptr;
	HWND hWndBrowser_ = nullptr; 
	std::unique_ptr<OverlayWindow> overlay_;
	CefRefPtr<MyCefClient> client_;
	std::string url_ = "http://localhost:5173/";
	bool isClosing_ = false; 
};

