//
// Created by Hassan Attar on 2024-01-25.
//

#include "Node.cpp"
#include <initializer_list>
#include "RandomCoinFlip.h"
template<typename T>
class SkipList {
    Node<T> **heads;
    RandomCoinFlip *randomCoinFlip;
    int size;
    static int maxLevel;
    static const int DEFAULT_MAX_LEVEL;

    Node<T> *find(const T &item, Node<T> **update = nullptr);
public:
    int randomLevel();
    void displayHeadToTail();
    void displayLevelByLevel();
    SkipList();
    int getSize();
    static void setMaxLevel(int l);

    SkipList(const std::initializer_list<T> &list);
    void insert(const T &item);
    void insertVerbose(const T &item);
    const Node<T> *binarySearch(const T &item);
    const Node<T> *binarySearchVerbose(const T &item);
    const Node<T> *linearSearch(const T &item);
    const Node<T>* linearSearchVerbose(const T &item);
    T remove(const T &item);
    T removeVerbose(const T &item);
};

