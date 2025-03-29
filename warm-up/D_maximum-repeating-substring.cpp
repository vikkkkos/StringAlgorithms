#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

size_t MaximumRepeatingSubstring(const std::string& str) {
    size_t k_repeatition = 1;

    for (size_t start_index = 0; start_index < str.length(); ++start_index) {
        std::string suffix = str.substr(start_index);
        std::vector<size_t> prefix_str(suffix.length());
        prefix_str[0] = 0;

        for (size_t index = 1; index < suffix.length(); ++index) {
            char symbol = suffix[index];
            size_t prefix = prefix_str[index - 1];
            while (prefix > 0 && symbol != suffix[prefix]) {
                prefix = prefix_str[prefix - 1];
            }
            if (symbol == suffix[prefix]) {
                ++prefix;
            }
            prefix_str[index] = prefix;

            size_t length = index + 1;
            size_t number_of_symbols = length - prefix;

            if (length % number_of_symbols == 0) {
                k_repeatition =
                    std::max(k_repeatition, length / number_of_symbols);
            }
        }
    }
    return k_repeatition;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_str;
    std::cin >> input_str;

    size_t answer = MaximumRepeatingSubstring(input_str);
    std::cout << answer << "\n";
    return 0;
}
