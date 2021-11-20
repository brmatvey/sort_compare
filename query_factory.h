#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <set>

//#include "vector_processing.h"

namespace sort {

// enumeration of sort types
enum class Type {
    Bubble,
    Shaker,
    Comb,
    Insertion,
    Selection,
    Quick,
    Merge,
    Heap
};

inline static std::set<Type> ALL_TYPES = {Type::Bubble
                                         ,Type::Shaker
                                         ,Type::Comb
                                         ,Type::Insertion
                                         ,Type::Selection
                                         ,Type::Quick
                                         ,Type::Merge
                                         ,Type::Heap};

std::string typeToString(Type type);

// abstract sort algorithm
class Algoritm {
public:
    Algoritm(int n, int step = 10)
        : n_(n)
        , step_(step)
    {

    }

    virtual ~Algoritm() = default;

    // returns an array of sort times with a step interval of elements
    virtual std::vector<double> Process() const;
protected:
    virtual void doSort(std::vector<int>& vector) const = 0;

    int n_;
    int step_ = 10;
};

// abstract factory
class Factory {
public:
    virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const = 0;
    virtual ~Factory() = default;
    static const Factory& getFactory(Type type);
};

// implementation sorting algorithm (https://academy.yandex.ru/posts/osnovnye-vidy-sortirovok-i-primery-ikh-realizatsii)
class Bubble final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

class Shaker final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

class Comb final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

class Insertion final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

class Selection final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

class Quick final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

class Merge final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

class Heap final : public Algoritm {
public:
    using Algoritm::Algoritm;

    class Factory : public sort::Factory {
    public:
        virtual std::unique_ptr<Algoritm> Construct(int n, int step = 10) const override;
    };
protected:
    virtual void doSort(std::vector<int>& vector) const override;
};

} // namespace sort
