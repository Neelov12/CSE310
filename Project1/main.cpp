#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void bubble_sort(int arg_array[], int n)
{
    bool isSwapped;
    for (int i = 0; i < n - 1; i++) {
        isSwapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arg_array[j] > arg_array[j + 1]) {
                swap(arg_array[j], arg_array[j + 1]);
                isSwapped = true;
            }
        }
        if (isSwapped == false)
            break;
    }
}

int main() {
    int arraySize; 
    
    // Receives user input for size of list 
    cout << "Please enter list size: "; 
    cin >> arraySize;

    int array[arraySize];

    // Recieves user input for contents of list
    cout << "Please enter contents of list: "; 
    for (int i = 0; i < arraySize; i++) {
        cin >> array[i]; 
    }

    bubble_sort(array, arraySize);

    // Print sorted array
    cout << "Sorted array: "; 
    for (int i = 0; i < arraySize; i++) {
        cout << " " <<  array[i]; 
    } 
    cout << endl; 

     return 0; 
}