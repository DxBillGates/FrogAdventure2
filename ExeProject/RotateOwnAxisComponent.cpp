#include "RotateOwnAxisComponent.h"

RotateOwnAxisComponent::RotateOwnAxisComponent()
	: speed(1)
	, rotateAxisType(RotateOwnAxisType::Y)
{
}

void RotateOwnAxisComponent::Start()
{
}

void RotateOwnAxisComponent::Update(float deltaTime)
{
	GE::Math::Vector3 speedVector = 0;
	if (rotateAxisType == RotateOwnAxisType::X)speedVector = {speed,0,0};
	if (rotateAxisType == RotateOwnAxisType::Y)speedVector = {0,speed,0};
	if (rotateAxisType == RotateOwnAxisType::Z)speedVector = {0,0,speed};

	transform->rotation += speedVector;
}

void RotateOwnAxisComponent::SetSpeed(float value)
{
	speed = value;
}

void RotateOwnAxisComponent::SetAxisType(RotateOwnAxisType type)
{
	rotateAxisType = type;
}
