#include <iostream>
#include "SkipList.cpp"
#include <vector>
#include <algorithm>
#include <random>




void displayMainMenu(){
    std::cout << std::setfill('#') << std::setw(60) << "#" << std::setfill(' ') << std::endl;
    std::cout << std::setw(100) << std::left <<"Main Menu" << std::endl;;
    std::cout << std::setw(100) << std::left <<"1 - Create a SkipList from Scratch" << std::endl;
    std::cout << std::setw(100) << std::left <<"2 - Create a SkipList with size N" << std::endl;
    std::cout << std::setw(100) << std::left <<"3 - Exit" << std::endl;
}

void displayMenuSkipList(bool verbose){
    std::cout << std::setfill('#') << std::setw(60) << "#" << std::setfill(' ') << std::endl;
    std::cout << std::left <<"SkipList" << std::endl;
    std::cout << std::left <<"1 - Switch Verbose (Status: " << (verbose ? "ON" : "OFF") << ")" << std::endl;
    std::cout << std::left <<"2 - Add Element" << std::endl;
    std::cout << std::left <<"3 - Remove Element" << std::endl;
    std::cout << std::left <<"4 - Search Element (Linear)" << std::endl;
    std::cout << std::left <<"5 - Search Element (Binary)" << std::endl;
    std::cout << std::left <<"6 - Display Elements Head To Tail (Level 0)" << std::endl;
    std::cout << std::left <<"7 - Display Elements Level by Level" << std::endl;
    std::cout << std::left <<"8 - Back to Main Menu (Deleting the created SkipList)" << std::endl;
}

int getChoice(int maxAllowedChoice){
    int c{0};
    do {
        std::cout << "Enter your choice number: ";
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
    for(int i = 0; i < size; i++){
        if(i == size/2){
            randomValues[i]= 0;
            std::cout << "Element not in the list is: "<< (size/2 + 1) << std::endl;
            continue;
        }
        randomValues[i]= i + 1; // items to be inserted range from 1 to size (both inclusive)
    }
    int numLevel{20};
    std::cout << "Enter Number of levels for SkipList (Default is 20 (recommended)): (MAX is 100)" << std::endl;
    numLevel = getChoice(100);
    SkipList<int>::setMaxLevel(numLevel);
    SkipList<int> *s = new SkipList<int>();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(randomValues.begin(), randomValues.end(), g); // put input data in random order
    for(const int &x: randomValues){
        s->insert(x); // insert them into SkipList
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

void addElement(SkipList<int> *s, bool verbose){
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
        if(verbose){
            s->displayLevelByLevel();
            s->insertVerbose(e);
            s->displayLevelByLevel();
        }else{
            s->insert(e);
        }
        break;
    }
}

bool switchVerbose(){
    int c{0};
    std::cout << "Do you want to turn verbose mode on? 1-Yes 2-No" << std::endl;
    c = getChoice(2);
    return c==1;
}

void removeElement(SkipList<int> *s, bool verbose){
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
            if(verbose){
                s->displayLevelByLevel();
                s->removeVerbose(e);
                s->displayLevelByLevel();
            }else{
                s->remove(e);
            }
        } catch (const std::runtime_error &e){
            std::cout << e.what() << std::endl;
        }
        break;
    }
}

void searchElement(SkipList<int> *s, bool verbose, bool isBinary){
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
        if(verbose){
            if(isBinary){
                s->displayLevelByLevel();
                s->binarySearchVerbose(e);
            } else {
                s->linearSearchVerbose(e);
            }
        }else{
            if(isBinary){
                std::cout << "Found ? " << std::boolalpha <<  (s->binarySearch(e) != nullptr) << std::endl;
            } else {
                std::cout << "Found ? " << std::boolalpha <<  (s->linearSearch(e) != nullptr) << std::endl;
            }
        }
        break;
    }
}

void workWithSkipList(SkipList<int> *s){
    int c{0};
    bool verbose{true};
    while(true){
        displayMenuSkipList(verbose);
        c = getChoice(8);
        switch (c) {
            case 1:
                verbose = switchVerbose();
                break;
            case 2:
                addElement(s, verbose);
                break;
            case 3:
                removeElement(s, verbose);
                break;
            case 4:
                searchElement(s, verbose, false);
                break;
            case 5:
                searchElement(s, verbose, true);
                break;
            case 6:
                s->displayHeadToTail();
                break;
            case 7:
                s->displayLevelByLevel();
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

