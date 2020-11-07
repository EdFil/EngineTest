#pragma once

#include <vector>
#include <utility>
#include <algorithm>

template <typename Type, typename Data>
class EventDispatcher {
public:
    class Observer {
    public:
        virtual void onEventCalled(const Type& type, const Data& data) = 0;
    };

public:
    /**  */
    void Subscribe(Observer& observer);

    /**  */
    void Unsubscribe(Observer& observer);

    /**  */
    void Signal(const Type& type, const Data& data);

private:
    enum class DelayedAction { Subscribe, Unsubscribe };

    std::vector<Observer*> _observers;
    std::vector<std::pair<DelayedAction, Observer*>> _delayedActions;
    bool _isRunning;
};

// --------------

template<typename Type, typename Data>
void EventDispatcher<Type, Data>::Subscribe(EventDispatcher::Observer& observer) {
    if (_isRunning) {
        _delayedActions.emplace_back(DelayedAction::Subscribe, &observer);
    } else {
        _observers.emplace_back(&observer);
    }
}

template<typename Type, typename Data>
void EventDispatcher<Type, Data>::Unsubscribe(EventDispatcher::Observer &observer) {
    if (_isRunning) {
        _delayedActions.emplace_back(DelayedAction::Unsubscribe, &observer);
    } else {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), &observer));
    }
}

template<typename Type, typename Data>
void EventDispatcher<Type, Data>::Signal(const Type &type, const Data &data) {
    _isRunning = true;
    for (Observer* observer : _observers) {
        observer->onEventCalled(type, data);
    }
    _isRunning = false;

    if (!_delayedActions.empty()) {
        for (size_t i = 0; i < _delayedActions.size(); ++i) {
            switch (_delayedActions[i].first) {
                case DelayedAction::Subscribe:
                    Subscribe(*_delayedActions[i].second);
                    break;
                case DelayedAction::Unsubscribe:
                    Unsubscribe(*_delayedActions[i].second);
                    break;
                default:
                    break;

            }
        }

        _delayedActions.resize(0);
    }
}

