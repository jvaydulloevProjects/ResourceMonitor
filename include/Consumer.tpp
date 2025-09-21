#include "Consumer.hpp"

template <typename T>
void Consumer<T>::run()
{
    tasks_->pop();
}