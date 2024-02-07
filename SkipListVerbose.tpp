//
// Created by Hassan Attar on 2024-01-25.
//


#include "SkipListVerbose.h"
#include <iostream>
#include <iomanip>
template<typename T>
SkipListVerbose<T>::SkipListVerbose(): SkipList<T>() {}

template<typename T>
SkipListVerbose<T>::SkipListVerbose(const SkipListVerbose<T> &rhs) : SkipList<T>(rhs) {}

template<typename T>
SkipListVerbose<T>::SkipListVerbose(size_t maxLevel): SkipList<T>(maxLevel) {}

template<typename T>
SkipListVerbose<T>::SkipListVerbose(const std::initializer_list<T> &list): SkipList<T>(list) {}

template<typename T>
SkipListVerbose<T>::SkipListVerbose(SkipListVerbose<T> &&rhs) noexcept : SkipList<T>(std::move(rhs)) {}

template<typename T>
SkipListVerbose<T> &SkipListVerbose<T>::operator=(const SkipListVerbose<T> &rhs) {
    SkipList<T>::operator=(rhs);
}

template<typename T>
SkipListVerbose<T> &SkipListVerbose<T>::operator=(SkipListVerbose<T> &&rhs) noexcept {
    SkipList<T>::operator=(std::move(rhs));
}

