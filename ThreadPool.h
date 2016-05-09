#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <vector>
#include <chrono>
#include <thread>

#include "TaskQueue.h"

typedef std::function<long long(void)> FibonacciTask;

class ThreadPool {
    typedef TaskQueue<FibonacciTask> FibonacciTaskQueue;

    std::vector<std::thread> workers;
    FibonacciTaskQueue &tasks;
    bool stopFlag;

public:
    ThreadPool(const size_t threadCnt, FibonacciTaskQueue &taskQueue) : tasks(taskQueue), stopFlag(false) {
        LOG(__func__ << " start");
        for (size_t threadId = 0; threadId < threadCnt; ++threadId) {
            workers.emplace_back(std::thread([this, threadId](){
                LOG("worker(" << threadId << ") start");
                while (!stopFlag) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                LOG("worker(" << threadId << ") end");
            }));
        }
        LOG(__func__ << " end");
    }
    ~ThreadPool() {
        stopFlag = true;
        for (std::thread &worker : workers) {
            worker.join();
        }
    }
};

#endif //THREADPOOL_THREADPOOL_H