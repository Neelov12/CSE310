# include "heap.h"

void heap::add(int n) {
    pq.push(n); 
}

void heap::removeTop() {
    pq.pop();
}

bool heap::isEmpty() {
    return pq.empty();
}

