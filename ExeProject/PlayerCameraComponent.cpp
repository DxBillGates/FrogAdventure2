#include "PlayerCameraComponent.h"

PlayerCameraComponent::PlayerCameraComponent()
	: camera(PlayerCamera())
	, distance(1000)
	, pitch(75)
	, isSetPitch(false)
	, isPlayScene(false)
{
}

void PlayerCameraComponent::Start()
{
	camera.Initialize();
	camera.SetPitch(GE::Math::ConvertToRadian(75));

	if (!isSetPitch)pitch = 75;
	distance = 1000;
}

void PlayerCameraComponent::Update(float deltaTime)
{
	const GE::CameraInfo& cameraInfo = camera.GetCameraInfo();
	GE::Math::Vector3 cameraDir = { cameraInfo.cameraDir.x,cameraInfo.cameraDir.y,cameraInfo.cameraDir.z };

	GE::Math::Vector3 setCameraPosition = transform->position - cameraDir * distance;
	GE::Math::Vector3 setCameraPrePosition = gameObject->GetPreTranform()->position - cameraDir * distance;

	if (isPlayScene)
	{
		setCameraPosition.z = 0;
		setCameraPrePosition.z = 0;
	}

	camera.SetPrePosition(setCameraPrePosition);
	camera.SetPosition(setCameraPosition);
	camera.SetPitch(GE::Math::ConvertToRadian(pitch));
	camera.Update();
}

GE::Camera* PlayerCameraComponent::GetCamera()
{
	return &camera;
}

void PlayerCameraComponent::SetPitch(float value)
{
	pitch = value;
	isSetPitch = true;
}

void PlayerCameraComponent::SetIsPlayScene(bool flag)
{
	isPlayScene = flag;
}


PlayerCamera::PlayerCamera()
	: prePos(GE::Math::Vector3())
	, deltaTime(1)
{
}

void PlayerCamera::Initialize()
{
	info.cameraPos = prePos = GE::Math::Vector3();
	Camera3D::Initialize();
	deltaTime = 1;
}

void PlayerCamera::Update()
{
	float minMaxPitch = GE::Math::ConvertToRadian(89);
	if (pitch > minMaxPitch)pitch = minMaxPitch;
	if (pitch < -minMaxPitch)pitch = -minMaxPitch;

	GE::Math::Vector3 pos = { info.cameraPos.x,info.cameraPos.y,info.cameraPos.z };
	//prePos = pos;

	const float LERP_VALUE = 0.05f;
	GE::Math::Vector3 fixPos = GE::Math::Vector3::Lerp(prePos, pos, LERP_VALUE);

	direction = GE::Math::Vector3(0, 0, 1);
	rotation = GE::Math::Matrix4x4::RotationX(pitch) * GE::Math::Matrix4x4::RotationY(yaw);
	direction = GE::Math::Matrix4x4::Transform(direction, rotation);

	GE::Math::Axis axis = rotation.GetAxis();

	info.viewMatrix = GE::Math::Matrix4x4::GetViewMatrixLookTo(fixPos, direction, axis.y);
	info.projMatrix = GE::Math::Matrix4x4::GetPerspectiveMatrix(90, aspect, 1, 20000);

	info.cameraPos = fixPos;
	info.cameraDir = direction;
}

void PlayerCamera::SetPrePosition(const GE::Math::Vector3& pos)
{
	prePos = pos;
}

void PlayerCamera::SetDeltaTime(float value)
{
	deltaTime = value;
}
