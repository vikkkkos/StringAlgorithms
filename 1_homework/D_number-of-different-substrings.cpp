#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> BuildSuffixArray(const std::string& str) {
    std::vector<int> suffix_array(str.size());
    std::vector<int> rank(str.size());
    std::vector<int> temp(str.size());

    for (size_t i = 0; i < str.size(); ++i) {
        suffix_array[i] = i;
        rank[i] = str[i];
    }

    for (size_t kdx = 1; kdx < str.size(); kdx *= 2) {
        auto cmp = [&](int idx, int jdx) {
            if (rank[idx] != rank[jdx]) {
                return rank[idx] < rank[jdx];
            }
            int ri = (idx + kdx < str.size()) ? rank[idx + kdx] : -1;
            int rj = (jdx + kdx < str.size()) ? rank[jdx + kdx] : -1;
            return ri < rj;
        };
        std::sort(suffix_array.begin(), suffix_array.end(), cmp);

        temp[suffix_array[0]] = 0;
        for (size_t i = 1; i < str.size(); ++i) {
            temp[suffix_array[i]] =
                temp[suffix_array[i - 1]] +
                (cmp(suffix_array[i - 1], suffix_array[i]) ? 1 : 0);
        }
        rank = temp;
    }

    return suffix_array;
}

std::vector<int> BuildLcp(const std::string& str,
                          const std::vector<int>& suffix_array) {
    std::vector<int> lcp(str.size());
    std::vector<int> rank(str.size());

    for (size_t i = 0; i < str.size(); ++i) {
        rank[suffix_array[i]] = i;
    }

    size_t hdx = 0;
    for (size_t idx = 0; idx < str.size(); ++idx) {
        if (rank[idx] > 0) {
            int jdx = suffix_array[rank[idx] - 1];
            while (idx + hdx < str.size() && jdx + hdx < str.size() &&
                   str[idx + hdx] == str[jdx + hdx]) {
                ++hdx;
            }
            lcp[rank[idx]] = hdx;
            if (hdx > 0) {
                --hdx;
            }
        }
    }

    return lcp;
}

int64_t CountDistinctSubstrings(const std::string& str) {
    std::vector<int> suffix_array = BuildSuffixArray(str);
    std::vector<int> lcp = BuildLcp(str, suffix_array);

    int64_t total = static_cast<int64_t>(str.size()) * (str.size() + 1) / 2;
    int64_t duplicates = 0;
    for (size_t i = 1; i < str.size(); ++i) {
        duplicates += lcp[i];
    }

    return total - duplicates;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::cin >> input;

    std::cout << CountDistinctSubstrings(input) << "\n";

    return 0;
}
