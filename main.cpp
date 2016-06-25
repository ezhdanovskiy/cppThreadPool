#include <iostream>

#include "Logger.h"
#include "TaskQueue.h"
#include "ThreadPool.h"

using namespace std;

typedef std::function<void(size_t)> FibonacciTask;

long long fibonacci(int i) {
    if (i == 0) return 0;
    if (i == 1) return 1;
    return fibonacci(i - 1) + fibonacci(i - 2);
}

void runFibonacci(int i, size_t threadId) {
    LOG("worker(" << threadId << ") fibonacci(" << i << ")=" << fibonacci(i));
};

int main() {
    TaskQueue<FibonacciTask> fibonacciTasks;
    for (int i = 42; i >= 39; --i) {
        fibonacciTasks.add([i](size_t threadId) { runFibonacci(i, threadId); });
    }

    ThreadPool<FibonacciTask> threadPool(4, fibonacciTasks);

    for (int j = 0; j < 5; ++j) {
        for (int i = 35; i > 20; --i) {
            fibonacciTasks.add([i](size_t threadId) { runFibonacci(i, threadId); });
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}