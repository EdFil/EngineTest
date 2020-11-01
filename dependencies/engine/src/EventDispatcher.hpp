#pragma once

#include <vector>

template <typename T>
class EventDispatcher {
public:
    void queueEvent(const T& event);
    bool popEvent(T& event);

private:
    std::vector<T> _queuedEvents;
};

// -----------------

template <typename T>
void EventDispatcher<T>::queueEvent(const T& event) {
    _queuedEvents.push_back(event);
}

template <typename T>
bool EventDispatcher<T>::popEvent(T& event) {
    if (_queuedEvents.empty()) return false;

    event = _queuedEvents.back();
    _queuedEvents.pop_back();
    return true;
}