#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "TaskQueue.hpp"
#include <memory>


template<typename T>
class Producer
{
private:
    std::shared_ptr<TaskQueue> tasks_;

public:
    inline Producer(std::shared_ptr<TaskQueue> tasks):tasks_(tasks){};
    ~Producer()=default;

    void run(T task);
};

#endif

