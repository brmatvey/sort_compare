#include "sort_algo.h"

void sort::bubble(std::vector<int> &vector) {
    for (size_t i = 0; i + 1 < vector.size(); ++i) {
        for (size_t j = 0; j + 1 < vector.size(); ++j) {
            if (vector[j + 1] < vector[j]) {
                std::swap(vector[j], vector[j + 1]);
            }
        }
    }
}

void sort::shaker(std::vector<int> &vector) {
    if (vector.empty()) {
        return;
    }
    int left = 0;
    int right = vector.size() - 1;
    while (left <= right) {
        for (int i = right; i > left; --i) {
            if (vector[i-1] > vector[i]) {
                std::swap(vector[i - 1], vector[i]);
            }
        }
        ++left;
        for (int i = left; i < right; ++i) {
            if (vector[i] > vector[i + 1]) {
                std::swap(vector[i], vector[i + 1]);
            }
        }
        --right;
    }
}

void sort::comb(std::vector<int> &vector) {
    const double factor = 1.247; // Фактор уменьшения
    double step = vector.size() - 1;
    while (step >= 1) {
        for (int i = 0; i + step < vector.size(); ++i) {
            if (vector[i] > vector[i + step]) {
                std::swap(vector[i], vector[i + step]);
            }
        }
        step /= factor;
    }
    // сортировка пузырьком
    for (size_t idx_i = 0; idx_i + 1 < vector.size(); ++idx_i) {
        for (size_t idx_j = 0; idx_j + 1 < vector.size() - idx_i; ++idx_j) {
            if (vector[idx_j + 1] < vector[idx_j]) {
                std::swap(vector[idx_j], vector[idx_j + 1]);
            }
        }
    }
}

void sort::insertion(std::vector<int>& vector) {
    for (size_t i = 1; i < vector.size(); ++i) {
        int x = vector[i];
        size_t j = i;
        while (j > 0 && vector[j - 1] > x) {
            vector[j] = vector[j - 1];
            --j;
        }
        vector[j] = x;
    }
}

void sort::selection(std::vector<int>& vector) {
    for (auto i = vector.begin(); i != vector.end(); ++i) {
        auto j = std::min_element(i, vector.end());
        std::swap(*i, *j);
    }
}

int Partition(std::vector<int>& values, int l, int r) {
    int x = values[r];
    int less = l;

    for (int i = l; i < r; ++i) {
        if (values[i] <= x) {
            std::swap(values[i], values[less]);
            ++less;
        }
    }
    std::swap(values[less], values[r]);
    return less;
}

void QuickSortImpl(std::vector<int>& values, int l, int r) {
    if (l < r) {
        int q = Partition(values, l, r);
        QuickSortImpl(values, l, q - 1);
        QuickSortImpl(values, q + 1, r);
    }
}

void sort::quick(std::vector<int>& values) {
    if (!values.empty()) {
        QuickSortImpl(values, 0, values.size() - 1);
    }
}

void MergeSortImpl(std::vector<int>& values, std::vector<int>& buffer, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        MergeSortImpl(values, buffer, l, m);
        MergeSortImpl(values, buffer, m + 1, r);

        int k = l;
        for (int i = l, j = m + 1; i <= m || j <= r; ) {
            if (j > r || (i <= m && values[i] < values[j])) {
                buffer[k] = values[i];
                ++i;
            } else {
                buffer[k] = values[j];
                ++j;
            }
            ++k;
        }
        for (int i = l; i <= r; ++i) {
            values[i] = buffer[i];
        }
    }
}

void sort::merge(std::vector<int>& vector) {
    if (!vector.empty()) {
        std::vector<int> buffer(vector.size());
        MergeSortImpl(vector, buffer, 0, vector.size() - 1);
    }
}

void sort::heap(std::vector<int>& vector) {
    std::make_heap(vector.begin(), vector.end());
    for (auto i = vector.end(); i != vector.begin(); --i) {
        std::pop_heap(vector.begin(), i);
    }
}
