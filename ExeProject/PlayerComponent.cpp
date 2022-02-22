#include "PlayerComponent.h"

void PlayerComponent::CalculateVelocity(bool isBoost, const GE::Math::Axis& axis, float deltaTime)
{
	const float SPEED = 5;
	const float MAX_VEL_LENGTH = 5;
	const float STOP_TIME = 1;

	if (isBoost)vel += axis.x * SPEED * deltaTime;
	else
	{
		vel -= preVel.Normalize() * deltaTime / STOP_TIME;
	}

	if (vel.Length() >= MAX_VEL_LENGTH)vel = vel.Normalize() * MAX_VEL_LENGTH;
}

void PlayerComponent::RotateAxis(bool isBoost, float deltaTime)
{
	const float ROTATE_VALUE = 200;

	if (isBoost)return;

	transform->rotation.y += ROTATE_VALUE * deltaTime;
}

void PlayerComponent::FixPosition(bool isPlayScene, float deltaTime)
{
	if (!isPlayScene)return;

	if (transform->position.z >= 830)
	{
		transform->position.z = 830;
		vel.z *= -1;
	}
	else if (transform->position.z <= -760)
	{
		transform->position.z = -760;
		vel.z *= -1;
	}
}

PlayerComponent::PlayerComponent()
	: inputDevice(GE::InputDevice::GetInstance())
	, vel(GE::Math::Vector3())
	, preVel(GE::Math::Vector3())
	, isPlayScene(false)
	, isReturnStageSelectScene(false)
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Start()
{
	vel = GE::Math::Vector3();
	preVel = vel;
}

void PlayerComponent::Update(float deltaTime)
{
	GE::Math::Matrix4x4 worldMatrix = transform->GetMatrix();
	GE::Math::Axis axis = worldMatrix.GetAxis();
	preVel = vel;

	bool isInputBoostKey = false;
	if (inputDevice->GetKeyboard()->CheckHitKey(GE::Keys::SPACE))isInputBoostKey = true;
	if (inputDevice->GetXCtrler()->CheckHitButton(GE::XInputControllerButton::XINPUT_B))isInputBoostKey = true;

	bool isReturnScene = false;
	if (inputDevice->GetKeyboard()->CheckHitKey(GE::Keys::D0))isReturnScene = true;
	isReturnStageSelectScene = isReturnScene;

	FixPosition(isPlayScene, deltaTime);
	RotateAxis(isInputBoostKey, deltaTime);
	CalculateVelocity(isInputBoostKey,axis,deltaTime);

	transform->position += vel;
}

void PlayerComponent::Draw()
{
	const float DRAW_SIZE = 100;
	GE::ICBufferAllocater* cbufferAllocater = graphicsDevice->GetCBufferAllocater();
	GE::RenderQueue* renderQueue = graphicsDevice->GetRenderQueue();

	graphicsDevice->SetShader("DefaultMeshShader");

	transform->scale = DRAW_SIZE;
	GE::Math::Matrix4x4 modelMatrix = transform->GetMatrix();
	GE::Material material;
	material.color = GE::Color::White();
	const GE::CameraInfo& camera = graphicsDevice->GetMainCamera()->GetCameraInfo();

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1, &camera, sizeof(GE::CameraInfo)) });
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(GE::Material)) });
	graphicsDevice->DrawMesh("Cube");
}

void PlayerComponent::OnCollision(GE::ICollider* hitCollider)
{
}

void PlayerComponent::SetIsPlayScene(bool flag)
{
	isPlayScene = flag;
}

bool PlayerComponent::IsReturnStageSelectScene()
{
	return isReturnStageSelectScene;
}
