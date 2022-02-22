#pragma once
#include "Header/GameFramework/Component/Component.h"

enum class RotateOwnAxisType
{
	X,Y,Z
};

class RotateOwnAxisComponent : public GE::Component
{
private:
	float speed;
	RotateOwnAxisType rotateAxisType;
public:
	RotateOwnAxisComponent();
	void Start() override;
	void Update(float deltaTime) override;
	void SetSpeed(float value);
	void SetAxisType(RotateOwnAxisType type);
};

