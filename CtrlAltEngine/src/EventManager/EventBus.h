/**
 * @file EventBus.h
 * @brief
 * EventBus is a map of event types and a list of wrapper classes for callback functions.
 *
 * This file defines the EventBus class, which is responsible for managing event subscriptions and emitting events.
 * The EventBus class uses a map to store event types as keys and a list of callback functions as values.
 * When an event is emitted, the corresponding callback functions are executed.
 *
 * The EventBus class also provides a template function, SubscribeToEvent, which allows users to subscribe to specific event types.
 * The SubscribeToEvent function takes a callback function as a parameter and associates it with the specified event type.
 *
 * Another template function, EmitEvent, is provided to emit events of a specific type.
 * The EmitEvent function retrieves the list of callback functions associated with the event type and executes them.
 *
 * This file also includes the Event and IEventCallback classes, which are used as base classes for events and callback functions respectively.
 * The Event class is a simple base class for all events, while the IEventCallback class is an interface for callback functions.
 *
 * The EventBus class is designed to be used as a singleton, with a single instance managing all event subscriptions and emissions.
 *
 */

#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"
#include <map>
#include <typeindex>
#include <list>
#include <memory>
#include "Event.h"

//Interface for the callback functions
//This is a pure virtual function that is used to call the callback functions
class IEventCallback
{
private:
	//Since EventCallback is a wrapper around a function pointer, we just need
	//to call the function pointer to execute the callback function, so we use a pure virtual function
	virtual void Call(Event& e) = 0;
public:
	virtual ~IEventCallback() = default;

	void Execute(Event& e)
	{
		Call(e);
	}
};

//Wrapper class for the callback functions
//Inherits from the interface
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback
{
private:
	//keep track of the function pointer
	//Each one of these callback functions, we keep track of the instance
	//of the function pointer, and what is the callback function that we need to invoke
	typedef void (TOwner::*CallbackFunction)(TEvent&);

	TOwner* ownerInstance;
	CallbackFunction callbackFunction;

	virtual void Call(Event& e) override
	{
		//main function call that  executes the function pointer
		//stdd::invoke takes something callabke and arguments to call with and does the call
		//std::invoke(function, args...)
		std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
	}
public:
	EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) : ownerInstance(ownerInstance), callbackFunction(callbackFunction) {}
	virtual ~EventCallback() override = default;
};

//Our EventBus has a map of keys and values and for each type of event we have a unique
//pointer to a list of callback functions that are called when an event is emitted.
using HandlerList = std::list<std::unique_ptr<IEventCallback>>;

class EventBus
{
private:
	/**
	* @brief A map of event types and their callbacks
	* To avoid order dependency, we use a key-value pair
	* so that arguments can appear in any order.
	* @param std::type_index The event type
	* 
	*/

	//A list of handlers is a list of callback functions that are called when an event is emitted.
	std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

public:

	EventBus()
	{
		Logger::LogInfo("EventBus created");
	}
	~EventBus()
	{
		Logger::LogInfo("EventBus destroyed");
	}

	/** 
	* @brief Subscribe to an event
	* @tparam T The event type
	* @param callback The callback function
	* Example: eventBus->SubscribeToEvent<LoggingEvent>([](LoggingEvent e);
	*/
	template <typename TEvent, typename TOwner>
	void SubscribeToEvent(TOwner* owner, void(TOwner::*callbackFunction)(TEvent&))
	{
		if (!subscribers[typeid(TEvent)].get())
		{
			subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
		}
		auto subscriber = std::make_unique<EventCallback<TOwner,TEvent>>(ownerInstance,callbackFunction);
		subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
	}

	/**
	* @brief Emit an event as soon as something happens and execute all the callbacks
	* @tparam T The event type
	* @param e The event
	* Example: eventBus->EmitEvent<LoggingEvent>();
	*/
	template <typename TEvent,typename ...TArgs>
	void EmitEvent(TArgs&& ...args)
	{
		//go thjrough every subscriber and execute the events
		auto handlers = subscribers[typeid(TEvent)].get();
		if (handlers) {
			for (auto it = handlers->begin(); it != handlers->end(); ++it)
			{
				auto handler = it->get();
				TEvent event(std::forward<TArgs>(args)...);
				handler->Execute(event);
			}
		}
	}
};


#endif