#ifndef THREADPOOL_TASKQUEUE_H
#define THREADPOOL_TASKQUEUE_H

#include <functional>
#include <queue>

template<class Task>
class TaskQueue {
    std::queue<Task> tasks;

public:
    void add(const Task &task) {
        tasks.push(task);
    }

    Task get() {
        Task task = tasks.front();
        tasks.pop();
        return task;
    }

    size_t size() {
        return tasks.size();
    }
};

#endif //THREADPOOL_TASKQUEUE_H
