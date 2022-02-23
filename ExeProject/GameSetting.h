#pragma once

class GameSetting
{
private:
	GameSetting* instance;
	float gameTime;
	float startPlaySceneTime;
	float startStageSelectTime;
public:
	static GameSetting* GetInstance();
	float GetGameTime();
	float GetStartPlaySceneTime();
	float GetStageSelectTime();
	void SetGameTime(float value);
protected:
	GameSetting();
	GameSetting(const GameSetting&) = delete;
	~GameSetting() = default;
	GameSetting& operator=(const GameSetting&) = delete;
};
