///////////////////////////////////////////////////////////////
//  File:   SquareList.h
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: Sean Miller
//  Date:   9/19/2019
//  Usage:  SquareList is the data structure that is being created
///////////////////////////////////////////////////////////////

#ifndef SQUARELIST_H
#define SQUARELIST_H

#include <list>
#include <cmath>
#include "InnerSquareList.h"

class SquareList {
    //the horizonal list containing all inner lists
    std::list<InnerSquareList> inners;
public:
    SquareList();

    ~SquareList();

    //Keep the length of each inner list satisfying the definition of a Square List
    void consolidate();

    //insert
    void addFirst(int data);

    void addLast(int data);

    int removeFirst();

    //insert a value to be at location "pos"
    void add(int pos, int data);

    int remove(int pos);

    int get(int pos);

    void set(int pos, int data);

    //total number of nodes in all inner lists
    int size();

    //Position of first occurrence of a value
    int indexOf(int data);

    //Printing out information of Square List for debugging
    void dump();
};

#endif