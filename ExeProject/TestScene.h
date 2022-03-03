#pragma once
#include "Header/GameFramework/Scene/Scene.h"
#include "PlayerComponent.h"
#include "PlayerCameraComponent.h"

class TestScene : public GE::Scene
{
private:
	PlayerComponent* playerComponent;
	PlayerCameraComponent* playerCameraComponent;

	GE::ICollider* playerCollider;
	GE::ICollider* stage1Collider;
	GE::ICollider* stage2Collider;
	GE::ICollider* stage3Collider;

	bool isClearStage1;
	bool isClearStage2;
	bool isClearStage3;

	bool isSetPlayerCamera;
public:
	TestScene();
	TestScene(const std::string& sceneName);
	~TestScene();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void LateDraw() override;
};

