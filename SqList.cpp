/*
    Name:   Anna Devadas
    Course: CMSC341, Sec 01
    Project:Project 2
    File:   SqList.cpp
*/

#include <iostream>
#include <list>
#include <stdexcept>
#include <cmath>
#include "SqList.h"

using namespace std;

// default constructor
SqList::SqList() {
    m_listSize = 0;
    m_numItems = 0;
}
 
 // copy constructor
SqList::SqList(const SqList& other) {

    L = other.L;
    m_listSize = other.m_listSize;
    m_numItems = other.m_numItems;
}
 
// destructor?? maybe depends on design
// SqList::~SqList() {}

// overloaded operator
const SqList& SqList::operator=(const SqList& rhs) {
    // use stl list operator= to make lhs L a copy of rhs
    L = rhs.L;
    m_listSize = rhs.m_listSize;
    m_numItems = rhs.m_numItems;
}
 
// function inserts data at the beginning of SqList
// should call consolidate after insertion   
void SqList::addFirst (const Int341& x) {
    // if the Sqlist is empty no inner lists, create new InnerL
    if (L.empty()){
        // create new innerL at front, add item to that list
        list<Int341> s;
        L.push_front(s);
        L.front().push_front(x);
        // increment listSize and numItems
        m_listSize++;
        m_numItems++;
    }
    // if there are already innerL that exists
    else{
        // put item if the first index of first innerL
        L.front().push_front(x);
        // increment items and call consolidate
        m_numItems++;
        consolidate();
    }
}
 
// function inserts data at the end of SqList
// should call consolidate after insertion 
void SqList::addLast (const Int341& x) {
    // if the Sqlist is empty no inner lists, create new innerL
    if (L.empty()){
        // create new innerL at back and add item to list
        list<Int341> s;
        L.push_back(s);
        L.back().push_back(x);
        // increment member variables for size and numItems
        m_listSize++;
        m_numItems++;
    }
    // if innerL exists 
    else{
        // put item in last list in last index
        L.back().push_back(x);
        // incremetn numItems and call consolidate
        m_numItems++;
        consolidate();
    }
}
 
// function removes item from beginning of SqList
// must return Int341 value stored in list. If empty throw out of range
// should call consolidate after removal
Int341 SqList::removeFirst () {
    // if out of range throw error
    if(L.empty()){
        throw out_of_range("The list is empty, cannot remove item.");
    }
    // if SqList is not empty
    else{
        // save value of first item then remove item from list
        Int341 item = L.front().front();
        L.front().pop_front();
        // decrement numItems and call consolidate
        m_numItems -= 1;

        consolidate();
        return item;
    }
}
 
// function removes item from end of SqList
// must return Int341 value stored in list. If empty throw out of range
// should call consolidate after removal
Int341 SqList::removeLast () {
    // if out of range throw error
    if(L.empty()){
        throw out_of_range("The list is empty, cannot remove item.");
    }
    // if SqList is not empty
    else{
        // save value of last item then remove item from list
        Int341 item = L.back().back();
        L.back().pop_back();
        // decrement numItems and call consolidate
        m_numItems -= 1;

        consolidate();
        return item;
    }
}
 
// function inserts item at given position of SqList
void SqList::add(int pos, const Int341& data) {
    // if pos is out of range or the Sqlist is empty
    if (pos > m_numItems || L.empty()){
        throw out_of_range("Cannot access. Position is invalid.");
    }
    else if (pos == m_numItems){
        // put item in last list in last index
        L.back().push_back(data);
        // incremetn numItems and call consolidate
        m_numItems++;
        consolidate();
    }   
    else{
        // create an iterator it set to beginning of SqList
        list< list<Int341> > ::iterator it = L.begin();
        bool match = false;
        int count = 0;

        // loop checks sizes of innerlists and sums them to setermine in which  
        // list the specified pos is located
        while(match == false){
            count += it->size();
            if (pos < count){
                match = true;
            }
            else{
                it++;
            }
        }

        // determine the index pos lies on the matched innerlist
        count = pos - (count - it->size());
        // create innerl iterator, and advance to specific pos
        list<Int341> :: iterator p = it->begin();
        advance(p, count);

        // insert data at position of iterator p
        it->insert(p, data);
        m_numItems++;
        consolidate();
    }
}
 
// function to remove an item from a given position of a SqList and return value
Int341 SqList::remove(int pos) {
    // if pos is out of range or the Sqlist is empty
    if (pos >= m_numItems || L.empty()){
        throw out_of_range("Cannot access. Position is invalid.");
    }
    else{
        // create an iterator it set to beginning of SqList
        list< list<Int341> > ::iterator it = L.begin();
        bool match = false;
        int count = 0;

        // loop checks sizes of innerlists and sums them to setermine in which  
        // list the specified pos is located
        while(match == false){
            count += it->size();
            if (pos < count){
                match = true;
            }
            else{
                it++;
            }
        }

        // determine the index pos lies on the matched innerlist
        count = pos - (count - it->size());
        // create innerl iterator, and advance to specific pos
        list<Int341> :: iterator p = it->begin();
        advance(p, count);

        Int341 item = *p;   // saves value of position in item
        it->erase(p);   // remove data at position of iterator p
        m_numItems--;
        consolidate();

        return item;
    }
}
 
