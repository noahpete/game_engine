#include "Transform.h"

void Transform::Update()
{
	Physics* phys = mParent->GetComponent<Physics>();
	if (phys)
	{
		Position.x = phys->Body->GetTransform().p.x;
		Position.y = phys->Body->GetTransform().p.y;
		Rotation = phys->Body->GetTransform().q.GetAngle();
	}
}
