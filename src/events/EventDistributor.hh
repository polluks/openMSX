// $Id$

#ifndef EVENTDISTRIBUTOR_HH
#define EVENTDISTRIBUTOR_HH

#include "Event.hh"
#include "Semaphore.hh"
#include "shared_ptr.hh"
#include <map>
#include <vector>

namespace openmsx {

class Reactor;
class EventListener;
class EmuTime;

class EventDistributor
{
public:
	typedef shared_ptr<const Event> EventPtr;

	explicit EventDistributor(Reactor& reactor);
	virtual ~EventDistributor();

	/**
	 * Registers a given object to receive certain events.
	 * @param type The type of the events you want to receive.
	 * @param listener Listener that will be notified when an event arrives.
	 */
	void registerEventListener(EventType type, EventListener& listener);
	/**
	 * Unregisters a previously registered event listener.
	 * @param type The type of the events the listener should no longer receive.
	 * @param listener Listener to unregister.
	 */
	void unregisterEventListener(EventType type, EventListener& listener);

	void distributeEvent(EventPtr event);
	void deliverEvents();

private:
	Reactor& reactor;

	typedef std::multimap<EventType, EventListener*> ListenerMap;
	ListenerMap detachedListeners;
	typedef std::vector<EventPtr> EventQueue;
	EventQueue scheduledEvents;
	Semaphore sem;
};

} // namespace openmsx

#endif
