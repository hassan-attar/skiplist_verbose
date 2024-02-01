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

This repository contains a C++ implementation of a SkipList data structure. SkipList is a data structure that allows for efficient search, insertion, and removal of elements, providing logarithmic time complexity for these operations on average.
mized Level Generation:** The SkipList utilizes a randomized process to determine the level of each node, providing a balanced structure.

## Usage

- **To use the SkipList in your project, you can include the `SkipList.h` header file and instantiate a `SkipList` object with the desired type.**
- **You can run the command-line based application, to interact with the SkipList, you can perform operations and activate the verbose mode. (recommended for educational purposes)**

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
Enter value to Search (int): 24
Level 0 : * -> 0    1    2    3    4    5    6    7    8    9    10   11   12   14   15   16   17   18   19   20   21   22   23   24   25    -> * 
Level 1 : * -> 0         2         4         6    7                   11        14                  18                       23   24         -> * 
Level 2 : * ->           2         4         6                                                      18                                       -> * 
Level 3 : * ->           2                   6                                                      18                                       -> * 
Level 4 : * ->           2                   6                                                      18                                       -> * 
Level 5 : * ->                               6                                                      18                                       -> * 
Level 6 : * ->                               6                                                                                               -> * 
Searching for 24 using Fast Search (similar to Binary Search)...
Comparisons: 
24 > 6 ?
24 > 18 ?
24 > 23 ?
24 > 24 ?
24 > 24 ?
Stats for binarySearch
Comparisons # 5
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

### Searching in Large dataset (Size 1000000):
<pre>
Searching for 713245 using Linear Search...
Stats for linearSearch
Comparisons # 713245
Found ? true
##################################################
Searching for 713245 using Fast Search (similar to Binary Search)...
Comparisons: 
713245 > 161906 ?
713245 > 675651 ?
713245 > 988126 ?
713245 > 988126 ?
713245 > 719788 ?
713245 > 685302 ?
713245 > 719788 ?
713245 > 719788 ?
713245 > 706027 ?
713245 > 717484 ?
713245 > 717484 ?
713245 > 713312 ?
713245 > 707935 ?
713245 > 708493 ?
713245 > 709812 ?
713245 > 711960 ?
713245 > 713312 ?
713245 > 712614 ?
713245 > 712760 ?
713245 > 712956 ?
713245 > 713312 ?
713245 > 713040 ?
713245 > 713312 ?
713245 > 713158 ?
713245 > 713312 ?
713245 > 713312 ?
713245 > 713164 ?
713245 > 713191 ?
713245 > 713263 ?
713245 > 713208 ?
713245 > 713263 ?
713245 > 713222 ?
713245 > 713262 ?
713245 > 713234 ?
713245 > 713245 ?
713245 > 713235 ?
713245 > 713237 ?
713245 > 713243 ?
713245 > 713245 ?
713245 > 713244 ?
713245 > 713245 ?
Stats for binarySearch
Comparisons # 41
Found ? true
</pre>
