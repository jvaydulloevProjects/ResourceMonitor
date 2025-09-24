#include "TaskQueue.hpp"



template <typename T>
void TaskQueue<T>::push(T& task)
{
    {
        std::unique_lock<std::mutex> lg(m);
        queue_.push(task);
    }
    cv.notify_one();
    
}
template <typename T>
std::optional<T> TaskQueue<T>::pop(IEventManager<T>& event, std::atomic<bool>& stop)
{
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, [this, &stop]() { return !queue_.empty() || stop; });

    if (queue_.empty() && stop)
        return std::nullopt;

    T item = queue_.front();
    queue_.pop();
    event.invoke(EventType::TaskRemoved);
    
    if(queue_.empty())
            cv.notify_all();
    
    return item;
}
