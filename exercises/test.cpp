#include <iostream>
#include <vector>
int main() {
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::cout << sizeof(vec) << std::endl;
    std::cout << vec.size() * sizeof(int) << std::endl;
    return 0;
}