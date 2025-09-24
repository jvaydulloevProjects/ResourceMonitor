#pragma once
#include <functional>
#include <cstddef>


enum class EventType
{
    TaskAdded,
    TaskRemoved,
    TaskProcessed
};

// Writer interface
template<typename T>
class IWriteable {
public:
    virtual ~IWriteable() = default;
    virtual void write(const T& value) = 0;
};

// EventManager interface
template<typename T>
class IEventManager {
public:
    virtual ~IEventManager() = default;
    virtual std::size_t subscribe(EventType type, std::function<void()> handler) = 0;
    virtual void unsubscribe(EventType type, std::size_t id) = 0;
    virtual void invoke(EventType) = 0;
};



// Producer interface
template<typename T>
class IProducable {
public:
    virtual ~IProducable() = default;
    virtual void run(T& task, IEventManager<T>& event) = 0;
};

// Consumer interface
template<typename T>
class IConsumable {
public:
    virtual ~IConsumable() = default;
    virtual void run(IEventManager<T>& event,IWriteable<T>& write) = 0;
    virtual void stop() = 0;
};

// Reader interface
template<typename T>
class IReadable {
public:
    virtual ~IReadable() = default;
    virtual void read(IEventManager<T>& event,
                      IProducable<T>& producer,
                      IConsumable<T>& consumer) = 0;
};


