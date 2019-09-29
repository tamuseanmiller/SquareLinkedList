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

    // iterator for loop
    for (auto i = inners.begin(); i != inners.end(); i++) {

        // Checks for empty inner list
        if (i->sizeOfThisInnerList() == 0) {
            i->clean();
            inners.erase(i++);

            // Skip the first iteration since I'm using previous
        } else if (i == inners.begin()) {
            continue;

            // Checks for two short lists
        } else if (((std::prev(i)->sizeOfThisInnerList() + i->sizeOfThisInnerList()) <= (sqrt(size()) / 2)) &&
                   (size() != 1)) {
            std::prev(i)->merge(*i);
            i->clean();
            inners.erase(i++);

            // Checks for lists that are too long
        } else if (i->sizeOfThisInnerList() > 2 * sqrt(size()) && (size() > 2)) {
            auto *current = new InnerSquareList;
            for (unsigned int j = 0; j < i->sizeOfThisInnerList() / 2; j++) {
                current->addLast(i->get(j));
                i->remove(j);
            }
            inners.insert(i, *current);
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
    remove(0);
}

void SquareList::add(int pos, int data) {
    // Check
    if (size() < pos) {
        std::cout << "Error with position inputted!";
    }
    unsigned int cnt = 0;
    for (auto i = inners.begin(); i != inners.end(); i++) {
        if (cnt == pos) {
            i->add(0, data);
        }
        cnt++;
    }
    consolidate();
}

// Traverses through the inner linked lists and returns the value at pos, if it is in that inner list and removes it
int SquareList::remove(int pos) {
    // Check
    if (size() < pos) {
        std::cout << "Error with position inputted!";
    }

    // Declare variables
    unsigned int cnt = 0;
    unsigned int final = 0;
    unsigned int max = 0;

    // Traverses through inners and checks to see if the position exists, then removes it.
    for (auto i = inners.begin(); i != inners.end(); i++) {
        if (pos > i->sizeOfThisInnerList())
            cnt += i->sizeOfThisInnerList();
        if (pos <= cnt) {
            final = i->remove(cnt - pos);
            consolidate();
            return final;
        }
        if (pos <= i->sizeOfThisInnerList())
            cnt += i->sizeOfThisInnerList();
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
    unsigned int max = 0;
    unsigned int cnt = 0;
    unsigned int cnt2 = 0;

    // Loops through and returns the value at a certain position
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt += i->sizeOfThisInnerList();
        if (i->sizeOfThisInnerList() > max)
            max = i->sizeOfThisInnerList();
        if (pos < cnt && max*cnt <= pos) { // TODO: Literally doesn't work
            return i->get(pos - max * cnt2);
        } else if (pos < cnt) {

        }
        cnt2++;
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
    unsigned int cnt = 0;
    unsigned int cnt2 = 0;
    unsigned int max = 0;

    // Loops through and sets the value at the position given
    for (auto i = inners.begin(); i != inners.end(); i++) {
        cnt += i->sizeOfThisInnerList();
        if (i->sizeOfThisInnerList() > max)
            max = i->sizeOfThisInnerList();
        if (pos < cnt) {
            i->set(pos - max * cnt2, data);
            break;
        }
        cnt2++;
    }
}

// Traverses through inners and returns the size of all of the elements in inners
int SquareList::size() {
    unsigned int cnt = 0;
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

}
