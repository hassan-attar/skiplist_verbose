//
// Created by Hassan Attar on 2024-01-25.
//
#ifndef SKIPLIST_SKIPLIST_VERBOSE_H
#define SKIPLIST_SKIPLIST_VERBOSE_H

#include "skiplist/SkipList.h"
template<typename T>
class SkipListVerbose : public SkipList<T>{
public:
    SkipListVerbose();
    explicit SkipListVerbose(size_t maxLevel);
    SkipListVerbose(const std::initializer_list<T> &list);
    SkipListVerbose(const SkipListVerbose<T> &rhs);
    SkipListVerbose(SkipListVerbose<T> &&rhs) noexcept ;
    ~SkipListVerbose() = default;
    SkipListVerbose<T> &operator=(const SkipListVerbose<T> &rhs);
    SkipListVerbose<T> &operator=(SkipListVerbose<T> &&rhs) noexcept;

    void insertVerbose(const T &item);
    typename SkipList<T>::iterator findVerbose(const T &item);
    typename SkipList<T>::iterator linearSearchVerbose(const T &item);
    bool removeVerbose(const T &item);
};

#include "SkipListVerbose.tpp"

#endif //SKIPLIST_SKIPLIST_VERBOSE_H