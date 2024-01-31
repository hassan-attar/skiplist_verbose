//
// Created by Hassan Attar on 2024-01-25.
//


template<typename T>
class Node {
public:
    Node<T> **next; // 8 bytes
    int level;
    T data; // max 8 bytes on this pc
    explicit Node(const T &data);
    Node(const T &data, int _level);
};
