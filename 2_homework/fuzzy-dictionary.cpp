#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int LevenshteinDistance(const std::string& str_first,
                        const std::string& str_second) {
    int first_size = str_first.length();
    int second_size = str_second.length();
    std::vector<std::vector<int>> dp(first_size + 1,
                                     std::vector<int>(second_size + 1));

    for (int idx = 0; idx <= first_size; ++idx) {
        for (int jdx = 0; jdx <= second_size; ++jdx) {
            if (idx == 0) {
                dp[idx][jdx] = jdx;
            } else if (jdx == 0) {
                dp[idx][jdx] = idx;
            } else {
                dp[idx][jdx] = std::min(
                    {dp[idx - 1][jdx] + 1, dp[idx][jdx - 1] + 1,
                     dp[idx - 1][jdx - 1] +
                         (str_first[idx - 1] == str_second[jdx - 1] ? 0 : 1)});
            }
        }
    }
    return dp[first_size][second_size];
}

struct BKNode {
    std::string word;
    std::unordered_map<int, BKNode*> children;

    explicit BKNode(const std::string& str) : word(str) {}

    ~BKNode() {
        for (std::pair<const int, BKNode*>& child : children) {
            delete child.second;
        }
    }
};

class BKTree {
public:
    BKTree(int (*dist_func)(const std::string&, const std::string&))
        : root_(nullptr), distance_func_(dist_func) {}

    ~BKTree() { delete root_; }

    void Insert(const std::string& word) {
        if (root_ == nullptr) {
            root_ = new BKNode(word);
            return;
        }

        BKNode* current = root_;
        while (current != nullptr) {
            int dist = distance_func_(word, current->word);
            if (dist == 0) {
                return;
            }

            auto it = current->children.find(dist);
            if (it == current->children.end()) {
                current->children[dist] = new BKNode(word);
                return;
            }
            current = it->second;
        }
    }

    std::vector<std::pair<std::string, int>> Search(const std::string& word,
                                                    int max_dist) {
        std::vector<std::pair<std::string, int>> results;
        if (root_ == nullptr) {
            return results;
        }

        std::vector<BKNode*> candidates = {root_};
        while (!candidates.empty()) {
            BKNode* node = candidates.back();
            candidates.pop_back();

            int dist = distance_func_(word, node->word);
            if (dist <= max_dist) {
                results.emplace_back(node->word, dist);
            }

            for (auto& child : node->children) {
                if (dist - max_dist <= child.first &&
                    child.first <= dist + max_dist) {
                    candidates.push_back(child.second);
                }
            }
        }
        return results;
    }

private:
    BKNode* root_;
    int (*distance_func_)(const std::string&, const std::string&);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int dictionary_number;
    std::cin >> dictionary_number;
    std::vector<std::string> dictionary(dictionary_number);
    for (size_t i = 0; i < dictionary.size(); ++i) {
        std::cin >> dictionary[i];
    }

    BKTree bk_tree(LevenshteinDistance);
    for (size_t i = 0; i < dictionary.size(); ++i) {
        bk_tree.Insert(dictionary[i]);
    }

    int query_number;
    std::cin >> query_number;
    for (int idx = 0; idx < query_number; ++idx) {
        std::string query;
        std::cin >> query;

        if (find(dictionary.begin(), dictionary.end(), query) !=
            dictionary.end()) {
            std::cout << query << "\n";
            continue;
        }

        std::vector<std::pair<std::string, int>> results =
            bk_tree.Search(query, 2);
        if (results.empty()) {
            std::cout << "-1\n";
        } else {
            auto min_it =
                min_element(results.begin(), results.end(),
                            [](const std::pair<std::string, int>& first_pair,
                               const std::pair<std::string, int>& second_pair) {
                                return first_pair.second < second_pair.second;
                            });
            std::cout << min_it->first << "\n";
        }
    }

    return 0;
}
