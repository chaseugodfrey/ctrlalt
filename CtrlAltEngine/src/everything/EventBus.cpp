/**
 * @file EventBus.cpp
 * @author Michael Lazaroo
 * @email m.lazaroo@digipen.edu
 * @brief
 * @brief Implementation of non-template EventBus functionality
 */
#include "../src/pch.h"
#include "EventBus.h"

namespace Event {

    void IEventCallback::Execute(Event& e) {
        Call(e);
    }

    EventBus::EventBus() {
        Logger::LogInfo("EventBus created");
    }

    EventBus::~EventBus() {
        Logger::LogInfo("EventBus destroyed");
    }

    void EventBus::Reset() {
        subscribers.clear();
    }

} // namespace Event