// overloads [] to access given position in SqList
// can be used to return value at index, or to modify index's value
Int341& SqList::operator[](int pos) {
    // if pos is out of range or the Sqlist is empty
    if (pos >= m_numItems || L.empty()){
        throw out_of_range("Cannot access. Pos is invalid.");
    }
    // create an iterator it set to beginning of SqList
    list< list<Int341> > ::iterator it = L.begin();
    bool match = false;
    int count = 0;

    // loop checks sizes of innerlists and sums them to setermine in which  
    // list the specified pos is located
    while(match == false){
        count += it->size();
        if (pos < count){
            match = true;
        }
        else{
            it++;
        }
    }

    // determine the index pos lies on the matched innerlist
    count = pos - (count - it->size());
    // create innerl iterator, and advance to specific pos
    list<Int341> :: iterator p = it->begin();
    advance(p, count);
    
    return *p; 
}

// returns the index of first occurence of data in SqList
// if data does not appear in list, return -1
int SqList::indexOf(const Int341& data) {
    // if empty throw our of range
    if (L.empty()){
        throw out_of_range("The SqList is empty.");
    }
    
    int index = 0;
    // Traverses top level list
    for(list< list<Int341> > :: iterator it = L.begin(); it!=L.end(); ++it){
        // traverses innner lists
        for(list<Int341> :: iterator p = it->begin(); p!=it->end(); ++p){
            // if the current data = input data return index
            if(data.m_data == p->m_data){ return index;}
            // if have reached end of SqList return -1
            else if (index == m_numItems - 1){ return -1;}
            // else increment index
            else{ index++;}
        }
    }

}

// consolidate function. traverses the top-level list. 
// for empty inner list, remove. for two adjacent short inner lists, merge. 
// when an inner list has more than 2 √n items, split into two lists of equal length. 
void SqList::consolidate() {
    // create iterator for top level list
    list< list<Int341> > :: iterator it = L.begin();
    // runs until iterator reaches past the end of the list
    while( it!=L.end()){
        // if the innerlist is empty eraseit
        if(it->empty()) {
            it = L.erase(it);
        }
        // case checks for two adjacent shortlists
        else if(shortList(*it)){
            // creates a copy of iterator and move to next innerlist
            list< list<Int341> > ::iterator cit = it;
            ++cit;
            // checks to make sure innerlist isn's = end()
            if(cit!=L.end()){
                if(shortList(*cit)){
                    // merges next list into current shortlist
                    list<Int341> :: iterator a = it->end();
                    it->splice(a, *cit);
                }
            }
            it++;
        }
        // case checks for too longlist
        else if(longList(*it)){
            // create new iterator cit and insert new innerlist
            list< list<Int341> > ::iterator cit = it;
            ++cit;
            // create new innerlist and insert after current list
            list<Int341> s;
            L.insert(cit, s);
            --cit;
            
            int half = (it->size() / 2) - 1;  // divide list in half
            list<Int341> :: iterator a = it->begin();
            advance(a, half);   // move iterator a to halfway through list
            cit->splice(cit->begin(), *it, a, it->end());

            advance(it, 2); // increment iterator 2 spaces forward
        }
        else{
            it++;
        }

    }
}


// function calculates if innerlist does not meet lowerbound
bool SqList::shortList(const list<Int341> & s) {
    if(sqrt(m_numItems) / 2 >= s.size()) { return true;}
    else{
        return false;
    }
}

// function calculates if innerlist exceeds upperbound
bool SqList::longList(const list<Int341> & s){
    if(sqrt(m_numItems) * 2 <= s.size()) {
        return true;
    }
    else{
        return false;
    }
}

// function that returns the number of items in a SqList
int SqList::numItems() {
    return m_numItems;
} 

// debugging function; prints various attributes of SqList
void SqList::dump() {
    cout << "----- SqList dump() -----" << endl;
    cout << "number of items = " << m_numItems << endl;
    cout << "-------------------------" << endl;

    int index = 0;
    for(list< list<Int341> > :: iterator it = L.begin(); it!=L.end(); ++it){
        cout << index << "(" << it->size() << ") : "; 
        for(list<Int341> :: iterator p = it->begin(); p!=it->end(); ++p){
            cout << p->m_data << " ";
        }
        index++;
        cout << endl;
    }
    cout << endl;
    cout << "-------------------------" << endl; 
} 