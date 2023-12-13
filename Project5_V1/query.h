
// GUARD 
#ifndef __QUERY_H_INCLUDED__   // if query.h hasn't been included yet...
#define __QUERY_H_INCLUDED__ 

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <sstream> 




using namespace std; 

class query {

    private: 
        bool vtxFound; 

    public: 
        query();
        string interpret(string a, int b);
        bool case1IsValid(int a,int b,int c, int d);
        bool case2IsValid(int a, int b);
        string getNthWord(string a, int b);
};

#endif