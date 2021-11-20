#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// n - size of vector
// min - minimum value
// max - maximum value
std::vector<int> createVector(int n, int min, int max) {
    std::random_device rd;                              // only used once to initialise (seed) engine
    std::mt19937 rng(rd());                             // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max);   // guaranteed unbiased
    std::vector<int> result(n);

    for (int i = 0; i < n; ++i) {
        result[i] = uni(rng);
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& container) {
    using namespace std::literals;
    for (const auto& value : container) {
        out << value << " "s;
    }
    return out;
}
