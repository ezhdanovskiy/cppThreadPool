#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

template<class Task>
class ThreadPool {
    typedef TaskQueue<Task> TTaskQueue;

    std::vector<std::thread> workers;
    TTaskQueue &tasks;
    std::mutex tasksMutex;
    bool stopFlag;

public:
    ThreadPool(const size_t threadCnt, TTaskQueue &taskQueue) : tasks(taskQueue), stopFlag(false) {
        LOG(__func__ << " Ctor start");
        for (size_t threadId = 0; threadId < threadCnt; ++threadId) {
            workers.emplace_back(std::thread([this, threadId]() {
                LOG("worker(" << threadId << ") start");
                while (!stopFlag) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(tasksMutex);
                        if (tasks.size()) {
                            task = tasks.get();
                        }
                    }
                    if (task) {
                        task(threadId);
                    }
                }
                LOG("worker(" << threadId << ") end");
            }));
        }
        LOG(__func__ << " Ctor end");
    }

    ~ThreadPool() {
        stopFlag = true;
        for (std::thread &worker : workers) {
            worker.join();
        }
        LOG(__func__ << " end");
    }
};

#endif //THREADPOOL_THREADPOOL_H