#include "MovingLengthWatcherComponent.h"

MovingLengthWatcherComponent::MovingLengthWatcherComponent()
	: movingLength(0)
	, movingMaxLength(10000)
	, movingUIMaxLength(1000)
	, offset(GE::Math::Vector3(1920/2,1080/20,0))
{
}

MovingLengthWatcherComponent::~MovingLengthWatcherComponent()
{
}

void MovingLengthWatcherComponent::Start()
{
	movingLength = 0;
}

void MovingLengthWatcherComponent::Update(float deltaTime)
{
}

void MovingLengthWatcherComponent::Draw()
{
	GE::Math::Vector3 uiStartPos = offset - GE::Math::Vector3(movingUIMaxLength / 2, 0,0);
	GE::Math::Vector3 uiEndPos = offset + GE::Math::Vector3(movingUIMaxLength / 2, 0, 0);
	float persent = movingLength / movingMaxLength;

	GE::Math::Vector3 drawPlayerUIPos = GE::Math::Vector3::Lerp(uiStartPos, uiEndPos, persent);

	GE::ICBufferAllocater* cbufferAllocater = graphicsDevice->GetCBufferAllocater();
	GE::RenderQueue* renderQueue = graphicsDevice->GetRenderQueue();

	graphicsDevice->SetShader("DefaultSpriteShader");

	// プレイシーン全体の長さを描画
	const float HEIGHT = 10;
	GE::Math::Matrix4x4 modelMatrix = GE::Math::Matrix4x4::Scale({ movingUIMaxLength,HEIGHT,0 });
	modelMatrix *= GE::Math::Matrix4x4::Translate({ offset });
	GE::Material material;
	material.color = GE::Color::White();
	GE::CameraInfo cameraInfo;
	cameraInfo.viewMatrix = GE::Math::Matrix4x4::GetViewMatrixLookTo({ 0,1,0 }, { 0,0,1 }, { 0,1,0 });
	cameraInfo.projMatrix = GE::Math::Matrix4x4::GetOrthographMatrix({ 1920,1080 });

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1, &cameraInfo, sizeof(GE::CameraInfo)) });
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(GE::Material)) });
	graphicsDevice->DrawMesh("2DPlane");

	// プレイヤーが現在どこにいるかを上で描画したUIの上に表示
	float scale = 20;
	modelMatrix = GE::Math::Matrix4x4::Identity();
	modelMatrix *= GE::Math::Matrix4x4::Scale(scale);
	modelMatrix *= GE::Math::Matrix4x4::Translate(drawPlayerUIPos);
	material.color = GE::Color::Red();

	renderQueue->AddSetConstantBufferInfo({ 0,cbufferAllocater->BindAndAttachData(0, &modelMatrix, sizeof(GE::Math::Matrix4x4)) });
	renderQueue->AddSetConstantBufferInfo({ 1,cbufferAllocater->BindAndAttachData(1, &cameraInfo, sizeof(GE::CameraInfo)) });
	renderQueue->AddSetConstantBufferInfo({ 2,cbufferAllocater->BindAndAttachData(2,&material,sizeof(GE::Material)) });
	graphicsDevice->DrawMesh("2DPlane");
}

void MovingLengthWatcherComponent::SetMovingLength(float value)
{
	movingLength = value;
	if (movingLength < 0)movingLength = 0;
	if (movingLength > movingMaxLength)movingLength = movingMaxLength;
}

void MovingLengthWatcherComponent::SetMovingUIMaxLength(float value)
{
	movingUIMaxLength = value;
	if (movingUIMaxLength < 0)movingUIMaxLength = 0;
	if (movingUIMaxLength > 1080)movingUIMaxLength = 1080;
}

void MovingLengthWatcherComponent::SetOffset(const GE::Math::Vector3& offset)
{
	this->offset = offset;
}
