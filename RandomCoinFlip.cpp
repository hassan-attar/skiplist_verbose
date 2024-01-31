//
// Created by Hassan Attar on 2024-01-25.
//

#include "RandomCoinFlip.h"
RandomCoinFlip::RandomCoinFlip() : gen(rd()), distrib(0, 1) {}

int RandomCoinFlip::flipCoin() {
    return distrib(gen);
}