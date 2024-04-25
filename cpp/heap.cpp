#include "heap.hpp"

template<typename T>
tree<T>::tree(T a)
    :value(a)
    ,node(0)
{

}

template<typename T>
tree<T>::~tree()
{

}

template<typename T>
T tree<T>::var()
{
    return value;
}