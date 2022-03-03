#include "StageClearEvent.h"
#include "GameSetting.h"
#include "Header/Util/Math/Math.h"
#include "Header/Input/InputDevice.h"

void StageClearEvent::SlowGameTime()
{
	if (!startFlagController.GetFlag())return;

	GameSetting* gameSetting = GameSetting::GetInstance();

	const float SLOW_TIME = 0.1f;
	float easingValue = GE::Math::Easing::EaseInExpo(startFlagController.GetTime());
	gameSetting->SetGameTime(GE::Math::Lerp(1, SLOW_TIME, easingValue));
}

StageClearEvent::StageClearEvent()
{
}

StageClearEvent::~StageClearEvent()
{
}

void StageClearEvent::Initialize()
{
	const float MAX_STAGE_CLEAR_TIME = 10000;
	flag.Initialize();
	flag.SetMaxTimeProperty(MAX_STAGE_CLEAR_TIME);
	flag.SetFlag(true);

	const float MAX_START_FLAG_TIME = 0.5f;
	startFlagController.Initialize();
	startFlagController.SetMaxTimeProperty(MAX_START_FLAG_TIME);
	startFlagController.SetFlag(true);

	SetEventFlag(true);
	SetEndFlag(false);
}

void StageClearEvent::Update(float deltaTime)
{
	if (flag.GetOverTimeTrigger())SetEndFlag();
	if (startFlagController.GetOverTimeTrigger())startFlagController.SetFlag(false);

	if (!startFlagController.GetFlag())
	{
		bool isInputButton = false;
		GE::InputDevice* inputDevice = GE::InputDevice::GetInstance();
		if (inputDevice->GetKeyboard()->CheckHitKeyAll())isInputButton = true;
		if (inputDevice->GetXCtrler()->CheckHitAllButton())isInputButton = true;

		if (isInputButton)SetEndFlag();
	}

	SlowGameTime();

	flag.Update(deltaTime);
	startFlagController.Update(deltaTime);
}
