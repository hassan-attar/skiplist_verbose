//
// Created by Hassan Attar on 2024-01-25.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H
#include "SkipList.h"
#include <cmath>
#include <iostream>
#include <iomanip>

template<typename T>
const int SkipList<T>::DEFAULT_MAX_LEVEL = 15;
template<typename T>
int SkipList<T>::maxLevel = DEFAULT_MAX_LEVEL;

/**
 * Initializer list constructor
 * @param list std::initializer_list<T>
 */
template<typename T>
SkipList<T>::SkipList(const std::initializer_list<T> &list)
:heads{new Node<T>*[maxLevel]}, randomCoinFlip{new RandomCoinFlip()}, size{0}{
    for(int i = 0; i < maxLevel; i++) heads[i] = nullptr;
    for(const T &x: list)
        insert(x);
}

/**
 * Default Constructor
 */
template<typename T>
SkipList<T>::SkipList():heads{new Node<T>*[maxLevel]}, randomCoinFlip{new RandomCoinFlip()}, size{0} {
    for(int i = 0; i < maxLevel; i++) heads[i] = nullptr;
}

/**
 * Returns a number between 0 (inclusive) and maxLevel (exclusive), representing the level to which the node will go up.
 * Probability of a node rising each level is 1/2
 * @return random level
 */
template<typename T>
int SkipList<T>::randomLevel() {
    int level = 0;
    while(level < maxLevel - 1){
        if(randomCoinFlip->flipCoin() == 0) break;
        level++;
    }
    return level;
}

template<typename T>
Node<T> *SkipList<T>::find(const T &item, Node<T> **update) {
    int currentLevel = maxLevel - 1; // start from top most level.
    Node<T> *cur, *prev{nullptr};
    while (currentLevel >= 0){
        cur = prev ? prev->next[currentLevel] : heads[currentLevel];
        /*
        if cur becomes null, there are 2 cases:
            1- if prev is null, that means that level has no nodes (empty level)
                => cur should start from the beginning of the next level
            2- if prev is not null, which means cur is either at the end of that level or has a data greater than or equal to item. therefore, the item should be on the right side of the prev node.
                => cur should start from the prev node (scan the bottom level from that element forward)
        cur starts to point at heads[currentLevel], since prev is null at the beginning;
        */
        while(cur && item > cur->data){ // move cur to the smallest element, larger than or equal to item or null(end of that level)
            prev = cur;
            cur = cur->next[currentLevel];
        }
        // we either reached the end of a level, or a node whose data is larger than or equal to item
        if(update) update[currentLevel] = prev;
        --currentLevel; // go to the bottom level.
    }
    // cur now points to the item or the smallest element larger than the item.
    return cur;
}

/**
 * inserts item into the SkipList, if it does not already exist.
 * @param item to be inserted
 */
template<typename T>
void SkipList<T>::insert(const T &item) {
    Node<T> **update = new Node<T> *[maxLevel]; // array for updating links between node after insertion
    for(int i = 0; i < maxLevel; i++) update[i] = nullptr;

    Node<T> *cur = find(item, update); // cur now points to the item or the smallest element larger than the item.
    if(cur && cur->data == item) return; // don't add duplicates

    int itemLevel = randomLevel(); // determine to which level the new node should be promoted
    Node<T> *newNode = new Node<T>(item, itemLevel);

    for(int currentLevel = 0; currentLevel <= itemLevel; currentLevel++){ //update the links of new node and the SkipList
        newNode->next[currentLevel] = update[currentLevel] ? update[currentLevel]->next[currentLevel] : heads[currentLevel];
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = newNode : heads[currentLevel] = newNode;
        /*
        newNode next at each level should point to:
            1- if update[currentLevel] is null, that means the newNode is becoming the first node in a level.
                => A - newNode->next[currentLevel] should become heads[currentLevel] (which is either null(level was empty), or address of the previous first node in that level)
                   B - heads[currentLevel] should now point to the new Node
            2- if update[currentLevel] is not null
            Attention: update[currentLevel]->item, is the largest data, smaller than the item. the new node is inserted after that node.
                => A - newNode->next should point to the next node of update[currentLevel].
                   B - update[currentLevel]->next[currentLevel] should become the newNode
         */
    }
    size++;
    delete[] update;
}

