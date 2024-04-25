#pragma once

#include "box2d/box2d.h"
#include "Component.h"
#include "Transform.h"

class Transform;

class Physics : public Component
{
public:
	struct ColliderData
	{
		bool Active = false;
		std::string Type = "box";
		float Width = 1.0f;
		float Height = 1.0f;
		float Radius = 0.5f;
	};

	struct TriggerData
	{
		bool Active = false;
		std::string Type = "box";
		float Width = 1.0f;
		float Height = 1.0f;
		float Radius = 0.5f;
	};

	static inline b2World* GetWorld()
	{
		static b2World* sWorld = nullptr;
		if (!sWorld)
		{
			sWorld = new b2World(b2Vec2(0.0f, 9.8f));
			b2ContactListener* collisionListener = new b2ContactListener();
			sWorld->SetContactListener(collisionListener);
		}
		return sWorld;
	}

	ColliderData Collider;
	TriggerData Trigger;
	b2Body* Body;
	b2BodyDef* BodyDef;
	std::string BodyType = "dynamic";
	bool Precise = true;
	bool HasCollider = false;
	bool HasTrigger = false;
	float Density = 1.0f;
	float GravityScale = 1.0f;
	float Friction = 0.3f;
	float AngularFriction = 0.3f;
	float Bounciness = 0.3f;

	Physics()
		: Component("Physics")
	{
		Body = nullptr;
		BodyDef = nullptr;
	}

	~Physics()
	{

	}

	void Start() override;

	void InitializeBody();

	void InitializeCollider();

	void InitializeTrigger();


};