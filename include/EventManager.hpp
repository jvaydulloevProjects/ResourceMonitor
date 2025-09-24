#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Event.hpp"
#include <unordered_map>
#include <memory>
#include <mutex>
#include "interfaces.hpp"



template<typename T>
using unMapEvent =std::unordered_map<EventType,std::shared_ptr<Event<T>>>;


template<typename T>
class EventManager:public IEventManager<T>
{
private:
    unMapEvent<T> events;
    std::mutex mt;
public:
    EventManager()
    {
        events[EventType::TaskAdded]=std::make_shared<Event<T>>(EventType::TaskAdded);
        events[EventType::TaskProcessed]=std::make_shared<Event<T>>(EventType::TaskProcessed);
        events[EventType::TaskRemoved]=std::make_shared<Event<T>>(EventType::TaskRemoved);
    };
    ~EventManager()=default;

    std::size_t subscribe(EventType type, std::function<void()> handler) override
    {
        std::lock_guard<std::mutex> lock(mt);
        if(events.find(type) == events.end())return 0;
        return events[type]->subscribe(handler);
    }

    void unsubscribe(EventType type, std::size_t id) override
    {
        std::lock_guard<std::mutex> lock(mt);

        auto it = events.find(type);
        if (it != events.end())
            it->second->unsubscribe(id);
    };

    
    void invoke(EventType type) override
    {
        std::lock_guard<std::mutex> lock(mt);
        auto it = events.find(type);
        if (it != events.end())
            it->second->execute();
    }


};


#endif