template<typename T>
void SkipList<T>::insertVerbose(const T &item) {
    Node<T> **update = new Node<T> *[maxLevel]; // array for updating links between node after insertion
    for(int i = 0; i < maxLevel; i++) update[i] = nullptr;
    std::cout << "1- Finding the place for " << item <<"..." << std::endl;
    Node<T> *cur = find(item, update); // cur now points to the item or the smallest element larger than the item.
    if(cur && cur->data == item) std::cout <<"Item already exist! Exiting method..." << std::endl;
    if(cur && cur->data == item) return; // don't add duplicates
    for(int i = 0; i < maxLevel; i++) {
        std::cout << "At Level " << std::setw(2) << i << " item should go between "
        << (!update[i] ? (heads[i] && heads[i]->data < item ? std::to_string(heads[i]->data) : "*") : std::to_string(update[i]->data)) <<
        " and " << (update[i] && update[i]->next[i] ? std::to_string(update[i]->next[i]->data): (heads[i] && heads[i]->data > item ? std::to_string(heads[i]->data) : "*"))
        << std::endl;
        if(!heads[i]) {
            break;
        }
    }

    int itemLevel = randomLevel(); // determine to which level the new node should be promoted
    std::cout << "2- Creating Node, Node will be promoted to level " << itemLevel << std::endl;
    Node<T> *newNode = new Node<T>(item, itemLevel);
    std::cout << "3- Rewiring..." << std::endl;
    for(int i = 0; i <= itemLevel; i++){
        std::cout << "At Level " << std::setw(2) << i << ": " << (!update[i] ? (heads[i] && heads[i]->data < item? std::to_string(heads[i]->data) : "*") : std::to_string(update[i]->data)) << " -> " << newNode->data << " -> " << (update[i] && update[i]->next[i] ? std::to_string(update[i]->next[i]->data): (heads[i] && heads[i]->data > item ? std::to_string(heads[i]->data) : "*")) << std::endl;
    }
    for(int currentLevel = 0; currentLevel <= itemLevel; currentLevel++){ //update the links of new node and the SkipList
        newNode->next[currentLevel] = update[currentLevel] ? update[currentLevel]->next[currentLevel] : heads[currentLevel];
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = newNode : heads[currentLevel] = newNode;
        /*
        newNode next at each level should point to:
            1- if update[currentLevel] is null, that means the newNode is becoming the first node in a level.
                => A - newNode->next[currentLevel] should become heads[currentLevel] (which is either null(level was empty), or address of the previous first node in that level)
                   B - heads[currentLevel] should now point to the new Node
            2- if update[currentLevel] is not null
            Attention: update[currentLevel]->item, is the largest data, smaller than the item. the new node is inserted after that node.
                => A - newNode->next should point to the next node of update[currentLevel].
                   B - update[currentLevel]->next[currentLevel] should become the newNode
         */
    }
    std::cout << "#### >>> Insert Completed <<< ####" << std::endl;
    size++;
    delete[] update;
}
/**
 * This methods performs something similar to binary search on the SkipList. It runs in average-case: O(Log(n)), worst-case O(n)
 * @param item to search for
 * @return a pointer to the item, or nullptr if not found
 */
