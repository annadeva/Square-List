/*
    Name:   Anna Devadas
    Course: CMSC341, Sec 01
    Project:Project 2
    File:   SqList.h
*/

#ifndef _SQLIST_H_
#define _SQLIST_H_

#include <list>
#include "Int341.h"

class SqList{

public:

    // default constructor
    SqList() ;

    // copy constructor
    SqList(const SqList& other) ;

    // destructor?? maybe depends on design
    //~SqList() ;

    // overloaded operator
    const SqList& operator=(const SqList& rhs) ;

    // function inserts data at the beginning of SqList
    // should call consolidate after insertion   
    void addFirst (const Int341& x) ;

    // function inserts data at the end of SqList
    // should call consolidate after insertion 
    void addLast (const Int341& x) ;

    // function removes item from beginning of SqList
    // must return Int341 value stored in list. If empty throw out of range
    // should call consolidate after removal
    Int341 removeFirst ()  ;

    // function removes item from end of SqList
    // must return Int341 value stored in list. If empty throw out of range
    // should call consolidate after removal
    Int341 removeLast ()  ;

    // function inserts item at given position of SqList
    void add(int pos, const Int341& data) ;

    // function to remove an item from a given position of a SqList and return value
    Int341 remove(int pos) ;

    // overloads [] to access given position in SqList
    // can be used to return value at index, or to modify index's value
    Int341& operator[](int pos) ;

    // if data does not appear in list, return -1
    int indexOf(const Int341& data) ;

    // consolidate function
    void consolidate() ;

    // function calculates if innerlist does not meet lowerbound
    bool shortList(const std::list<Int341> & s);

    // function calculates if innerlist exceeds upperbound
    bool longList(const std::list<Int341> & s);

    // function that returns the number of items in a SqList
    int numItems() ; 

    // debugging function; prints various attributes of SqList
    void dump() ; 

    // grading function, do not implement
    void inspector() ; 

private:
    // initializes SqList of lists
    std::list< std::list<Int341> > L;

    int m_listSize; // number of indices in top level SqList
    int m_numItems; // total number of items in SqList

};

#endif