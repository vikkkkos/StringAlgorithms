#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> ZFunction(const std::string& str) {
    std::vector<size_t> z_function(str.size());
    size_t left = 0;
    size_t right = 0;
    for (size_t ind = 1; ind < str.size(); ++ind) {
        if (ind <= right) {
            z_function[ind] = std::min(right - ind + 1, z_function[ind - left]);
        }
        while (ind + z_function[ind] < str.size() &&
               str[z_function[ind]] == str[ind + z_function[ind]]) {
            ++z_function[ind];
        }
        if (ind + z_function[ind] - 1 > right) {
            left = ind;
            right = ind + z_function[ind] - 1;
        }
    }
    z_function[0] = str.size();

    return z_function;
}

size_t MaximumPeriod(const std::string& str) {
    std::vector<size_t> z_function = ZFunction(str);
    for (size_t i = 1; i < str.size(); ++i) {
        if (i + z_function[i] == z_function.size() &&
            z_function.size() % i == 0) {
            return z_function.size() / i;
        }
    }
    return 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::cin >> input;

    size_t answer = MaximumPeriod(input);
    std::cout << answer << "\n";
    return 0;
}
