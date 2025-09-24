#include "Producer.hpp"

template <typename T>
 void Producer<T>::run(T& task,IEventManager<T>& event)
{
    tasks_->push(task);
    event.invoke(EventType::TaskAdded);
}
