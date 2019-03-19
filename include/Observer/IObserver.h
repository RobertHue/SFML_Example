#pragma once

#include "Observer/EventTypes.h"

class IObserver
{
public:
	// catchEvent/Signal/Notify Observer
	virtual void notify(EventType e) = 0;
};
