#pragma once
#include "Header/GameFramework/Scene/Scene.h"
#include "PlayerComponent.h"
#include "PlayerCameraComponent.h"

class TestScene : public GE::Scene
{
private:
	PlayerComponent* playerComponent;
	PlayerCameraComponent* playerCameraComponent;
public:
	TestScene();
	TestScene(const std::string& sceneName);
	~TestScene();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void LateDraw() override;
};

