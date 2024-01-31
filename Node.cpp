//
// Created by Hassan Attar on 2024-01-25.
//


#ifndef SKIPLIST_NODE_H
#define SKIPLIST_NODE_H
#include "Node.h"

template<typename T>
Node<T>::Node(const T &data): Node(data, 0) {}

template<typename T>
Node<T>::Node(const T &data, int _level): next{new Node<T>*[_level + 1]}, level{_level}, data{data} {}

#endif //SKIPLIST_NODE_H
