#pragma once


#include <vector>
#include <unordered_map>
#include "Observer/IObserver.h"
#include "Observer/EventTypes.h"

// the subject the Observer is observing
class Observed
{
private:
	/// List of observers
	// typedef std::vector<std::reference_wrapper<IObserver>> ObserverList;
	// do not use references because Observer could have been destroyed
	typedef std::vector<IObserver*> ObserverList;
	typedef std::unordered_map<EventType, ObserverList> observersTable;

public:
	/// adds/registers observer to the evtHandler
	void registerObserver(IObserver* observer, EventType eType);

	/// send Event/Signal
	void sendEvent(EventType event);

	/// update events
	void update();

private:
	//map of observers for specific event type
	observersTable m_observers;
	//list of happend events
	std::vector<EventType> m_events;
};