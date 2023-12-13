// GUARD 
#pragma once
#ifndef __HEAP_H_INCLUDED__   // if heap.h hasn't been included yet...
#define __HEAP_H_INCLUDED__ 

#include <bits/stdc++.h> 
using namespace std; 

class heap {
    public: 
        priority_queue <int, vector<int>, greater<int> > pq; 
        void add(int ); 
        void removeTop(); 
        bool isEmpty(); 
};

// __HEAP.H_INCLUDED__
#endif