#pragma once
#include "Header/GameFramework/FlagController.h"
#include "Header/GameFramework/Component/Component.h"
#include "Header/Input/InputDevice.h"

class PlayerComponent : public GE::Component
{
private:
	GE::InputDevice* inputDevice;
	GE::Math::Vector3 vel;
	GE::Math::Vector3 preVel;
	bool isPlayScene;
	bool isReturnStageSelectScene;
private:
	void CalculateVelocity(bool isBoost, const GE::Math::Axis& axis, float deltaTime);
	void RotateAxis(bool isBoost,float deltaTime);
	void FixPosition(bool isPlayScene, float deltaTime);
public:
	PlayerComponent();
	~PlayerComponent();
	void Start() override;
	void Update(float deltaTime) override;
	void Draw();
	void OnCollision(GE::ICollider* hitCollider) override;
	void SetIsPlayScene(bool flag);
	bool IsReturnStageSelectScene();
};

