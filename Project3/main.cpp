// Project 3
#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void heapify(int arr[], int n, int i) {
    // Find parent 
    int parent = (i - 1) / 2;
    if (parent >= 0) { 
        
        if (arr[i] > arr[parent]) { 
            swap(arr[i], arr[parent]); 
            // Recursively heapify the parent node 
            heapify(arr, n, parent); 
        } 
    } 
}

void insertNode(int arr[], int& n, int Key)
{
    n = n + 1;

    arr[n - 1] = Key;

    heapify(arr, n, n - 1);
}

void deleteRoot(int arr[], int& n)
{
    int last = arr[n - 1];

    arr[0] = last;

    n = n - 1;

    heapify(arr, n, 0);
}

void printArray(int arr[], int n)
{
    cout << arr[n - 1];
    cout << endl; 
}

int main() {
    string numberString = ""; 
    int n = 0; 

    cout << "Enter command:" << endl;
    cin >> numberString; 
    string numstr = "";
    for (int j = 0; j < numberString.size(); j++) {
                if(isdigit(numberString[j]))
                    numstr += numberString[j];
        }
        
    n = stoi(numstr); 
    numstr = "";
    cout << endl;

    int list[1000];
    string input; 
    string input_parsed; 
    int num = 0; 
    string num_string = "";
    for (int i = 0; i < n; i++) {
        input = "";
        input_parsed = "";
        num = 0; 
        num_string = "";

        getline(cin, input); 

        input_parsed = input.substr(0, 5);

        // INSERT 
        if (input_parsed == "INSER") {
            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
            }
            num = stoi(num_string); 
            insertNode(list, n, num);
            n++; 
        }
        // DELETE 
        else if (input_parsed == "DELET") {
            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
            }
            num = stoi(num_string); 
            deleteRoot(list, n);
            n--; 
        }
        else if (input_parsed == "PRINT") {

            printArray(list, n);
        }
    }
    return 0; 
}

