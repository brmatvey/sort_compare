#include "query_factory.h"

#include <unordered_map>

#include "sort_algo.h"
#include "log_duration.h"

#include "vector_processing.h"

std::string sort::typeToString(Type type) {
    using namespace std::string_literals;
    static std::unordered_map<sort::Type, const std::string> factories = {{sort::Type::Bubble, "bubble"s},
                                                                          {sort::Type::Shaker, "shaker"s},
                                                                          {sort::Type::Comb, "comb"s},
                                                                          {sort::Type::Insertion, "insertion"s},
                                                                          {sort::Type::Selection, "selection"s},
                                                                          {sort::Type::Quick, "quick"s},
                                                                          {sort::Type::Merge, "merge"s},
                                                                          {sort::Type::Heap, "heap"s}};
    return factories.at(type);
}

std::vector<double> sort::Algoritm::Process() const {
    // результат записываем сюда
    std::vector<double> result;
    result.reserve(n_ / step_);
    for (int i = 0; i < n_; i += step_) {
        std::vector<int> v = createVector(i, 0, 10);
        LogDuration log;
        doSort(v);
        result.push_back(log.getDuration());
    }
    return result;
}

// implementation difference sort
void sort::Bubble::doSort(std::vector<int> &vector) const {
    sort::bubble(vector);
}

void sort::Shaker::doSort(std::vector<int> &vector) const {
    sort::shaker(vector);
}

void sort::Comb::doSort(std::vector<int> &vector) const {
    sort::comb(vector);
}

void sort::Insertion::doSort(std::vector<int> &vector) const {
    sort::insertion(vector);
}

void sort::Selection::doSort(std::vector<int> &vector) const {
    sort::selection(vector);
}

void sort::Quick::doSort(std::vector<int> &vector) const {
    sort::quick(vector);
}

void sort::Merge::doSort(std::vector<int> &vector) const {
    sort::merge(vector);
}

void sort::Heap::doSort(std::vector<int> &vector) const {
    sort::heap(vector);
}

// make algorithm fabrique
std::unique_ptr<sort::Algoritm> sort::Bubble::Factory::Construct(int n, int step) const {
    return std::make_unique<Bubble>(n, step);
}

std::unique_ptr<sort::Algoritm> sort::Shaker::Factory::Construct(int n, int step) const {
    return std::make_unique<Shaker>(n, step);
}

std::unique_ptr<sort::Algoritm> sort::Comb::Factory::Construct(int n, int step) const {
    return std::make_unique<Comb>(n, step);
}

std::unique_ptr<sort::Algoritm> sort::Insertion::Factory::Construct(int n, int step) const {
    return std::make_unique<Insertion>(n, step);
}

std::unique_ptr<sort::Algoritm> sort::Selection::Factory::Construct(int n, int step) const {
    return std::make_unique<Selection>(n, step);
}

std::unique_ptr<sort::Algoritm> sort::Quick::Factory::Construct(int n, int step) const {
    return std::make_unique<Quick>(n, step);
}

std::unique_ptr<sort::Algoritm> sort::Merge::Factory::Construct(int n, int step) const {
    return std::make_unique<Merge>(n, step);
}

std::unique_ptr<sort::Algoritm> sort::Heap::Factory::Construct(int n, int step) const {
    return std::make_unique<Heap>(n, step);
}

const sort::Factory& sort::Factory::getFactory(Type type) {
    static sort::Bubble::Factory bubble;
    static sort::Shaker::Factory shaker;
    static sort::Comb::Factory comb;
    static sort::Insertion::Factory insertion;
    static sort::Selection::Factory selection;
    static sort::Quick::Factory quick;
    static sort::Merge::Factory merge;
    static sort::Heap::Factory heap;
    static std::unordered_map<sort::Type, const sort::Factory&> factories = {{sort::Type::Bubble, bubble},
                                                                             {sort::Type::Shaker, shaker},
                                                                             {sort::Type::Comb, comb},
                                                                             {sort::Type::Insertion, insertion},
                                                                             {sort::Type::Selection, selection},
                                                                             {sort::Type::Quick, quick},
                                                                             {sort::Type::Merge, merge},
                                                                             {sort::Type::Heap, heap}};
    return factories.at(type);
}
