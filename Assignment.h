// Assignment.h
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include "Class.h"

using namespace std;

struct Assignment {
    string id;
    string description;
    string dueDate;
    Class* classPtr; // pointer to the class this assignment belongs to

    Assignment(string id, string description, string dueDate)
        : id(id), description(description), dueDate(dueDate), classPtr(nullptr) {}

    void display() {
        cout << "Assignment ID: " << id << endl;
        cout << "Description: " << description << endl;
        cout << "Due Date: " << dueDate << endl;
        // cout << "Class: " << classPtr->name << endl;
        cout << endl;
    }
};

Assignment *assign;

struct CSVRecordAssignment {
    string id;
    string description;
    string dueDate;   

    CSVRecordAssignment(string id, string description, string dueDate)
    : id(id), description(description), dueDate(dueDate) {} 
};

#endif // ASSIGNMENT_H