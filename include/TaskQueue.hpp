#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class TaskQueue
{
private:
    std::queue<T> queue_;
    std::mutex m;
    std::condition_variable cv;
public:
    TaskQueue()=default;
    ~TaskQueue()=default;

    void push(T task);
    T pop();
};

#endif

