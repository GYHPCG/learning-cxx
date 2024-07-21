#include <iostream>
#include <vector>
int main() {
    std::vector<double> vec{1, 2, 3, 4, 5};
    std::cout << sizeof(vec) << std::endl;
    std::cout << vec.size() * sizeof(double) << std::endl;
    return 0;
}