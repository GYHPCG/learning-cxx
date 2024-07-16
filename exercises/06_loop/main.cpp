#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(int i) {
    // TODO: 为缓存设置正确的初始值
    static unsigned long long cache[128], cached = 2;
    cache[0] = 0, cache[1] = 1;
    // TODO: 设置正确的循环条件
    for (; (int)cached <= i; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }
    return cache[i];
}

int main(int argc, char **argv) {
    auto fib100 = fibonacci(100);
    ASSERT(fib100 == 3736710778780434371, "fibonacci(100) should be 3736710778780434371");
    std::cout << "fibonacci(100) = " << fib100 << std::endl;
    return 0;
}
