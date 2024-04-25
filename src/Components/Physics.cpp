#include "Physics.h"

void Physics::Start()
{
	InitializeBody();

	if (HasCollider)
		InitializeCollider();

	if (HasTrigger)
		InitializeTrigger();
}

void Physics::InitializeBody()
{
	if (!mEnabled) return;

	BodyDef = new b2BodyDef;

	if (BodyType == "dynamic")
		BodyDef->type = b2_dynamicBody;
	else if (BodyType == "static")
		BodyDef->type = b2_staticBody;
	else if (BodyType == "kinematic")
		BodyDef->type = b2_kinematicBody;

	BodyDef->bullet = Precise;
	BodyDef->gravityScale = GravityScale;
	BodyDef->angularDamping = AngularFriction;

	Transform* transf = mParent->GetComponent<Transform>();

	BodyDef->position.x = transf->Position.x;
	BodyDef->position.y = transf->Position.y;
	//BodyDef.angle = ToRadians(tc->Rotation);

	Body = GetWorld()->CreateBody(BodyDef);

	mInitialized = true;
}

void Physics::InitializeCollider()
{
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = false;
	fixtureDef.density = Density;
	fixtureDef.friction = Friction;
	fixtureDef.restitution = Bounciness;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(mParent);
	HasCollider = true;

	if (Collider.Type == "box")
	{
		b2PolygonShape boxShape;
		boxShape.SetAsBox(Collider.Width * 0.5f, Collider.Height * 0.5f);
		fixtureDef.shape = &boxShape;
		Body->CreateFixture(&fixtureDef);
	}
	else if (Collider.Type == "circle")
	{
		b2CircleShape circle_shape;
		circle_shape.m_radius = Collider.Radius;
		fixtureDef.shape = &circle_shape;
		Body->CreateFixture(&fixtureDef);
	}
}

void Physics::InitializeTrigger()
{
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.density = Density;
	fixtureDef.friction = Friction;
	fixtureDef.restitution = Bounciness;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(mParent);
	HasTrigger = true;

	if (Trigger.Type == "box")
	{
		b2PolygonShape boxShape;
		boxShape.SetAsBox(Trigger.Width * 0.5f, Trigger.Height * 0.5f);
		fixtureDef.shape = &boxShape;
		Body->CreateFixture(&fixtureDef);
	}
	else if (Trigger.Type == "circle")
	{
		b2CircleShape circleShape;
		circleShape.m_radius = Trigger.Radius;
		fixtureDef.shape = &circleShape;
		Body->CreateFixture(&fixtureDef);
	}
}
