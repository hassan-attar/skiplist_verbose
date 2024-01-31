//
// Created by Hassan Attar on 2024-01-25.
//

#ifndef SKIPLIST_RANDOMCOINFLIP_H
#define SKIPLIST_RANDOMCOINFLIP_H
#include <random>

class RandomCoinFlip {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib;
public:
    // Constructor to initialize the random number generator and distribution
    RandomCoinFlip();
    // Function to return either 0 or 1 randomly
    int flipCoin();
};


#endif //SKIPLIST_RANDOMCOINFLIP_H
