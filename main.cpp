#include <iostream>
#include "SkipList.cpp"
#include <vector>
#include <algorithm>
#include <random>
#include <climits>



void displayMainMenu(){
    std::cout << std::setfill('#') << std::setw(60) << "#" << std::setfill(' ') << std::endl;
    std::cout << std::setw(100) << std::left <<"Main Menu" << std::endl;;
    std::cout << std::setw(100) << std::left <<"1 - Create a SkipList from Scratch" << std::endl;
    std::cout << std::setw(100) << std::left <<"2 - Create a SkipList with size N" << std::endl;
    std::cout << std::setw(100) << std::left <<"3 - Exit" << std::endl;
}

void displayMenuSkipList(bool visualAid){
    std::cout << std::setfill('#') << std::setw(60) << "#" << std::setfill(' ') << std::endl;
    std::cout << std::left <<"SkipList" << std::endl;
    std::cout << std::left <<"1 - Add Element" << std::endl;
    std::cout << std::left <<"2 - Remove Element" << std::endl;
    std::cout << std::left <<"3 - Search Element (Linear)" << std::endl;
    std::cout << std::left <<"4 - Search Element (Binary)" << std::endl;
    std::cout << std::left <<"5 - Display Elements Head To Tail (Level 0)" << std::endl;
    std::cout << std::left <<"6 - Display Elements Level by Level" << std::endl;
    std::cout << std::left <<"7 - Switch VisualAid mode (Status: " << (visualAid ? "ON" : "OFF") << ")" << std::endl;
    std::cout << std::left <<"8 - Back to Main Menu (Deleting the created SkipList)" << std::endl;
}

int getChoice(int maxAllowedChoice){
    int c{0};
    do {
        std::cout << "Enter your choice: ";
        std::cin >> c;
        if(std::cin.fail() ||  c <= 0 || c > maxAllowedChoice) {
            std::cout << "Invalid choice, try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(c <= 0 || c > maxAllowedChoice);
    return c;
}

SkipList<int>* createSkipList(){
    int size{0};
    std::cout << "Enter Size: " << std::endl;
    size = getChoice(INT_MAX);
    std::vector<int> randomValues(size);
    int i;
    for(i = 0; i < size; i++){
        if(i == size/2){
            randomValues[i]= 0;
            std::cout << ">>> Insert Test Opportunity for latter: Middle element not in the list is: "<< (size/2 + 1) << std::endl;
            continue;
        }
        randomValues[i]= i + 1; // items to be inserted range from 1 to size (both inclusive)
    }
    std::cout << "A vector<int> of size " << size << " has been created and filled with values 1 to " << size << "." << std::endl;
    int numLevel{20};
    std::cout << "Enter Number of levels for SkipList (Default is 20 (recommended)): (MAX is 100)" << std::endl;
    numLevel = getChoice(100);
    SkipList<int>::setMaxLevel(numLevel);
    SkipList<int> *s = new SkipList<int>();
    std::cout << "Shuffling numbers in the vector..." << std::endl;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(randomValues.begin(), randomValues.end(), g); // put input data in random order
    std::cout << ">>> vector<int> has been randomly shuffled, elements will be inserted in the SkipList in random order to make sure it can handle all the cases of insertion properly" << std::endl;
    i = 0;
    for(const int &x: randomValues){
        s->insert(x); // insert them into SkipList
        i++;
        if(i % (size/4) == 0){
            std::cout <<(i / (size/4))*25 <<  "% of elements inserted successfully." << std::endl;
        }
    }
    std::cout << "#### SkipList Created. ####"<< std::endl;
    return s;

}

SkipList<int>* createDefaultSkipList(){
    int numLevel{20};
    std::cout << "Enter Number of levels for SkipList (Default is 20 (recommended)): (MAX is 100)" << std::endl;
    numLevel = getChoice(100);
    SkipList<int>::setMaxLevel(numLevel);
    SkipList<int> *s = new SkipList<int>();
    std::cout << "#### SkipList Created. ####"<< std::endl;
    return s;
}

void addElement(SkipList<int> *s, bool visualAid){
    int e{0};
    while(true){
        std::cout << "Enter value to Insert (int): ";
        std::cin >> e;
        if(std::cin.fail()) {
            std::cout << "Invalid choice, try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(visualAid){
            s->displayLevelByLevel();
            s->insertVerbose(e);
            s->displayLevelByLevel();
        }else{
            s->insertVerbose(e);
        }
        break;
    }
}

bool switchVisualAid(){
    int c{0};
    std::cout << "VisualAid: this mode will prints level-by-level before and after insertion/deletion and before searching the elements" << std::endl;
    std::cout << "Do you want to turn VisualAid on? 1-Yes 2-No" << std::endl;
    c = getChoice(2);
    return c==1;
}

void removeElement(SkipList<int> *s, bool visualAid){
    int e{0};
    while(true){
        std::cout << "Enter value to Remove (int): ";
        std::cin >> e;
        if(std::cin.fail()) {
            std::cout << "Invalid choice, try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        try{
            if(visualAid){
                s->displayLevelByLevel();
                s->removeVerbose(e);
                s->displayLevelByLevel();
            }else{
                s->removeVerbose(e);
            }
        } catch (const std::runtime_error &e){
            std::cout << e.what() << std::endl;
        }
        break;
    }
}

void searchElement(SkipList<int> *s, bool visualAid, bool isBinary){
    int e{0};
    while(true){
        std::cout << "Enter value to Search (int): ";
        std::cin >> e;
        if(std::cin.fail()) {
            std::cout << "Invalid choice, try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(visualAid){
            if(isBinary){
                s->displayLevelByLevel();
                s->binarySearchVerbose(e);
            } else {
                s->displayHeadToTail();
                s->linearSearchVerbose(e);
            }
        }else{
            if(isBinary){
                s->binarySearchVerbose(e);
            } else {
                s->linearSearchVerbose(e);
            }
        }
        break;
    }
}

void workWithSkipList(SkipList<int> *s){
    int c{0};
    bool visualAid{false};
    while(true){
        displayMenuSkipList(visualAid);
        c = getChoice(8);
        switch (c) {
            case 1:
                addElement(s, visualAid);
                break;
            case 2:
                removeElement(s, visualAid);
                break;
            case 3:
                searchElement(s, visualAid, false);
                break;
            case 4:
                searchElement(s, visualAid, true);
                break;
            case 5:
                s->displayHeadToTail();
                break;
            case 6:
                s->displayLevelByLevel();
                break;
            case 7:
                visualAid = switchVisualAid();
                break;
            case 8:
                delete s;
                return;
            default:
                exit(1);
        }
    }
}

int mainMenu(){
    int c{0};
    SkipList<int> *s;
    while(true) {
        displayMainMenu();
        c = getChoice(3);
        switch (c) {
            case 1:
                s = createDefaultSkipList();
                workWithSkipList(s);
                break;
            case 2:
                s = createSkipList();
                workWithSkipList(s);
                break;
            case 3:
                exit(0);
            default:
                exit(1);
        }
    }
}





int main() {
    mainMenu();
    return 0;
}

