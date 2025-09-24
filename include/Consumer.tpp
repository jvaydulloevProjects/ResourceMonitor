#include "Consumer.hpp"

template <typename T>
void Consumer<T>::run(IEventManager<T>& event,IWriteable<T>& file)
{
    while (true)
    {
        auto maybeData = tasks_->pop(event, stop_);
        if (!maybeData) break; 
        auto& data = *maybeData;
        processFunc(data);
        file.write(data);
        event.invoke(EventType::TaskProcessed);         
    }
}
