#include <iostream>


void reverse(char a[]) {
    int length = 0;
    while (a[length] != '\0') {
        length++;
    }
    for (int i = 0; i < length / 2; i++) {
        char temp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = temp;
    }
}


void delete_char(char a[], char c) {
    int i = 0, j = 0;
    while (a[i] != '\0') {
        if (a[i] != c) {
            a[j] = a[i];
            j++;
        }
        i++;
    }
    a[j] = '\0';
}


void pad_right(char a[], int n) {
    int length = 0;
    while (a[length] != '\0') {
        length++;
    }
    if (length >= n) {
        return;
    }
    for (int i = length; i < n; i++) {
        a[i] = ' ';
    }
    a[n] = '\0';
}


void pad_left(char a[], int n) {
    int length = 0;
    while (a[length] != '\0') {
        length++;
    }
    if (length >= n) {
        return;
    }
    for (int i = length; i >= 0; i--) {
        a[i + n - length - 1] = a[i];
    }
    for (int i = 0; i < n - length; i++) {
        a[i] = ' ';
    }
}


void truncate(char a[], int n) {
    int length = 0;
    while (a[length] != '\0') {
        length++;
    }
    if (length <= n) {
        return;
    }
    a[n] = '\0';
}


bool is_palindrome(char a[]) {
    int length = 0;
    while (a[length] != '\0') {
        length++;
    }
    for (int i = 0; i < length / 2; i++) {
        if (a[i] != a[length - i - 1]) {
            return false;
        }
    }
    return true;
}

// Hàm lọc trái 
void trim_left(char a[]) {
    int i = 0, j = 0;
    while (a[i] != '\0' && a[i] == ' ') {
        i++;
    }
    while (a[i] != '\0') {
        a[j] = a[i];
        i++;
        j++;
    }
    a[j] = '\0';
}

// Hàm lọc phải 
void trim_right(char a[]) {
    int length = 0;
    while (a[length] != '\0') {
        length++;
    }
    length--;
    while (length >= 0 && a[length] == ' ') {
        a[length] = '\0';
        length--;
    }
}
