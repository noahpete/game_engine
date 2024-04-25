#include "Actor.h"

void Actor::Start()
{
	for (Component* component : mComponents)
		if (component->mEnabled)
			component->Start();
	mInitialized = true;
}

void Actor::Update()
{
	for (Component* component : mComponents)
	{
		if (!component->mEnabled)
			continue;

		if (component->mInitialized)
			component->Update();
		else
			component->Start();
	}
}

void Actor::LateUpdate()
{
	for (Component* component : mComponents)
		component->LateUpdate();
}

void Actor::Destroy()
{
}
