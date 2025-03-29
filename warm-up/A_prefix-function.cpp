#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunction(const std::string& str) {
    std::vector<int> prefix_str(str.size());
    prefix_str[0] = 0;
    for (size_t i = 1; i < str.size(); ++i) {
        int start_index = prefix_str[i - 1];
        while (start_index > 0 && str[start_index] != str[i]) {
            start_index = prefix_str[start_index - 1];
        }
        if (str[start_index] == str[i]) {
            ++start_index;
        }
        prefix_str[i] = start_index;
    }
    return prefix_str;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_str;
    std::cin >> input_str;

    std::vector<int> answer = PrefixFunction(input_str);
    for (size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
