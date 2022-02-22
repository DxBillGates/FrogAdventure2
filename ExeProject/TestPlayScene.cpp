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
	, isSetPlayerCamera(false)
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
	{
		auto* gameObject = gameObjectManager.AddGameObject(new GE::GameObject());
		movingLengthWatcherComponent = gameObject->AddComponent<MovingLengthWatcherComponent>();
	}

	gameObjectManager.Awake();
}

TestPlayScene::~TestPlayScene()
{
}

void TestPlayScene::Initialize()
{
	changeSceneInfo.flag = false;
	gameObjectManager.Awake();
	gameObjectManager.Start();

	isSetPlayerCamera = false;

	const float MAX_START_TIME = 1;
	startFlagController.Initialize();
	startFlagController.SetMaxTimeProperty(MAX_START_TIME);
	startFlagController.SetFlag(true);
}

void TestPlayScene::Update(float deltaTime)
{
	if (!isSetPlayerCamera)
	{
		GE::GraphicsDeviceDx12* gDevice = dynamic_cast<GE::GraphicsDeviceDx12*>(graphicsDevice);
		gDevice->SetMainCamera(playerCameraComponent->GetCamera());
		isSetPlayerCamera = true;
	}

	if (startFlagController.GetOverTimeTrigger())
	{
		startFlagController.SetFlag(false);
	}

	if (playerComponent->IsReturnStageSelectScene())
	{
		changeSceneInfo.flag = true;
		changeSceneInfo.initNextSceneFlag = false;
		changeSceneInfo.name = "TestScene";
	}

	gameObjectManager.Update(deltaTime);

	movingLengthWatcherComponent->SetMovingLength(playerComponent->GetGameObject()->GetTransform()->position.x);

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
