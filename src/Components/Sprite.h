#pragma once

#include "Component.h"

class Sprite : public Component
{
public:
	std::string TextureName = "";

	Sprite()
		: Component("Sprite")
	{
		mInitialized = true;
	}

	~Sprite()
	{

	}

};