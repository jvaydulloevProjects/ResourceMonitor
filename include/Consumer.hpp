#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include "interfaces.hpp"
#include <memory>
#include "EventManager.hpp"
#include "TaskQueue.hpp"
#include <iostream>
#include <chrono>
#include <atomic>
#include "FileReader.hpp"

template<typename T>
class Consumer : public IConsumable<T>
{
private:
    std::shared_ptr<TaskQueue<T>> tasks_;
    std::atomic<bool> stop_ = false;
    std::function<void(T&)> processFunc;

public:
    explicit Consumer(std::shared_ptr<TaskQueue<T>> tasks,std::function<void(T&)> processFunc)
        : tasks_(tasks),processFunc(processFunc) {}

    ~Consumer() {std::cout<<"Destructor Consumer \n";};

    void stop() override {  
            stop_ = true; 
            tasks_->notifyAll();
    }
    void run(IEventManager<T>& event,IWriteable<T>& file) override;
};

#include "Consumer.tpp"
#endif
