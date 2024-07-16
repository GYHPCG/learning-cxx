#include "../exercise.h"

int func(int param) {
    static int static_ = param;
    std::cout << "static_ = " << static_++ << std::endl;
    return static_;
}

int main(int argc, char **argv) {
    ASSERT(func(5) == 6, "static variable value incorrect");
    ASSERT(func(4) == 7, "static variable value incorrect");
    ASSERT(func(3) == 8, "static variable value incorrect");
    ASSERT(func(2) == 9, "static variable value incorrect");
    ASSERT(func(1) == 10, "static variable value incorrect");
    return 0;
}
