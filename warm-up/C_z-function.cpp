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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::cin >> input;

    std::vector<size_t> answer = ZFunction(input);
    for (size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
