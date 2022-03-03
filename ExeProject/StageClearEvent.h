#pragma once
#include "Event.h"
#include "Header/GameFramework/FlagController.h"

class StageClearEvent : public Event
{
private:
	GE::FlagController flag;
	GE::FlagController startFlagController;
private:
	void SlowGameTime();
public:
	StageClearEvent();
	~StageClearEvent();
	void Initialize() override;
	void Update(float deltaTime) override;
};

