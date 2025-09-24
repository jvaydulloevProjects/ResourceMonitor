#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>
#include <optional>
#include <iostream>
#include <atomic>
#include "interfaces.hpp"


template<typename T>
class TaskQueue
{
private:
    std::queue<T> queue_;
    std::mutex m;
    std::condition_variable cv;
public:
    TaskQueue()=default;
    ~TaskQueue(){std::cout<<"Destructor TaskQueue \n";};

    void push(T& task);
    std::optional<T> pop(IEventManager<T>& event, std::atomic<bool>& stop);
    bool taskIsEmpty(){return queue_.empty();};
    void notifyAll() {cv.notify_all();}
};

#include "TaskQueue.tpp"
#endif

