#pragma once
#include <platform/MyWin.h>
#include <ui/OverlayWindow.h>
#include <string>
#include <memory>
#include <cef/config/MyCefConfig_base.h>


class MyCefClient;

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
private:
	// singleton manages registration/cleanup of window class
	class MainWindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		MainWindowClass();
		~MainWindowClass();
		MainWindowClass(const MainWindowClass&) = delete;
		MainWindowClass& operator=(const MainWindowClass&) = delete;
		static constexpr const char* wndClassName = "CefApp.MainWindow.Win32";
		static MainWindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	MainWindow();
	~MainWindow();
	void CreateBrowserView();
	void SetBrowserHWND(HWND hWndBrowser);
	void CreateHandle();
	void CreateD3DWindow();
	bool HasBrowserWindow() const;
	void OnSize(WPARAM wParam);
	void RequestClose();
	void StartFade(FadeAction action);
public:
	inline static MainWindow* GetWindow(HWND hWnd)
	{
		return reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	inline void AttachHWND(HWND hWnd) { hWnd_ = hWnd; }
	inline void RaiseHandle() noexcept
	{
		if (hHandle_) SetWindowPos(hHandle_, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
	inline OverlayWindow* GetOverlay() const { return d3dWindow_.get(); }
	inline void DestroyD3DWindow() { if (d3dWindow_) d3dWindow_.reset(); }
public:
	static constexpr int FADE_STEPS = 15;
	static constexpr int TIMER_FADE = 1;
	int fadeStep = 0;
	bool isMinimized_ = false;
	bool isMaximized_ = false;
	FadeAction fadeAction_ = FadeAction::None;
	int handleX = 0;
private:
	HWND hWnd_ = nullptr;
	HWND hHandle_ = nullptr;
	HWND hWndBrowser_ = nullptr;
	std::unique_ptr<OverlayWindow> d3dWindow_;
	CefRefPtr<MyCefClient> client_;
	std::string url_ = "http://localhost:5173/";
	bool isClosing_ = false;
};
