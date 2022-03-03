#pragma once
#include "Event.h"
#include "Header/Util/Manager.h"

class EventManager : public GE::Manager<Event>
{
private:
	Event* currentEvent;
	Event* beforeEvent;
public:
	EventManager();
	~EventManager();
	void Initialize();
	void Update(float deltaTime);
	void SetEvent(const std::string& eventName);
	void Reset();
};

