#include <iostream>

#include "Logger.h"
#include "TaskQueue.h"
#include "ThreadPool.h"

using namespace std;

typedef std::function<long long(void)> FibonacciTask;

long long fibonacci(int i) {
    if (i == 0) return 0;
    if (i == 1) return 1;
    return fibonacci(i - 1) + fibonacci(i - 2);
}

long long runFibonacci(int i) {
    long long res = fibonacci(i);
    LOG("fibonacci(" << i << ")=" << res);
    return res;
};

int main() {
    TaskQueue<FibonacciTask> fibonacciTasks;
    for (int i = 41; i > 0; --i) {
        fibonacciTasks.add([i]() { return runFibonacci(i); });
    }
    ThreadPool<FibonacciTask> threadPool(4, fibonacciTasks);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    return 0;
}