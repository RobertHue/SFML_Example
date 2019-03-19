#include "Observer/Observed.h"



void Observed::registerObserver(IObserver* observer, EventType eType)
{
	m_observers[eType].push_back(observer);
}


void Observed::sendEvent(EventType event)
{
	m_events.push_back(event);
}

void Observed::update()
{
	for (auto e : m_events)
	{
		for (auto& o : m_observers[e])
		{
			o->notify(e);
		}
	}
	m_events.clear();
}
