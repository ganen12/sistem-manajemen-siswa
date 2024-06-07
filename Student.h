// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "Class.h"

using namespace std;

struct Student {
    string id;
    string username;
    string password;
    string firstName, lastName;
    string email;
    float Ipk;
    Class* classPtr; // pointer to the class the student is enrolled in

    Student(string id, string username, string password, string firstName, string lastName, string email, Class* classPtr = nullptr)
    : id(id), username(username), password(password), firstName(firstName), lastName(lastName), email(email), classPtr(classPtr), Ipk() {}   

    void setClass(Class* cls) {
        classPtr = cls;
    }

    Class* getClass() const { 
        return classPtr;
    }

    void display() {
        cout << id << ", " << username << ", " << password << ", " << firstName << ", " << email << ", " << classPtr->name << endl;
    }
};

struct CSVRecordStudent {
    string id;
    string username;
    string password;
    string name;
    string email;

    CSVRecordStudent(string id, string username, string password, string name, string email)
    : id(id), username(username), password(password), name(name), email(email) {}     
};

#endif // STUDENT_H
