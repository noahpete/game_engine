#pragma once

#include "glm/glm.hpp"
#include "Util.h"

class Camera
{
public:
	Camera();
	~Camera();

	static void SetPosition(float x, float y);
	static void SetZoom(float zoom);
	static float GetPositionX();
	static float GetPositionY();
	static float GetZoom();
	static void Reset();

private:
	static glm::vec2 sPosition;
	static glm::vec2 sOffset;
	static float sZoom;
	static float sEase;

};

