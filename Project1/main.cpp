#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
  
        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

int main() {
    int arraySize; 
    string userInput; 
    
    cin >> arraySize;

    int array[arraySize];

    for (int i = 0; i < arraySize; i++) {
        cin >> array[i]; 
    }

    for (int i = 0; i < arraySize; i++) {
        cout << array[i]; 
        cout << " "; 
    }
    

     return 0; 
}