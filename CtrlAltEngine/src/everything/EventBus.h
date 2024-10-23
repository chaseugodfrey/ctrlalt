/**
 * @file EventBus.h
 * @author Michael Lazaroo
 * @email m.lazaroo@digipen.edu
 * @brief Header file for the EventBus system implementing the Publisher-Subscriber pattern
 *
 * The EventBus system provides a decoupled way for different parts of the application
 * to communicate through events. It uses template metaprogramming to allow type-safe
 * event subscription and emission.
 */

#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"
#include <map>
#include <typeindex>
#include <list>
#include <memory>
#include "Event.h"

namespace Event {

    /**
     * @brief Interface for event callback functions
     *
     * This abstract class provides a common interface for all event callbacks,
     * allowing them to be stored and executed polymorphically regardless of
     * their specific event type.
     */
    class IEventCallback {
    private:
        virtual void Call(Event& e) = 0;
    public:
        virtual ~IEventCallback() = default;
        void Execute(Event& e);
    };

    /**
     * @brief Wrapper class for member function callbacks
     *
     * @tparam TOwner The class type that owns the callback method
     * @tparam TEvent The event type this callback handles
     */
    template <typename TOwner, typename TEvent>
    class EventCallback : public IEventCallback {
    private:
        typedef void (TOwner::* CallbackFunction)(TEvent&);
        TOwner* ownerInstance;
        CallbackFunction callbackFunction;

        virtual void Call(Event& e) override;

    public:
        EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction);
        virtual ~EventCallback() override = default;
    };

    // Type alias for a list of event handlers
    using HandlerList = std::list<std::unique_ptr<IEventCallback>>;

    /**
     * @brief Main EventBus class that manages event subscriptions and emissions
     *
     * The EventBus maintains a mapping of event types to their respective handlers.
     * It provides methods to subscribe to events and emit events to all subscribers.
     */
    class EventBus {
    private:
        // Maps event types to their list of handlers
        std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

    public:
        EventBus();
        ~EventBus();

        /**
         * @brief Clears all event subscriptions
         */
        void Reset();

        /**
         * @brief Subscribe to an event type with a member function callback
         *
         * @tparam TEvent The event type to subscribe to
         * @tparam TOwner The class type that owns the callback method
         * @param ownerInstance Pointer to the instance that will handle the event
         * @param callbackFunction Member function pointer to the event handler
         */
        template <typename TEvent, typename TOwner>
        void SubscribeToEvent(TOwner* ownerInstance, void(TOwner::* callbackFunction)(TEvent&));

        /**
         * @brief Emit an event to all subscribers
         *
         * @tparam TEvent The type of event to emit
         * @tparam TArgs Types of arguments to forward to the event constructor
         * @param args Arguments to forward to the event constructor
         */
        template <typename TEvent, typename ...TArgs>
        void EmitEvent(TArgs&& ...args);
    };

    // Template implementations
#include "EventBus.inl"

} // namespace Event

#endif // EVENTBUS_H