///////////////////////////////////////////////////////////////
//  File:   InnerSquareList.cpp
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   9/19/2019
//  Usage:  InnerSquareList are the nodes that come off of the standard doubly linked list.
///////////////////////////////////////////////////////////////

using namespace std;

#include <climits>
#include "InnerSquareList.h"

// Get Method for m_head
Node *InnerSquareList::getHeader() {
    return m_head;
}

// Get Method for m_tail
Node *InnerSquareList::getTail() {
    return m_tail;
}

// Default Constructor
InnerSquareList::InnerSquareList() {
    m_head = nullptr;
    m_tail = nullptr;
    m_length = 0;
}

// Initialized constructor
InnerSquareList::InnerSquareList(Node *header, Node *tail, size_t length) {
    m_head = header;
    m_tail = tail;
    m_length = length;
}

// Destructor
InnerSquareList::~InnerSquareList() = default;

// Clears out LinkedList and clears memory
void InnerSquareList::clean() {
    auto *temp = m_head;

//  Traverses from the head to the tail and clears and deletes every node
    while (temp != nullptr and m_head != m_tail) {
        temp = m_head;
        m_head = m_head->next;
        delete temp;
        temp = m_head->next;
    }
    m_head = nullptr;
    m_tail = nullptr;
    delete m_head;
    delete m_tail;
    m_length = 0;
}

// Adds a value to a specific position
void InnerSquareList::add(int pos, int data) {
    // Check
    if (pos > m_length) {
        cout << "Error: Wrong position";
    }
    m_length++;

//    Traverse to the position and set value
    int cnt = 0;
    auto *newNode = new tagNode;
    newNode->value = data;
    tagNode *current = m_head;
    tagNode *previous = current;
    while (current != nullptr) {
        if (cnt == pos) {

//          Check for the starting position, so you can set head.
            if (pos == 0) {
                m_head = newNode;
                newNode->next = current;
                previous = nullptr;
                delete previous;
                current = nullptr;
                delete current;
                break;
            }
            newNode->next = current;
            previous->next = newNode;
            previous = nullptr;
            delete previous;
            current = nullptr;
            delete current;
            break;
        }
        previous = current;
        current = current->next;
        cnt++;
    }
    delete current;
}

// Creates a new node and sets the value to data, then points to the first node, and sets head to the new node
void InnerSquareList::addFirst(int data) {
    m_length++;
    auto *newNode = new tagNode;
//  Checks to see if head is equal to tail
    if (m_length == 1) {
        newNode->value = data;
        newNode->next = nullptr;
        m_head = newNode;
        m_tail = newNode;
        return;
    }
    newNode->value = data;
    newNode->next = m_head;
    m_head = newNode;
}

// Creates a new node and sets the value of data, then points to the last node and sets tail to the new node
void InnerSquareList::addLast(int data) {
    m_length++;
    auto *newNode = new tagNode;

//  Checks to see if head is equal to tail
    if (m_length == 1 or m_length >= 1000000000) {
        newNode->value = data;
        newNode->next = nullptr;
        m_head = newNode;
        m_tail = newNode;
        return;
    }
    newNode->value = data;
    newNode->next = nullptr;
    m_tail->next = newNode;
    m_tail = newNode;
}

// Removes a value from a specific position
int InnerSquareList::remove(int pos) {
    // Check
    if (pos > sizeOfThisInnerList()) {
        cout << "Error: Wrong position" << endl;
    }

//  Initializes variables and objects
    int cnt = 0;
    tagNode *current = m_head;
    tagNode *previous = current;

//  Checks to see if the place to remove is at the front of the list, to avoid problems with head.
    if (pos == 0) {
        if (current == m_tail) {
            m_tail = previous;
        }
        m_head = current->next;
        cnt = current->value;
        current = nullptr;
        previous = nullptr;
        delete current;
        delete previous;
        m_length--;
        return cnt;
    }

    while (current != nullptr) {
        if (cnt == pos) {

//          Checks to see if the tail is the index being removed
            if (m_tail == current) {
                m_tail = previous;
            }
            previous->next = current->next;
            cnt = current->value;
            current->next = nullptr;
            previous = nullptr;
            current = nullptr;
            delete current;
            delete previous;
            m_length--;
            return cnt;
        }
        cnt++;
        previous = current;
        current = current->next;
    }
    return -1;
}

// Method that returns the value at a specific position
int InnerSquareList::get(int pos) const {
    // Check
    if (pos > sizeOfThisInnerList()) {
        cout << "Error: Wrong position" << endl;
        return 0;
    }

//  Initializes variables and objects
    int cnt = 0;
    tagNode *current = m_head;

//  Loops through until position is reached, then returns the value
    while (current != nullptr) {
        if (cnt == pos) {
            return current->value;
        }
        current = current->next;
        cnt++;
    }
    return 0;
}

// Method that changes the value at a specific position in the list
void InnerSquareList::set(int pos, int data) {
    // Check
    if (pos >= sizeOfThisInnerList()) {
        cout << "Error: Wrong position:" << pos << endl;
    }

//  Declare variables and objects
    tagNode *current = m_head;

//  Loops through list until position is met, then reallocates the data to newNode and discards the old node.
    for (int i = 0; i < sizeOfThisInnerList(); i++) {
        if (i == pos) {
            current->value = data;
            current = nullptr;
            delete current;
            break;
        }
        current = current->next;
    }
}

// Getter for the length of the inner list
int InnerSquareList::sizeOfThisInnerList() const {
    return m_length;
}

// Returns the index of the place where the data is stored
int InnerSquareList::indexOf(int data) const {
    tagNode *current = m_head;
    int cnt = 0;

//  Loops through and checks to see if the value is equal to the data parameter
    while (current != nullptr) {
        if (current->value == data) {
            current = nullptr;
            delete current;
            return cnt;
        }
        cnt++;
        current = current->next;
    }
    return -1;
}

// Merges two lists into one
void InnerSquareList::merge(InnerSquareList &isl) {
    auto *current = isl.getHeader();
    while (current != nullptr) {
        addLast(current->value);
        current = current->next;
    }
}


InnerSquareList InnerSquareList::split() {
    auto *newInn = new InnerSquareList;
    tagNode *current = m_head;
    for (unsigned int i = 0; i < m_length; i++) {
        if (i >= m_length / 2) {
            newInn->addLast(current->value);
            current = current->next;
            remove(i);
            i--;
            continue;
        }
        current = current->next;
    }
    return *newInn;
}

void InnerSquareList::dump() {
    auto *current = m_head;
    while (current != nullptr) {
        cout << "[" << current->value << "]";
        current = current->next;
    }
    current = nullptr;
    delete current;
}
