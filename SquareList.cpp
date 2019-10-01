///////////////////////////////////////////////////////////////
//  File:   SquareList.cpp
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   9/19/2019
//  Usage:  SquareList is the data structure that is being created
///////////////////////////////////////////////////////////////

#include "SquareList.h"

// Default Constructor
SquareList::SquareList() = default;

// Destructor
SquareList::~SquareList() {
    inners.clear();
}

// Makes sure the Square List is able to be quickly traversed
void SquareList::consolidate() {

    double shorter = sqrt(size() / 2);
    double longer = 2 * sqrt(size());


    // iterator for loop
    for (auto i = inners.begin(); i != inners.end(); i++) {

        auto k = i;
        k++;

        // Checks for empty inner list
        if (i->sizeOfThisInnerList() == 0) {
            i->clean();
            inners.erase(i++);

        // Skip the last iteration since I'm using the next value
        } else if (i->getHeader() == inners.back().getHeader()) {
            break;

        // Checks for two short lists
        } else if ((k->sizeOfThisInnerList() <= shorter) && (i->sizeOfThisInnerList() <= shorter) &&
                   (size() != 2) && (size() != 1)) {

            auto m = k;

            // Check for if 3 short lists are in a row
            if(k->getHeader() != inners.back().getHeader()) {
                m++;
                if(m->sizeOfThisInnerList() <= shorter) {
                    i->merge(*k);
                    i->merge(*m);
                    m->clean();
                    inners.erase(m++);
                    k->clean();
                    inners.erase(k++);
                    consolidate();
                    break;
                }
            }

            i->merge(*k);
            k->clean();
            inners.erase(k++);
            consolidate();

        // Checks for lists that are too long
        } else if ((i->sizeOfThisInnerList() > longer) && (size() > 2)) {

            inners.insert(++i, i->split());
            consolidate();
        }
    }
}

// Adds a value to the inner list at the front
void SquareList::addFirst(int data) {
    auto *current = new InnerSquareList;
    current->addFirst(data);
    inners.insert(inners.begin(), *current);
    consolidate();
}

// Adds an inner list to the back and then consolidates
void SquareList::addLast(int data) {
    auto *current = new InnerSquareList;
    current->addFirst(data);
    inners.insert(inners.end(), *current);
    consolidate();
}

// Removes the first inner list
int SquareList::removeFirst() {
    return remove(0);
}

void SquareList::add(int pos, int data) {
    // Check
    if (size() < pos) {
        std::cout << "Error with position inputted!";
    }

    // Declare variables
    int cnt = 0;
    int cnt2 = 0;

    // To save time
    if (pos == this->size() - 1) {
        inners.back().add(inners.back().sizeOfThisInnerList() - 1, data);
        consolidate();
        return;
    } else if (pos == 0) {
        inners.front().add(0, data);
        consolidate();
        return;
    } else if (pos < inners.front().sizeOfThisInnerList()) {
        inners.front().add(pos, data);
        consolidate();
        return;
    }

    // Traverses through inners and checks to see if the position exists, then removes it.
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt += i->sizeOfThisInnerList();
        if (pos < cnt) {
            i->add(pos - cnt2 - 1, data);
            consolidate();
            break;
        }
        cnt2 = cnt - 1;
    }

}

// Traverses through the inner linked lists and returns the value at pos, if it is in that inner list and removes it
int SquareList::remove(int pos) {
    // Check
    if (size() < pos) {
        std::cout << "Error with position inputted!";
    }

    // Declare variables
    int cnt = 0;
    int final = 0;
    int cnt2 = 0;

    // To save time
    if (pos == this->size() - 1) {
        final = inners.back().remove(inners.back().sizeOfThisInnerList() - 1);
        consolidate();
        return final;
    } else if (pos == 0) {
        final = inners.front().remove(0);
        consolidate();
        return final;
    } else if (pos < inners.front().sizeOfThisInnerList()) {
        final = inners.front().remove(pos);
        consolidate();
        return final;
    }

    // Traverses through inners and checks to see if the position exists, then removes it.
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt += i->sizeOfThisInnerList();
        if (pos < cnt) {
            final = i->remove(pos - cnt2 - 1);
            consolidate();
            return final;
        }
        cnt2 = cnt - 1;
    }
    return 0;
}

// Traverses through the inner linked lists and returns the value at pos, if it is in that inner list
int SquareList::get(int pos) {
    // Check
    if (size() < pos) {
        std::cout << "Error with position inputted!  -> " << inners.size();
        return 0;
    }

    // Declare variables
    int cnt = 0;
    int cnt2 = 0;

//  To save time
    if (pos == this->size() - 1) {
        return inners.back().get(inners.back().sizeOfThisInnerList() - 1);
    } else if (pos == 0) {
        return inners.front().get(0);
    } else if (pos < inners.front().sizeOfThisInnerList()) {
        return inners.front().get(pos);
    }

//    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
//    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20


    // Loops through and returns the value at a certain position
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt += i->sizeOfThisInnerList();
        if (cnt > pos) {
            return i->get(pos - cnt2 - 1);
        }
        cnt2 = cnt - 1;
    }
    return 0;
}

// Traverses through the inner linked lists and sets the value at pos, if it is in that inner list
void SquareList::set(int pos, int data) {
    // Check
    if (size() < pos) {
        std::cout << "Error with position inputted!";
    }

    // Declare variables
    int cnt = 0;
    int cnt2 = 0;

    // To save time
    if (pos == this->size() - 1) {
        inners.back().set(inners.back().sizeOfThisInnerList() - 1, data);
        return;
    } else if (pos == 0) {
        inners.front().set(0, data);
        return;
    } else if (pos < inners.front().sizeOfThisInnerList()) {
        inners.front().set(pos, data);
        return;
    }

    // Loops through and sets the value at the position given
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt += i->sizeOfThisInnerList();
        if (pos < cnt) {
            i->set(pos - cnt2 - 1, data);
            break;
        }
        cnt2 = cnt - 1;
    }
}

// Traverses through inners and returns the size of all of the elements in inners
int SquareList::size() {
    int cnt = 0;
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt += i->sizeOfThisInnerList();
    }
    return cnt;
}

// Traverses through inners and checks for a value then returns the index of that value.
int SquareList::indexOf(int data) {
    for (auto i = inners.begin(); i != inners.end(); i++) {
        if (i->indexOf(data)) {
            return i->indexOf(data);
        }
    }
    std::cout << "Data does not exist in Square Linked List" << std::endl;
}

void SquareList::dump() {
    int cnt = 0;
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt++;
    }

    std::cout << "*********************************************************" << std::endl;
    std::cout << "SquareList dump:" << std::endl;
    std::cout << "Total size = " << size() << ", # of lists = " << cnt << std::endl;
    for (auto i = inners.begin(); i != inners.end(); i++) {
        std::cout << "=========================================================" << std::endl;
        std::cout << "InnerList dump:" << std::endl;
        std::cout << "size = " << i->sizeOfThisInnerList() << std::endl;
        consolidate();
        i->dump();
        std::cout << "\ntail.data = " << i->getTail()->value << std::endl;
    }
}
