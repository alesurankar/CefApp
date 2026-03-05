#pragma once
#include <platform/MyTimer.h>
#include <renderer/Graphics.h>
#include <memory>


class Renderer
{
public:
private:
	std::unique_ptr<Graphics> gfx_;
	MyTimer timer;
};