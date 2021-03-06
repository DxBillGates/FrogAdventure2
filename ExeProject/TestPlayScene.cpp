#include "TestPlayScene.h"
#include "Header/Graphics/GraphicsDeviceDx12.h"
#include "Header/GameFramework/Component/SphereCollider.h"
#include "StageClearEvent.h"
#include "GameSetting.h"

TestPlayScene::TestPlayScene()
	: TestPlayScene("TestPlayScene")
{
}

TestPlayScene::TestPlayScene(const std::string& sceneName)
	: Scene(sceneName)
	, playerComponent(nullptr)
	, playerCameraComponent(nullptr)
	, isSetPlayerCamera(false)
	, isClear(false)
{
	// このステージの長さ
	const float MAX_MOVING_LENGTH = 10000;
	{
		auto* gameObject = gameObjectManager.AddGameObject(new GE::GameObject());
		gameObject->SetDrawAxisEnabled(true);
		auto* collider = gameObject->AddComponent<GE::SphereCollider>();
		playerComponent = gameObject->AddComponent<PlayerComponent>();
		playerComponent->SetIsPlayScene(true);
		playerCameraComponent = gameObject->AddComponent<PlayerCameraComponent>();
		playerCameraComponent->SetPitch(90);
		playerCameraComponent->SetIsPlayScene(true);
		collisionManager.AddCollider(gameObject, collider, GameObjectCollisionType::PLAYER);
	}
	{
		auto* gameObject = gameObjectManager.AddGameObject(new GE::GameObject());
		movingLengthWatcherComponent = gameObject->AddComponent<MovingLengthWatcherComponent>();
		movingLengthWatcherComponent->SetMovingUIMaxLength(MAX_MOVING_LENGTH);
	}
	{
		auto* gameObject = gameObjectManager.AddGameObject(new GE::GameObject());
		gameObject->SetTag("HelpingObject");
		gameObject->GetTransform()->position = { MAX_MOVING_LENGTH,0,0 };
		gameObject->GetTransform()->scale = { 100 };
		auto* collider = gameObject->AddComponent<GE::SphereCollider>();
		collisionManager.AddCollider(gameObject, collider, GameObjectCollisionType::STAGE_CLEAR);
	}

	auto* testEvent = new StageClearEvent();
	eventManager.Add(testEvent, "testEvent");

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
	isClear = false;

	GameSetting::GetInstance()->SetGameTime(1);
	eventManager.Initialize();
}

void TestPlayScene::Update(float deltaTime)
{
	if (!isSetPlayerCamera)
	{
		GE::GraphicsDeviceDx12* gDevice = dynamic_cast<GE::GraphicsDeviceDx12*>(graphicsDevice);
		gDevice->SetMainCamera(playerCameraComponent->GetCamera());
		isSetPlayerCamera = true;
	}

	if (playerComponent->IsReturnStageSelectScene())
	{
		if (!isClear)
		{
			eventManager.SetEvent("testEvent");
			isClear = true;
		}

		if (eventManager.Get("testEvent")->IsEnd())
		{
			changeSceneInfo.flag = true;
			changeSceneInfo.initNextSceneFlag = false;
			changeSceneInfo.name = "TestScene";
			GameSetting::GetInstance()->SetGameTime(1);
		}
	}

	collisionManager.Update();
	gameObjectManager.Update(deltaTime);
	eventManager.Update(deltaTime);

	movingLengthWatcherComponent->SetMovingLength(playerComponent->GetGameObject()->GetTransform()->position.x);
}

void TestPlayScene::Draw()
{
	gameObjectManager.Draw();
}

void TestPlayScene::LateDraw()
{
	gameObjectManager.LateDraw();
}
