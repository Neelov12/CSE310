// C++ program for insertion sort
#include <bits/stdc++.h>
using namespace std;

// insertion sort
int* insertion_sort (int arr[], int number_of_elements)
{
    for (int index = 1; index < number_of_elements; index++) {
        int value_at_index = arr[ index ];
        int second_index = index - 1;
// Move elements of arr[0..i-1],
// that are greater than value_at_index,
// to one position ahead of their
// current position
    while (second_index >= 0 && arr[ second_index ] > value_at_index)
    {
        arr[ second_index + 1 ] = arr[ second_index ];
        second_index --;
    }
    arr[ second_index + 1 ] = value_at_index;
    }
    return arr;
    }
// Function to print array. Array is called by reference
void print_array (int arr[], int number_of_elements)
{
    for (int index = 0; index < number_of_elements; index++)
        cout << arr[ index ] << " ";
        cout << endl;
}

int main()
{
// Number of elements in array
int number_of_elements;
cin >> number_of_elements;
// Elements in Array
int arr[ number_of_elements ];

for (int index = 0; index < number_of_elements; index ++)
    cin >> arr[ index ];

    int* ans = insertion_sort (arr, number_of_elements);
    print_array (ans, number_of_elements);
    
return 0;
}