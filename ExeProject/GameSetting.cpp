#include "GameSetting.h"

GameSetting* GameSetting::GetInstance()
{
	static GameSetting gameSetting;
	return &gameSetting;
}

float GameSetting::GetGameTime()
{
	return gameTime;
}

float GameSetting::GetStartPlaySceneTime()
{
	return startPlaySceneTime;
}

float GameSetting::GetStageSelectTime()
{
	return startStageSelectTime;
}

void GameSetting::SetGameTime(float value)
{
	gameTime = value;
}

GameSetting::GameSetting()
	: instance(nullptr)
	, gameTime(1)
	, startPlaySceneTime(1)
	, startStageSelectTime(1)
{
}
