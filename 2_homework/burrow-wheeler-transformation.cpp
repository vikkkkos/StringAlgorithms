#include <iostream>
#include <string>
#include <vector>

class Transformator {
public:
    explicit Transformator(const std::string& in) : in_(in), size_(in_.size()) {
        bwt_ = in_;
        suffix_array_.resize(in_.size());
        classes_.resize(GetClassesSize());
        for (auto& item : classes_) {
            item.resize(in_.size());
        }
    }

    std::vector<int>& SuffixArray() {
        InitSuffixArray();
        int n_classes = InitClasses();
        MainLoop(n_classes);

        return suffix_array_;
    }
    std::string& BurrowsWheelerTransform() {
        SuffixArray();
        for (int i = 0; i < size_; ++i) {
            const int kIdx =
                (suffix_array_[i] > 0) ? suffix_array_[i] - 1 : size_ - 1;
            bwt_[i] = in_[kIdx];
        }

        return bwt_;
    }

private:
    void InitSuffixArray() {
        const int kAlphabetLength = 'z' - 'a' + 1;
        const char kFirstLetter = 'a';

        std::vector<int> scores(kAlphabetLength);

        for (const auto& item : in_) {
            ++scores[item - kFirstLetter];
        }
        for (int i = 1; i < kAlphabetLength; ++i) {
            scores[i] += scores[i - 1];
        }
        for (int i = size_ - 1; i >= 0; --i) {
            const int kIdx = in_[i] - kFirstLetter;
            --scores[kIdx];
            suffix_array_[scores[kIdx]] = i;
        }
    }
    int GetClassesSize() {
        std::vector<int> sizes(in_.size() + 1);

        sizes[0] = -1;
        for (int i = 1; i <= size_; ++i) {
            sizes[i] = sizes[i / 2] + 1;
        }

        return sizes[size_] + 1;
    }
    int InitClasses() {
        int num_classes = 0;

        classes_[0][suffix_array_[0]] = 0;
        for (int i = 1; i < size_; ++i) {
            if (in_[suffix_array_[i]] != in_[suffix_array_[i - 1]]) {
                ++num_classes;
            }
            classes_[0][suffix_array_[i]] = num_classes;
        }

        return num_classes + 1;
    }
    void MainLoop(int n_classes) {
        std::vector<int> buffer(in_.size());
        for (int iter = 0;; ++iter) {
            std::vector<int> scores(n_classes, 0);
            for (int i = 0; i < size_; ++i) {
                ++scores[classes_[iter][i]];
            }
            for (int i = 1; i < n_classes; ++i) {
                scores[i] += scores[i - 1];
            }

            const int kShift = 1 << iter;
            buffer = suffix_array_;
            for (int i = size_ - 1; i >= 0; --i) {
                int idx = buffer[i] - kShift;
                if (idx < 0) {
                    idx += size_;
                }
                --scores[classes_[iter][idx]];
                suffix_array_[scores[classes_[iter][idx]]] = idx;
            }

            if (size_ <= 2 * kShift) {
                break;
            }

            int local_n_classes = 0;

            classes_[iter + 1][suffix_array_[0]] = local_n_classes;
            for (int idx = 1; idx < size_; ++idx) {
                const int kCurrentIdx = suffix_array_[idx];
                const int kPrevIdx = suffix_array_[idx - 1];
                const int kShiftedCurrentIdx = (kCurrentIdx + kShift) % size_;
                const int kShiftedPrevIdx = (kPrevIdx + kShift) % size_;

                if (classes_[iter][kCurrentIdx] != classes_[iter][kPrevIdx] ||
                    classes_[iter][kShiftedCurrentIdx] !=
                        classes_[iter][kShiftedPrevIdx]) {
                    ++local_n_classes;
                }
                classes_[iter + 1][kCurrentIdx] = local_n_classes;
            }

            n_classes = local_n_classes + 1;
        }
    }

    const std::string& in_;
    int size_;
    std::string bwt_;
    std::vector<int> suffix_array_;
    std::vector<std::vector<int>> classes_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::cin >> input;

    Transformator transformator{input};
    std::cout << transformator.BurrowsWheelerTransform() << std::endl;

    return 0;
}
