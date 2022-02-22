#pragma once
#include "Header/GameFramework/Scene/Scene.h"
#include "PlayerComponent.h"
#include "PlayerCameraComponent.h"

class TestPlayScene : public GE::Scene
{
private:
	PlayerComponent* playerComponent;
	PlayerCameraComponent* playerCameraComponent;
	GE::FlagController startFlagController;
public:
	TestPlayScene();
	TestPlayScene(const std::string& sceneName);
	~TestPlayScene();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void LateDraw() override;
};

