#include "Stack.h"
#include <iostream>
#include <ctime>
#include <iomanip>

void Stack::push(const string& data) {
    if (isFull()) {
        cout << "STACK SUDAH PENUH" << endl;
    } else {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        // Format waktu menjadi string
        string timeString = to_string(ltm->tm_mday) + "/" + 
                            to_string(1 + ltm->tm_mon) + "/" + 
                            to_string(1900 + ltm->tm_year) + " " + 
                            to_string(ltm->tm_hour) + ":" + 
                            to_string(ltm->tm_min) + ":" + 
                            to_string(ltm->tm_sec);
        top++;
        this->data[top] = timeString + " -- " + data;
    }
}

void Stack::pop() {
    if (!isEmpty()) {
        top--;
    }
}

void Stack::clear() {
    top = -1;
}

bool Stack::isEmpty() {
    return (top == -1);
}

bool Stack::isFull() {
    return (top >= (MAX_STACK - 1));
}

void Stack::printHistory() {
    if (isEmpty()) {
        cout << "History log kosong." << endl;
    } else {
        cout << "History Log:" << endl;
        for (int i = this->top; i >= 0; i--) {
            cout << this->data[i] << endl;
        }
    }
}