// Assignment.h
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include "Class.h"

using namespace std;

const string SUBJECTS[] = {"Bahasa Indonesia", "Bahasa Inggris", "Matematika", "IPA", "IPS", "PKN", "Seni Budaya", "Penjaskes"};

struct Assignment {
    string id;
    string subject;
    int subjectId;
    string description;
    string dueDate;
    Class* classPtr; // pointer to the class this assignment belongs to

    // Assignment(string id, string description, string dueDate, Class* classPtr = nullptr)
    //     : id(id), description(description), dueDate(dueDate), classPtr(classPtr) {}

    void initialize(string id, int subjectNum, string description, string dueDate) {
        this->id = id;
        this->subjectId = subjectNum - 1;
        this->description = description;
        this->dueDate = dueDate;
        this->classPtr = nullptr;
        this->subject = "";
    }

    void setSubject() {
        this->subject = SUBJECTS[this->subjectId];
    }
    
    void setClass(Class* cls) {
        this->classPtr = cls;
    }

    void display() {
        cout << "Assignment ID: " << id << endl;
        cout << "Mata Pelajaran: " << subject << endl;
        cout << "Deskripsi: " << description << endl;
        cout << "Tanggal Tenggat: " << dueDate << endl;
        // cout << "Class: " << classPtr->name << endl;
        cout << endl;
    }
};

#endif // ASSIGNMENT_H
