#pragma once

#include <cstddef>
#include <memory>
#include <chrono>
#include <vector>
#include <functional>
#include <utility>
#include "interfaces.hpp"


struct Delegate
{
    std::size_t id;               // уникальный идентификатор
    std::function<void()> func;   // функция без параметров
};

template<typename T>
class Event
{
   private:

    EventType type_;
    std::chrono::system_clock::time_point timestamp;
    std::vector<Delegate> subscribers;

   public:

    Event() = default;
    ~Event() = default;

    Event(EventType type)
    : type_(type), timestamp(std::chrono::system_clock::now())
    {}

    std::size_t subscribe(std::function<void()> func)
    {
        static std::size_t nextId = 0;
        Delegate d{ ++nextId, std::move(func) };
        subscribers.push_back(std::move(d));
        return d.id; 
    }
    void unsubscribe(std::size_t id)
    {

         subscribers.erase(
            std::remove_if(subscribers.begin(), subscribers.end(),
                   [&](const auto& h){ return h.id == id; }),
            subscribers.end()
        );
    }
    void execute()
    {
        for(auto& it: subscribers)
        {
            it.func();
        }
    }

    EventType getType() const { return type_; }
    auto getTimestamp() const { return timestamp; }

    
};