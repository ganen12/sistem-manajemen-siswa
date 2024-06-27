#include "Stack.h"
#include <iostream>
#include <string>
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
                            to_string(ltm->tm_min);
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

void Stack::printHistory(bool isTeacher) {
    system("CLEAR");
    if (isEmpty()) {
        cout << "History log kosong." << endl;
        return;
    }

    cout << "History Log:" << endl;
    if (isTeacher) {
        for (int i = this->top; i >= 0; i--) {
            if (this->data[i].find("(GURU)") != string::npos) {
                cout << this->data[i] << endl;
            }
        }
    } else {
        for (int i = this->top; i >= 0; i--) {
            if (this->data[i].find("(SISWA)") != string::npos) {
                cout << this->data[i] << endl;
            }
        }
    }

    
}