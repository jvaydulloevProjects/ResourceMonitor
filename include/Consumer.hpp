#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <memory>
#include "TaskQueue.hpp"

template<typename T>
class Consumer
{
private:
    std::shared_ptr<TaskQueue> tasks_;

public:
    inline Consumer(std::shared_ptr<TaskQueue> tasks):tasks_(tasks){};
    ~Consumer()=default;

    void run();
};

#endif
