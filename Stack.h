#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

const int MAX_STACK = 100; // Batasan ukuran stack

struct Stack {
    int top;
    string data[MAX_STACK]; // Ubah tipe data menjadi string untuk menyimpan log

    Stack() : top(-1) {}

    void inisialisasi();
    void push(const string& data);
    void pop();
    void clear();
    bool isEmpty();
    bool isFull();
    void printHistory();
// Fungsi print() tidak diperlukan untuk history log

};

#endif // STACK_H