#include <iostream>

#include "Logger.h"
#include "TaskQueue.h"

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
    fibonacciTasks.add([]() { return runFibonacci(20); });
    fibonacciTasks.add([]() { return runFibonacci(21); });
    fibonacciTasks.add([]() { return runFibonacci(22); });
    while (fibonacciTasks.size()) {
        auto task = fibonacciTasks.get();
        task();
    }

    return 0;
}