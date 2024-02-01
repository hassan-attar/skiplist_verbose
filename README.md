# SkipList Implementation

## Overview

This repository contains a C++ implementation of a SkipList data structure. SkipList is a data structure that allows for efficient search, insertion, and removal of elements, providing logarithmic time complexity for these operations on average.
mized Level Generation:** The SkipList utilizes a randomized process to determine the level of each node, providing a balanced structure.

## Usage

- **To use the SkipList in your project, you can include the `SkipList.h` header file and instantiate a `SkipList` object with the desired type.
- **You can run the command-line based application, to interact with the SkipList, you can perform operations and activate the verbose mode. (recommended for educational purposes) 

## How to Compile the program:
```bash
g++ -std=c++17 Node.cpp RandomCoinFlip.cpp SkipList.cpp main.cpp -o prog && ./prog
```
## How to use the SkipList in your applications:
```cpp
#include "SkipList.h"

int main() {
    SkipList<int> skipList;
    
    // Example: Inserting elements
    skipList.insert(42);
    skipList.insert(18);
    
    // Example: Searching for an element
    const Node<int>* result = skipList.binarySearch(18);
    if (result) {
        std::cout << "Element found: " << result->data << std::endl;
    } else {
        std::cout << "Element not found." << std::endl;
    }

    // ... Other operations

    return 0;
}
```

