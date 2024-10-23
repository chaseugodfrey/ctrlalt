/**
 * @file EventBus.inl
 * @brief Inline implementations of EventBus template methods
 */

 // EventCallback implementation
template <typename TOwner, typename TEvent>
EventCallback<TOwner, TEvent>::EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction)
    : ownerInstance(ownerInstance), callbackFunction(callbackFunction) {
}

template <typename TOwner, typename TEvent>
void EventCallback<TOwner, TEvent>::Call(Event& e) {
    std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
}

// EventBus template method implementations
template <typename TEvent, typename TOwner>
void EventBus::SubscribeToEvent(TOwner* ownerInstance, void(TOwner::* callbackFunction)(TEvent&)) {
    if (!subscribers[typeid(TEvent)].get()) {
        subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
    }
    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
    subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
}

template <typename TEvent, typename ...TArgs>
void EventBus::EmitEvent(TArgs&& ...args) {
    auto handlers = subscribers[typeid(TEvent)].get();
    if (handlers) {
        for (auto it = handlers->begin(); it != handlers->end(); ++it) {
            auto handler = it->get();
            TEvent event(std::forward<TArgs>(args)...);
            handler->Execute(event);
        }
    }
}