#include "Event.h"

Event::Event()
	: isEvent(false)
	, isEnd(false)
{
}

Event::~Event()
{
}

void Event::SetEventFlag(bool flag)
{
	isEvent = flag;
}

void Event::SetEndFlag(bool flag)
{
	isEnd = flag;
}

bool Event::IsEvent()
{
	return isEvent;
}

bool Event::IsEnd()
{
	return isEnd;
}
