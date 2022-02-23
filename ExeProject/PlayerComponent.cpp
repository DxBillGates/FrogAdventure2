#include "PlayerComponent.h"
#include "GameSetting.h"

void PlayerComponent::CalculateVelocity(bool isBoost, const GE::Math::Axis& axis, float deltaTime)
{
	const float SPEED = 1000;
	const float MAX_VEL_LENGTH = 1000;
	const float STOP_VALUE = 500;

	// boostに対応したキーを押していた場合は速度を加算
	// 押していなければ減衰させる
	if (isBoost)
	{
		vel += axis.x * SPEED * deltaTime;
		stopFlagController.SetTime(0);
		stopFlagController.SetFlag(false);
	}
	else
	{
		// ブーストから非ブーストに変わったフレームのみ
		if (!isBoost && preIsBoostInputKey)
		{
			stopFlagController.SetFlag(true);
			preStopVelocity = vel;
		}
		if (stopFlagController.GetOverTimeTrigger())
		{
			vel = 0;
			preStopVelocity = 0;
			stopFlagController.SetTime(0);
			stopFlagController.SetFlag(false);
			return;
		}

		// ストップフラグコントローラーに設定した時間でvelが0になる用に計算
		vel -= preStopVelocity.Normalize() * preStopVelocity.Length() * deltaTime / stopFlagController.GetMaxTime();
		stopFlagController.Update(deltaTime);
	}

	// 速度の上限設定
	if (vel.Length() >= MAX_VEL_LENGTH)vel = vel.Normalize() * MAX_VEL_LENGTH;
}

void PlayerComponent::RotateAxis(bool isBoost, float deltaTime)
{
	const float ROTATE_VALUE = 200;

	if (isBoost)return;

	transform->rotation.y += ROTATE_VALUE * deltaTime;
}

void PlayerComponent::FixPosition(float deltaTime)
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

bool PlayerComponent::AutoMove(float deltaTime)
{
	if (!isPlayScene)return false;

	if (startFlagController.GetOverTimeTrigger())
	{
		startFlagController.Initialize();
	}

	startFlagController.Update(deltaTime);
	return true;
}

PlayerComponent::PlayerComponent()
	: inputDevice(GE::InputDevice::GetInstance())
	, vel(GE::Math::Vector3())
	, preVel(GE::Math::Vector3())
	, preStopVelocity(GE::Math::Vector3())
	, preIsBoostInputKey(false)
	, isPlayScene(false)
	, isReturnStageSelectScene(false)
	, startFlagController(GE::FlagController())
	, stopFlagController(GE::FlagController())
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Start()
{
	transform->position = GE::Math::Vector3(-1000, 0, 0);
	transform->rotation = GE::Math::Vector3();

	startFlagController.Initialize();
	startFlagController.SetFlag(true);
	startFlagController.SetMaxTimeProperty(GameSetting::GetInstance()->GetStartPlaySceneTime());

	const float STOP_TIME = 5;
	stopFlagController.Initialize();
	stopFlagController.SetMaxTimeProperty(STOP_TIME);

	vel = GE::Math::Vector3();
	preVel = vel;
}

void PlayerComponent::Update(float deltaTime)
{
	GE::Math::Matrix4x4 worldMatrix = transform->GetMatrix();
	GE::Math::Axis axis = worldMatrix.GetAxis();
	preVel = vel;

	// ブーストキーのフラグ管理
	bool isInputBoostKey = false;
	if (inputDevice->GetKeyboard()->CheckHitKey(GE::Keys::SPACE))isInputBoostKey = true;
	if (inputDevice->GetXCtrler()->CheckHitButton(GE::XInputControllerButton::XINPUT_B))isInputBoostKey = true;

	// テスト環境のみ
	bool isReturnScene = false;
	if (inputDevice->GetKeyboard()->CheckHitKey(GE::Keys::D0))isReturnScene = true;
	isReturnStageSelectScene = isReturnScene;

	// プレイシーンの最初のみオート移動
	if (startFlagController.GetFlag())isInputBoostKey = AutoMove(deltaTime);

	FixPosition(deltaTime);
	RotateAxis(isInputBoostKey, deltaTime);
	CalculateVelocity(isInputBoostKey, axis, deltaTime);

	transform->position += vel * deltaTime;

	preIsBoostInputKey = isInputBoostKey;
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

void PlayerComponent::OnCollision(GE::GameObject* other)
{
	if (other->GetTag() == "HelpingObject")
	{
		isReturnStageSelectScene = true;
	}
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
