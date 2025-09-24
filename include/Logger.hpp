#pragma once
#include "EventManager.hpp"
#include <iostream>

template<typename T>
class Logger {
private:
    std::mutex logMutex;
    int logCount;

public:
    Logger(IEventManager<T>& manager){
        logCount=0;
        manager.subscribe(EventType::TaskAdded, [this]() { log("Task Added"); });
        manager.subscribe(EventType::TaskRemoved, [this]() { log("Task Removed"); });
        manager.subscribe(EventType::TaskProcessed, [this]() { log("Task Processed"); });
    }

    ~Logger() =default;

    void log(const std::string& message) {
        std::cout <<++logCount<<" [Logger] " << message << std::endl;
    }
};