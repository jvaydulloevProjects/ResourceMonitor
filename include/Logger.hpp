#pragma once

#include <memory>
#include <chrono>

enum class EventType
{
    TaskAdded,
    TaskRemoved,
    TaskProcessed
};

template<typename T>
class Event
{
    EventType type;
    std::shared_ptr<T> task;
    std::chrono::system_clock::time_point timestamp;
};