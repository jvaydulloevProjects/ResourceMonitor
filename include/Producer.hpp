#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "TaskQueue.hpp"
#include <memory>
#include <iostream>
#include "interfaces.hpp"


template<typename T>
class Producer: public IProducable<T>
{
private:
    std::shared_ptr<TaskQueue<T>> tasks_;

public:
    inline Producer(std::shared_ptr<TaskQueue<T>> tasks):tasks_(tasks){};
    ~Producer(){std::cout<<"Destructor Producer \n";};

    void run(T& task,IEventManager<T>& event) override;
};

#include "Producer.tpp"
#endif
