#pragma once
#include "Header/GameFramework/Scene/Scene.h"
#include "PlayerComponent.h"
#include "PlayerCameraComponent.h"
#include "MovingLengthWatcherComponent.h"

class TestPlayScene : public GE::Scene
{
private:
	PlayerComponent* playerComponent;
	PlayerCameraComponent* playerCameraComponent;
	MovingLengthWatcherComponent* movingLengthWatcherComponent;
	GE::FlagController startFlagController;
	bool isSetPlayerCamera;
public:
	TestPlayScene();
	TestPlayScene(const std::string& sceneName);
	~TestPlayScene();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void LateDraw() override;
};

