#include "lab01.h"

bool insertAt(int a[], int& size, int cap, int pos, int x) {
    // reject if full or pos is outside [0, size]
    if (size >= cap) return false;
    if (pos < 0 || pos > size) return false;

    // shift from right to left
    for (int i = size; i > pos; i--) {
        a[i] = a[i - 1];
    }
    a[pos] = x;
    size++;
    return true;
}

bool deleteAt(int a[], int& size, int pos) {
    // reject positions outside [0, size-1]
    if (pos < 0 || pos >= size) return false;

    // shift from left to right
    for (int i = pos; i < size - 1; i++) {
        a[i] = a[i + 1];
    }
    size--;
    return true;
}

