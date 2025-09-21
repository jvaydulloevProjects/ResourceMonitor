#include "Producer.hpp"

template <typename T>
 void Producer<T>::run(T task)
{
    tasks_->push(task);
}
