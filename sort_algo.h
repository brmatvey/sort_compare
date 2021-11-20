#pragma once
#include <vector>
#include <algorithm>

namespace sort {
// bubble sort, complexity o(n
void bubble(std::vector<int> &vector);
// shaker sort, complexity o(n2)
void shaker(std::vector<int> &vector);
// comb sorting, complexity o(n2)
void comb(std::vector<int> &vector);
// complexity o(n2)
void insertion(std::vector<int> &vector);
// complexity o(n2)
void selection(std::vector<int> &vector);
// complexity o(n2) (average o(nlogn)
void quick(std::vector<int> &vector);
// complexity o(nlogn)
void merge(std::vector<int> &vector);
// complexity o(nlogn)
void heap(std::vector<int> &vector);
} // namespace sort
