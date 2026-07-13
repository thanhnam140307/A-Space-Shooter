#include "stdafx.h"
#include "Publisher.h"
#include "Subscriber.h"
#include <iostream>

std::multimap<Event, std::reference_wrapper<Subscriber> >  Publisher::subscribers;
void Publisher::addSubscriber(Subscriber& subscriber, Event event)
{
	auto t = std::make_pair(event, std::reference_wrapper<Subscriber>(subscriber));
	subscribers.insert(t);
	//std::cout << "subscribers: " << subscribers.size() << std::endl;
}

void Publisher::removeSubscriber(Subscriber& subscriber, Event event)
{
	auto t = std::make_pair(event, std::reference_wrapper<Subscriber>(subscriber));
	std::multimap<Event, std::reference_wrapper<Subscriber> >::iterator it = subscribers.equal_range(event).first;
	while (it != subscribers.equal_range(event).second)
	{
		if (&(it->second.get()) == &subscriber && event == it->first)
		{
			subscribers.erase(it);
			break;
		}
		it++;
	}
}

void Publisher::notifySubscribers(Event event, const void* data)
{
	std::multimap<Event, std::reference_wrapper<Subscriber> >::iterator it = subscribers.equal_range(event).first;
	while (it != subscribers.equal_range(event).second)
	{
		it->second.get().notify(event, data);
		it++;
	}
}