template<typename T>
const Node<T>* SkipList<T>::binarySearch(const T &item) {
    Node<T> *cur = find(item);
    // cur now points to the item or the largest element smaller than the item.
    if(cur && cur->data == item) return cur;
    else return nullptr;
}
template<typename T>
const Node<T>* SkipList<T>::binarySearchVerbose(const T &item) {
    int comp{0};
    std::cout << "Searching for " << item << " using Fast Search (similar to Binary Search)..." << std::endl;
    int currentLevel = maxLevel - 1; // start from top most level.
    Node<T> *cur, *prev{nullptr};
    std::cout << "Comparisons: " << std::endl;
    while (currentLevel >= 0){
        cur = prev ? prev->next[currentLevel] : heads[currentLevel];
        while(cur && (comp++ >= 0) && item > cur->data){ // move cur to the smallest element, larger than or equal to item or null(end of that level)
            std::cout << "Level " << std::setw(2) << currentLevel << ": " << item << " > " << cur->data << " ? TRUE => Go to next node" << std::endl;
            prev = cur;
            cur = cur->next[currentLevel];
        }
        if(cur) std::cout << "Level " << std::setw(2) << currentLevel << ": " << item << " > " << cur->data << " ? FALSE - " ;
        if(heads[currentLevel] && !cur) std::cout << "Reached end of level - ";
        if(heads[currentLevel]) std::cout << "Go one level down" << std::endl;
        //if(cur) std::cout << item << " = " << cur->data << " ?" << std::endl;
        //if(cur && (comp++>=0) &&cur->data == item) break;
        /*
         Based on the current implementation:
         If we uncomment the above lines, we will get a better time, finding the elements at the higher levels,
         Since it will terminate the loop early for those elements. (As fast as just 2 comparisons (if it's the first element in the top most level)).
         However, it will give us a worse average time, for finding elements located at the levels bellow (level 0, 1 and 2), because it does 1 extra comparison on each hop

         Since the probability of that item searched for being in bottom levels is far higher than being on the upper levels,
         It is reasonable to optimize the algorithm to find the elements on the bottom level in less comparisons.
         with this implementation, finding elements at the top most level takes almost the same time as finding the one in the bottom level.(around the average)

         in the case where an element does not exist in the list, you can witness the difference in average time clearly.
         */

//        if(cur && item == cur->data) return cur;
        // we either reached the end of a level, or a node whose data is larger than or equal to item
        --currentLevel; // go to the bottom level.
    }
    std::cout << "--- End of searching ---" << std::endl;
    std::cout << "Stats for binarySearch" << std::endl;
    std::cout << "Comparisons # " << comp << "\nFound ? " << std::boolalpha << (cur && cur->data == item) <<std::endl;
    if(cur && cur->data == item) return cur;
    else return nullptr;
    // cur now points to the item or the smallest element larger than the item.
}
template<typename T>
const Node<T>* SkipList<T>::linearSearch(const T &item) {
    Node<T> *cur{heads[0]};
    while(cur && item > cur->data){
        cur = cur->next[0];
    }
    // cur now points to the item or the largest element smaller than the item.
    if(cur && cur->data == item) return cur;
    else return nullptr;
}
template<typename T>
const Node<T>* SkipList<T>::linearSearchVerbose(const T &item) {
    int comp{0};
    std::cout << "Searching for " << item << " using Linear Search..." << std::endl;
    Node<T> *cur{heads[0]};
    while(cur && (comp++ >= 0) && item > cur->data){
        cur = cur->next[0];
    }
    std::cout << "Stats for linearSearch" << std::endl;
    std::cout << "Comparisons # " << comp << "\nFound ? " << std::boolalpha << (cur && cur->data == item) <<std::endl;

    // cur now points to the item or the largest element smaller than the item.
    if(cur && cur->data == item) return cur;
    else return nullptr;
}

/**
 * Removes item from the SkipList, if doesn't exist, will throw runtime_error
 * @param item to be removed
 * @return data that was inside that item.
 */
template<typename T>
T SkipList<T>::remove(const T &item) {
    Node<T> **update = new Node<T> *[maxLevel]; // array for updating links between node after insertion
    for(int i = 0; i < maxLevel; i++) update[i] = nullptr;
    Node<T> *cur = find(item, update);
    // cur now points to the item or the largest element smaller than the item.
    if(!cur || cur->data != item) {
        throw std::runtime_error("Item doesn't exist!");
    }; // don't need to delete anything
    for(int currentLevel = 0; currentLevel <= cur->level; currentLevel++){
        /*
        if update[currentLevel] is null, that means the cur is the first node in that level.
                => heads[currentLevel] should point to the next node of the cur (heads[currentLevel] = cur->next[currentLevel])
        if update[currentLevel] is NOT null, then it is the node before the element to be deleted.
                => it's next should point to the cur->next at that same level
         */
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = cur->next[currentLevel] : heads[currentLevel] = cur->next[currentLevel];
    }
    size--;
    T x = cur->data;
    delete cur;
    delete[] update;
    return x;
}

