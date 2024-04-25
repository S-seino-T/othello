#pragma once
#include "util.hpp"


template<typename T>
class tree
{
    T value;
public:
    tree(T);
    ~tree();
    T var();

    vector<tree<T>> node;
};
