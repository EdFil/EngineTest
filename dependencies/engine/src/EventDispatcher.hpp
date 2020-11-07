#pragma once

#include <vector>
#include <algorithm>

template <typename Type, typename Data>
class EventDispatcher {
public:
    class Observer {
    public:
        virtual void onEventCalled(const Type& type, const Data& data) = 0;
    };

public:
    void Subscribe(Observer& observer) { _observers.push_back(&observer); }
    void Unsubscribe(Observer& observer) { _observers.erase(std::remove(_observers.begin(), _observers.end(), &observer)); }

    void Signal(const Type& type, const Data& data) {
        for (Observer* observer : _observers) {
            observer->onEventCalled(type, data);
        }
    }

private:
    std::vector<Observer*> _observers;
};