template<typename T>
void SkipListVerbose<T>::insertVerbose(const T &item) {
    Node<T> **update = new Node<T> *[SkipList<T>::maxLevel]; // array for updating links between node after insertion
    for(int i = 0; i < SkipList<T>::maxLevel; i++) update[i] = nullptr;
    std::cout << "1- Finding the place for " << item <<"..." << std::endl;
    Node<T> *cur = SkipList<T>::findItem(item, update); // cur now points to the item or the smallest element larger than the item.
    if(cur && cur->data == item) std::cout <<"Item already exist! Exiting method..." << std::endl;
    if(cur && cur->data == item) return; // don't add duplicates
    for(int i = 0; i < SkipList<T>::maxLevel; i++) {
        std::cout << "At Level " << std::setw(2) << i << " item should go between "
        << (!update[i] ? (SkipList<T>::heads[i] && SkipList<T>::heads[i]->data < item ? std::to_string(SkipList<T>::heads[i]->data) : "*") : std::to_string(update[i]->data)) <<
        " and " << (update[i] && update[i]->next[i] ? std::to_string(update[i]->next[i]->data): (SkipList<T>::heads[i] && SkipList<T>::heads[i]->data > item ? std::to_string(SkipList<T>::heads[i]->data) : "*"))
        << std::endl;
        if(!SkipList<T>::heads[i]) {
            break;
        }
    }

    int itemLevel = SkipList<T>::randomLevel(); // determine to which level the new node should be promoted
    std::cout << "2- Creating Node, Node will be promoted to level " << itemLevel << std::endl;
    Node<T> *newNode = new Node<T>(item, itemLevel);
    std::cout << "3- Rewiring..." << std::endl;
    for(int i = 0; i <= itemLevel; i++){
        std::cout << "At Level " << std::setw(2) << i << ": " << (!update[i] ? (SkipList<T>::heads[i] && SkipList<T>::heads[i]->data < item? std::to_string(SkipList<T>::heads[i]->data) : "*") : std::to_string(update[i]->data)) << " -> " << newNode->data << " -> " << (update[i] && update[i]->next[i] ? std::to_string(update[i]->next[i]->data): (SkipList<T>::heads[i] && SkipList<T>::heads[i]->data > item ? std::to_string(SkipList<T>::heads[i]->data) : "*")) << std::endl;
    }
    for(int currentLevel = 0; currentLevel <= itemLevel; currentLevel++){ //update the links of new node and the SkipList
        newNode->next[currentLevel] = update[currentLevel] ? update[currentLevel]->next[currentLevel] : SkipList<T>::heads[currentLevel];
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = newNode : SkipList<T>::heads[currentLevel] = newNode;
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
    SkipList<T>::size++;
    delete[] update;
}
/**
 * This methods performs something similar to binary search on the SkipList. It runs in average-case: O(Log(n)), worst-case O(n)
 * @param item to search for
 * @return a pointer to the item, or nullptr if not found
 */
template<typename T>
typename SkipList<T>::iterator SkipListVerbose<T>::findVerbose(const T &item) {
    int comp{0};
    std::cout << "Searching for " << item << " using Fast Search (similar to Binary Search)..." << std::endl;
    int currentLevel = SkipList<T>::maxLevel - 1; // start from top most level.
    Node<T> *cur, *prev{nullptr};
    std::cout << "Comparisons: " << std::endl;
    while (currentLevel >= 0){
        cur = prev ? prev->next[currentLevel] : SkipList<T>::heads[currentLevel];
        while(cur && (comp++ >= 0) && item > cur->data){ // move cur to the smallest element, larger than or equal to item or null(end of that level)
            std::cout << "Level " << std::setw(2) << currentLevel << ": " << item << " > " << cur->data << " ? TRUE => Go to next node" << std::endl;
            prev = cur;
            cur = cur->next[currentLevel];
        }
        if(cur) std::cout << "Level " << std::setw(2) << currentLevel << ": " << item << " > " << cur->data << " ? FALSE - " ;
        if(SkipList<T>::heads[currentLevel] && !cur) std::cout << "Reached end of level - ";
        if(SkipList<T>::heads[currentLevel]) std::cout << "Go one level down" << std::endl;
        //if(cur) std::cout << item << " = " << cur->data << " ?" << std::endl;
        //if(cur && (comp++>=0) &&cur->data == item) break;
        /*
         Based on the current implementation:
         If we uncomment the above lines, we will get a better time, finding the elements at the higher levels,
         Since it will terminate the loop early for those elements. (As fast as just 2 comparisons (if it's the first element in the top most level)).
         However, it will give us a worse average time for finding elements located at the levels bellow (level 0, 1 and 2), because it does 1 extra comparison on each hop

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
typename SkipList<T>::iterator SkipListVerbose<T>::linearSearchVerbose(const T &item) {
    int comp{0};
    std::cout << "Searching for " << item << " using Linear Search..." << std::endl;
    Node<T> *cur{SkipList<T>::heads[0]};
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
bool SkipListVerbose<T>::removeVerbose(const T &item) {
    Node<T> **update = new Node<T> *[SkipList<T>::maxLevel]; // array for updating links between node after insertion
    for(int i = 0; i < SkipList<T>::maxLevel; i++) update[i] = nullptr;
    std::cout << "Deleting " << item <<" From the list..." << std::endl;
    std::cout << "1- Finding " << item <<"..." << std::endl;
    Node<T> *cur = SkipList<T>::findItem(item, update);
    // cur now points to the item or the largest element smaller than the item.
    if(!cur || cur->data != item) {
        throw std::runtime_error("Item doesn't exist!");
    }; // don't need to delete anything
    for(int i = 0; i <= cur->level; i++) {
        std::cout << "At Level " << std::setw(2) << i << ": " << (!update[i] ? (SkipList<T>::heads[i] && SkipList<T>::heads[i]->data != item? std::to_string(SkipList<T>::heads[i]->data) : "*") : std::to_string(update[i]->data)) << " -> " << cur->data << " -> " << (cur->next[i]? std::to_string(cur->next[i]->data): "*") << std::endl;
    }


    std::cout << "2- Rewiring..." << std::endl;
    for(int i = 0; i <= cur->level; i++){
        std::cout << "At Level " << std::setw(2) << i << ": " << (!update[i] ? (SkipList<T>::heads[i] && SkipList<T>::heads[i]->data != item? std::to_string(SkipList<T>::heads[i]->data) : "*") : std::to_string(update[i]->data)) << " -> " << (cur->next[i]? std::to_string(cur->next[i]->data): "*") << std::endl;
    }
    for(int currentLevel = 0; currentLevel <= cur->level; currentLevel++){
        /*
        if update[currentLevel] is null, that means the cur is the first node in that level.
                => heads[currentLevel] should point to the next node of the cur (heads[currentLevel] = cur->next[currentLevel])
        if update[currentLevel] is NOT null, then it is the node before the element to be deleted.
                => it's next should point to the cur->next at that same level
         */
        update[currentLevel] ? update[currentLevel]->next[currentLevel] = cur->next[currentLevel] : SkipList<T>::heads[currentLevel] = cur->next[currentLevel];
    }

    std::cout << "3- Removing the node..." << std::endl;

    std::cout << "#### >>> Remove Completed <<< ####" << std::endl;
    SkipList<T>::size--;
    T x = cur->data;
    delete cur;
    delete[] update;
    return x;
}




