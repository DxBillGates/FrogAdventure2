#pragma once
#include "Header/GameFramework/Component/Component.h"
#include "Header/Graphics/Camera3D.h"

class PlayerCamera : public GE::Camera3D
{
private:
	GE::Math::Vector3 prePos;
	float deltaTime;
public:
	PlayerCamera();
	void Initialize() override;
	void Update() override;
	void SetPrePosition(const GE::Math::Vector3& pos);
	void SetDeltaTime(float value);
};

class PlayerCameraComponent : public GE::Component
{
private:
	PlayerCamera camera;
	float distance;
	float pitch;

	bool isSetPitch;
	bool isPlayScene;
public:
	PlayerCameraComponent();
	void Start() override;
	void Update(float deltaTime) override;
	GE::Camera* GetCamera();
	void SetPitch(float value);
	void SetIsPlayScene(bool flag);
};

