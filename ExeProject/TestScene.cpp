#include "TestScene.h"
#include "PlayerComponent.h"
#include "RotateOwnAxisComponent.h"
#include "PlayerCameraComponent.h"
#include "Header/Graphics/GraphicsDeviceDx12.h"

TestScene::TestScene()
	: TestScene("TestScene")
{
}

TestScene::TestScene(const std::string& sceneName)
	: Scene(sceneName)
	, playerComponent(nullptr)
	, playerCameraComponent(nullptr)
	, isSetPlayerCamera(false)
{
	{
		auto* gameObject = gameObjectManager.AddGameObject(new GE::GameObject());
		gameObject->SetDrawAxisEnabled(true);
		playerComponent = gameObject->AddComponent<PlayerComponent>();
		playerCameraComponent = gameObject->AddComponent<PlayerCameraComponent>();
	}

	gameObjectManager.Awake();
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	gameObjectManager.Awake();
	gameObjectManager.Start();

	isSetPlayerCamera = false;
}

void TestScene::Update(float deltaTime)
{
	if (!isSetPlayerCamera)
	{
		GE::GraphicsDeviceDx12* gDevice = dynamic_cast<GE::GraphicsDeviceDx12*>(graphicsDevice);
		gDevice->SetMainCamera(playerCameraComponent->GetCamera());
		isSetPlayerCamera = true;
	}

	if (inputDevice->GetKeyboard()->CheckHitKey(GE::Keys::D9))
	{
		changeSceneInfo.flag = true;
		changeSceneInfo.initNextSceneFlag = true;
		changeSceneInfo.name = "TestPlayScene";
		isSetPlayerCamera = false;
	}

	gameObjectManager.Update(deltaTime);
}

void TestScene::Draw()
{
	gameObjectManager.Draw();
}

void TestScene::LateDraw()
{
	gameObjectManager.LateDraw();
}