template<typename T>
T SkipList<T>::removeVerbose(const T &item) {
    Node<T> **update = new Node<T> *[maxLevel]; // array for updating links between node after insertion
    for(int i = 0; i < maxLevel; i++) update[i] = nullptr;
    std::cout << "Deleting " << item <<" From the list..." << std::endl;
    std::cout << "1- Finding " << item <<"..." << std::endl;
    Node<T> *cur = find(item, update);
    // cur now points to the item or the largest element smaller than the item.
    if(!cur || cur->data != item) {
        throw std::runtime_error("Item doesn't exist!");
    }; // don't need to delete anything
    for(int i = 0; i <= cur->level; i++) {
        std::cout << "At Level " << std::setw(2) << i << ": " << (!update[i] ? (heads[i] && heads[i]->data != item? std::to_string(heads[i]->data) : "*") : std::to_string(update[i]->data)) << " -> " << cur->data << " -> " << (cur->next[i]? std::to_string(cur->next[i]->data): "*") << std::endl;
    }


    std::cout << "2- Rewiring..." << std::endl;
    for(int i = 0; i <= cur->level; i++){
        std::cout << "At Level " << std::setw(2) << i << ": " << (!update[i] ? (heads[i] && heads[i]->data != item? std::to_string(heads[i]->data) : "*") : std::to_string(update[i]->data)) << " -> " << (cur->next[i]? std::to_string(cur->next[i]->data): "*") << std::endl;
    }
    for(int currentLevel = 0; currentLevel <= cur->level; currentLevel++){
        /*
        if update[currentLevel] is null, that means the cur is the first node in that level.
                => heads[currentLevel] should point to the next node of the cur (heads[currentLevel] = cur->next[currentLevel])
        if update[currentLevel] is NOT null, then it is the node before the element to be deleted.
                => it's next should point to the cur->next at that same level
         */
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = cur->next[currentLevel] : heads[currentLevel] = cur->next[currentLevel];
    }

    std::cout << "3- Removing the node..." << std::endl;

    std::cout << "#### >>> Remove Completed <<< ####" << std::endl;
    size--;
    T x = cur->data;
    delete cur;
    delete[] update;
    return x;
}

/**
 * Display elements in level 0
 */
template<typename T>
void SkipList<T>::displayHeadToTail() {
    Node<T>* temp = heads[0];
    while(temp){
        std::cout << temp->data << " ";
        temp = temp->next[0];
    }
    std::cout << std::endl;
}
/**
 * Display elements level by level
 */
template<typename T>
void SkipList<T>::displayLevelByLevel() {
    T *arr = new T[size];
    Node<T>* temp;
    int i;
    for(int curLevel = 0; curLevel < maxLevel && heads[curLevel]; curLevel++){
        i = 0;
        std::cout << "Level " << std::setw(2) << curLevel <<": * -> ";
        temp = heads[curLevel];
        while(temp){
            if(curLevel == 0){
                arr[i++] = temp->data;
            } else {
                while(arr[i] != temp->data){
                    std::cout << std::setw(4) << "" << " ";
                    i++;
                }
            }
            std::cout << std::setw(4) << temp->data << " ";
            temp = temp->next[curLevel];
            if(curLevel != 0) i++;
        }
        while(i < size){
            std::cout << std::setw(4) << "" << " ";
            i++;
        }
        std::cout <<" -> * " << std::endl;
    }

}



template<typename T>
void SkipList<T>::setMaxLevel(int l) {
    SkipList<T>::maxLevel = l;
}
template<typename T>
int SkipList<T>::getSize() {
    return size;
}

#endif //SKIPLIST_SKIPLIST_H


