#include "TaskQueue.hpp"

template <typename T>
void TaskQueue<T>::push(T task)
{
    {
        std::unique_lock<std::mutex> lg(m);
        queue_.push(task);
    }
    cv.notify_one();
    
}
template <typename T>
T TaskQueue<T>::pop()
{
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul,[this](){ return !queue_.empty();})
    T item = queue_.front();
    queue_.pop();
    return item;
}