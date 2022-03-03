#include "EventManager.h"

EventManager::EventManager()
	: currentEvent(nullptr)
	, beforeEvent(nullptr)
{
}

EventManager::~EventManager()
{
}

void EventManager::Initialize()
{
	beforeEvent = currentEvent = nullptr;
	for (auto& event : mapList)
	{
		event.second->Initialize();
	}
}

void EventManager::Update(float deltaTime)
{
	if (!currentEvent)return;

	currentEvent->Update(deltaTime);
}

void EventManager::SetEvent(const std::string& eventName)
{
	beforeEvent = currentEvent;
	currentEvent = mapList.at(eventName);

	currentEvent->Initialize();
	currentEvent->SetEventFlag();
}

void EventManager::Reset()
{
	beforeEvent = currentEvent;
	currentEvent = nullptr;
}
