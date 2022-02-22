#include "TestPlayScene.h"
#include "Header/Graphics/GraphicsDeviceDx12.h"

TestPlayScene::TestPlayScene()
	: TestPlayScene("TestPlayScene")
{
}

TestPlayScene::TestPlayScene(const std::string& sceneName)
	: Scene(sceneName)
	, playerComponent(nullptr)
	, playerCameraComponent(nullptr)
{
	{
		auto* gameObject = gameObjectManager.AddGameObject(new GE::GameObject());
		gameObject->SetDrawAxisEnabled(true);
		playerComponent = gameObject->AddComponent<PlayerComponent>();
		playerComponent->SetIsPlayScene(true);
		playerCameraComponent = gameObject->AddComponent<PlayerCameraComponent>();
		playerCameraComponent->SetPitch(90);
		playerCameraComponent->SetIsPlayScene(true);
	}
}

TestPlayScene::~TestPlayScene()
{
}

void TestPlayScene::Initialize()
{
	gameObjectManager.Awake();
	gameObjectManager.Start();

	GE::GraphicsDeviceDx12* gDevice = dynamic_cast<GE::GraphicsDeviceDx12*>(graphicsDevice);
	gDevice->SetMainCamera(playerCameraComponent->GetCamera());

	const float MAX_START_TIME = 1;
	startFlagController.Initialize();
	startFlagController.SetMaxTimeProperty(MAX_START_TIME);
	startFlagController.SetFlag(true);
}

void TestPlayScene::Update(float deltaTime)
{
	if (startFlagController.GetOverTimeTrigger())
	{
		startFlagController.SetFlag(false);
	}

	gameObjectManager.Update(deltaTime);

	startFlagController.Update(deltaTime);
}

void TestPlayScene::Draw()
{
	gameObjectManager.Draw();
}

void TestPlayScene::LateDraw()
{
	gameObjectManager.LateDraw();
}
