#pragma once

class Event
{
private:
	bool isEvent;
	bool isEnd;
public:
	Event();
	virtual ~Event() = 0;
	virtual void Initialize() {}
	virtual void Update(float deltaTime) {}
	void SetEventFlag(bool flag = true);
	void SetEndFlag(bool flag = true);
	bool IsEvent();
	bool IsEnd();
};

