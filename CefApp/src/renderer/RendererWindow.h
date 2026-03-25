#pragma once
#include <platform/MyWin.h>
#include <renderer/input/Keyboard.h>
#include <renderer/input/Mouse.h>
#include <renderer/Graphics.h>
#include <memory>

class RendererWindow
{
private:
	class RendererWindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		RendererWindowClass() noexcept;
		~RendererWindowClass();
		RendererWindowClass(const RendererWindowClass&) = delete;
		RendererWindowClass& operator=(const RendererWindowClass&) = delete;
		static constexpr const char* wndClassName = "D3DRendererWindow";
		static RendererWindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	RendererWindow(HWND hwndParent);
	~RendererWindow();
	RendererWindow(const RendererWindow&) = delete;
	RendererWindow& operator=(const RendererWindow&) = delete;
	void SetFrame(int left, int top, int width, int height);
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Keyboard kbd;
	Mouse mouse;
private:
	HWND hWnd_ = nullptr; 
	HWND hwndParent_ = nullptr;
	std::unique_ptr<Graphics> gfx_;
	int clientWidth = 0;
	int clientHeight = 0;
};