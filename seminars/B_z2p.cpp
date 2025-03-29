#include <algorithm>
#include <iostream>
#include <vector>

std::vector<size_t> ZToPrefix(const std::vector<size_t>& z_function) {
    std::vector<size_t> prefix_function(z_function.size(), 0);
    size_t right_border = 0;
    for (size_t i = 1; i < z_function.size(); ++i) {
        for (size_t j = right_border + 1;
             j < z_function.size() && j <= i + z_function[i] - 1; ++j) {
            prefix_function[j] = j - i + 1;
            right_border = std::max(right_border, i + z_function[i] - 1);
        }
    }

    return prefix_function;
}

int main() {
    size_t number;
    std::cin >> number;

    std::vector<size_t> z_function(number);
    for (size_t i = 0; i < number; ++i) {
        std::cin >> z_function[i];
    }

    std::vector<size_t> prefix_function = ZToPrefix(z_function);
    for (size_t i = 0; i < prefix_function.size(); ++i) {
        std::cout << prefix_function[i] << " ";
    }
    std::cout << "\n";
    return 0;
}