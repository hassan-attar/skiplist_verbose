# SkipList (Probabilistic Data Structure)

Sample Run of size 25:
<pre>
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25    -> * 
Level 1 : * ->      1                   5         7    8         10   11                  15        17   18   19   20        22        24   25    -> * 
Level 2 : * ->      1                   5                        10                       15             18                            24   25    -> * 
Level 3 : * ->      1                   5                                                                18                                       -> * 
Level 4 : * ->                                                                                           18                                       -> * 
</pre>
## Overview

This repository contains a C++ implementation of a SkipList data structure. SkipList is a data structure that allows for efficient search, insertion, and removal of elements, providing logarithmic time complexity for these operations on average. The SkipList utilizes a randomized process (coin flip) to determine the level of each node.

## Usage

- **To use the SkipList in your project, you can include the `SkipList.h` header file and instantiate a `SkipList` object with the desired type.**
- **You can run the command-line-based application, to interact with the SkipList, you can perform operations and activate the verbose mode. (recommended for educational purposes)**

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
    skipList.insert(20);
    skipList.insert(10);
    
    // Example: Searching for an element
    const Node<int>* result = skipList.binarySearch(18);
    if (result) {
        std::cout << "Element found: " << result->data << std::endl;
    } else {
        std::cout << "Element not found." << std::endl;
    }
    return 0;
}
```
## Features
### Operations:
- **InsertVerbose(const T &item)**
Inserts an item into the SkipList, if it does not already exist.
<pre>
Enter value to Insert (int): 13
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   14   15   16   17   18   19   20   21   22   23   24   25    -> * 
Level 1 : * -> 0    1              4    5         7    8                   12   14             17                                            -> * 
Level 2 : * ->                                    7                                            17                                            -> * 
1- Finding the place for 13...
At Level 0  item should go between 12 and 14
At Level 1  item should go between 12 and 14
At Level 2  item should go between 7 and 17
At Level 3  item should go between * and *
2- Creating Node, Node will be promoted to level 2
3- Rewiring...
At Level 0 : 12 -> 13 -> 14
At Level 1 : 12 -> 13 -> 14
At Level 2 :  7 -> 13 -> 17
At Level 3 :  * -> 13 -> *
#### >>> Insert Completed <<< ####
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25    -> * 
Level 1 : * -> 0    1              4    5         7    8                   12   13   14             17                                            -> * 
Level 2 : * ->                                    7                             13                  17                                            -> *
Level 3 : * ->                                                                  13                                                                -> *
</pre>

- **binarySearchVerbose(const T &item)**
<pre>
Enter value to Search (int): 19
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30    -> * 
Level 1 : * -> 0    1         3              6    7         9              12   13        15        17   18                  22        24                       29   30    -> * 
Level 2 : * ->      1                        6                             12             15                                 22                                 29         -> * 
Level 3 : * ->      1                                                      12             15                                 22                                            -> * 
Level 4 : * ->                                                                            15                                 22                                            -> * 
Searching for 19 using Fast Search (similar to Binary Search)...
Comparisons: 
Level 4 : 19 > 15 ? TRUE => Go to next node
Level 4 : 19 > 22 ? FALSE - Go one level down
Level 3 : 19 > 22 ? FALSE - Go one level down
Level 2 : 19 > 22 ? FALSE - Go one level down
Level 1 : 19 > 17 ? TRUE => Go to next node
Level 1 : 19 > 18 ? TRUE => Go to next node
Level 1 : 19 > 22 ? FALSE - Go one level down
Level 0 : 19 > 19 ? FALSE - Go one level down
--- End of searching ---
Stats for binarySearch
Comparisons # 8
Found ? true
</pre>

- **linearSearchVerbose(const T &item)**
<pre>
Enter value to Search (int): 24
Searching for 24 using Linear Search...
Stats for linearSearch
Comparisons # 24
Found ? true
</pre>

- **removeVerbose(const T &item)**
<pre>
Enter value to Remove (int): 17
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   14   15   16   17   18   19   20   21   22   23   24   25    -> * 
Level 1 : * ->      1    2    3    4    5    6    7         9                        15        17   18        20                       25    -> * 
Level 2 : * ->      1         3    4                                                 15        17   18        20                             -> * 
Level 3 : * ->                                                                                 17   18        20                             -> * 
Level 4 : * ->                                                                                 17                                            -> * 
Deleting 17 From the list...
1- Finding 17...
At Level 0 : 16 -> 17 -> 18
At Level 1 : 15 -> 17 -> 18
At Level 2 : 15 -> 17 -> 18
At Level 3 : * -> 17 -> 18
At Level 4 : * -> 17 -> *
2- Rewiring...
At Level 0 : 16 -> 18
At Level 1 : 15 -> 18
At Level 2 : 15 -> 18
At Level 3 : * -> 18
At Level 4 : * -> *
3- Removing the node...
#### >>> Remove Completed <<< ####
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   14   15   16   18   19   20   21   22   23   24   25    -> * 
Level 1 : * ->      1    2    3    4    5    6    7         9                        15        18        20                       25    -> * 
Level 2 : * ->      1         3    4                                                 15        18        20                             -> * 
Level 3 : * ->                                                                                 18        20                             -> * 

</pre>

### Searching in Large dataset (Size 10,000,000):
<pre>
Enter value to Search (int): 5932041
Searching for 5932041 using Fast Search (similar to Binary Search)...
Comparisons: 
Level 22: 5932041 > 273486 ? TRUE => Go to next node
Level 22: 5932041 > 1057797 ? TRUE => Go to next node
Reached end of level - Go one level down
Level 21: 5932041 > 4937902 ? TRUE => Go to next node
Level 21: 5932041 > 5747947 ? TRUE => Go to next node
Level 21: 5932041 > 8673141 ? FALSE - Go one level down
Level 20: 5932041 > 8673141 ? FALSE - Go one level down
Level 19: 5932041 > 6389008 ? FALSE - Go one level down
Level 18: 5932041 > 6383491 ? FALSE - Go one level down
Level 17: 5932041 > 5881698 ? TRUE => Go to next node
Level 17: 5932041 > 6383491 ? FALSE - Go one level down
Level 16: 5932041 > 6157260 ? FALSE - Go one level down
Level 15: 5932041 > 6005646 ? FALSE - Go one level down
Level 14: 5932041 > 5882211 ? TRUE => Go to next node
Level 14: 5932041 > 5888368 ? TRUE => Go to next node
Level 14: 5932041 > 5923170 ? TRUE => Go to next node
Level 14: 5932041 > 5954223 ? FALSE - Go one level down
Level 13: 5932041 > 5954223 ? FALSE - Go one level down
Level 12: 5932041 > 5929705 ? TRUE => Go to next node
Level 12: 5932041 > 5930920 ? TRUE => Go to next node
Level 12: 5932041 > 5943616 ? FALSE - Go one level down
Level 11: 5932041 > 5931541 ? TRUE => Go to next node
Level 11: 5932041 > 5932095 ? FALSE - Go one level down
Level 10: 5932041 > 5932095 ? FALSE - Go one level down
Level 9 : 5932041 > 5932095 ? FALSE - Go one level down
Level 8 : 5932041 > 5932095 ? FALSE - Go one level down
Level 7 : 5932041 > 5931703 ? TRUE => Go to next node
Level 7 : 5932041 > 5931752 ? TRUE => Go to next node
Level 7 : 5932041 > 5932095 ? FALSE - Go one level down
Level 6 : 5932041 > 5931866 ? TRUE => Go to next node
Level 6 : 5932041 > 5931898 ? TRUE => Go to next node
Level 6 : 5932041 > 5932093 ? FALSE - Go one level down
Level 5 : 5932041 > 5932056 ? FALSE - Go one level down
Level 4 : 5932041 > 5931950 ? TRUE => Go to next node
Level 4 : 5932041 > 5931952 ? TRUE => Go to next node
Level 4 : 5932041 > 5931960 ? TRUE => Go to next node
Level 4 : 5932041 > 5932024 ? TRUE => Go to next node
Level 4 : 5932041 > 5932056 ? FALSE - Go one level down
Level 3 : 5932041 > 5932032 ? TRUE => Go to next node
Level 3 : 5932041 > 5932037 ? TRUE => Go to next node
Level 3 : 5932041 > 5932038 ? TRUE => Go to next node
Level 3 : 5932041 > 5932050 ? FALSE - Go one level down
Level 2 : 5932041 > 5932043 ? FALSE - Go one level down
Level 1 : 5932041 > 5932043 ? FALSE - Go one level down
Level 0 : 5932041 > 5932039 ? TRUE => Go to next node
Level 0 : 5932041 > 5932040 ? TRUE => Go to next node
Level 0 : 5932041 > 5932041 ? FALSE - Go one level down
--- End of searching ---
Stats for binarySearch
Comparisons # 46
Found ? true
</pre>
