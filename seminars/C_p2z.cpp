#include <algorithm>
#include <iostream>
#include <vector>

std::vector<size_t> PrefixToZ(const std::vector<size_t>& prefix_function) {
    std::vector<size_t> z_function(prefix_function.size());

    for (size_t index = 1; index < prefix_function.size(); ++index) {
        if (prefix_function[index] != 0) {
            z_function[index - prefix_function[index] + 1] =
                prefix_function[index];
        }
    }

    z_function[0] = prefix_function.size();
    if (z_function[1] != 0) {
        for (size_t index = 1; index < z_function[1]; ++index) {
            z_function[index + 1] = z_function[1] - index;
        }
    }
    for (size_t index = z_function[1] + 1; index < prefix_function.size() - 1;
         ++index) {
        if ((z_function[index] != 0) && (z_function[index + 1] == 0)) {
            size_t length = 1;

            while ((length < z_function[index]) &&
                   (z_function[index + length] <= z_function[length])) {
                z_function[index + length] =
                    std::min(z_function[length], z_function[index] - length);
                ++length;
            }
            index += --length;
        }
    }

    return z_function;
}

int main() {
    size_t number;
    std::cin >> number;

    std::vector<size_t> prefix_function(number);
    for (size_t i = 0; i < number; ++i) {
        std::cin >> prefix_function[i];
    }

    std::vector<size_t> z_function = PrefixToZ(prefix_function);
    for (size_t i = 0; i < z_function.size(); ++i) {
        std::cout << z_function[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
