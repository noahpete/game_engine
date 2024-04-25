#pragma once

#include "glm/glm.hpp"
#include "Component.h"
#include "Physics.h"

class Physics;

class Transform : public Component
{
public:
	float Rotation = 0.0f;
	glm::vec2 Position = { 0.0f, 0.0f };
	glm::vec2 Scale = { 0.0f, 0.0f };

	Transform()
		: Component("Transform")
	{
		mInitialized = true;
	}
	~Transform() {}

	void Update() override;

};