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
    float nilaiRataRata=0;
    Class* classPtr; // pointer to the class the student is enrolled in

    // Student(string id, string username, string password, string firstName, string lastName, string email, Class* classPtr = nullptr)
    // : id(id), username(username), password(password), firstName(firstName), lastName(lastName), email(email), classPtr(classPtr), Ipk() {}   

    void initialize(string id, string username, string password, string firstName, string lastName, string email) {
        this->id = id;
        this->username = username;
        this->password =  password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
    }

    void setClass(Class* cls) {
        this->classPtr = cls;
        this->nilaiRataRata = 0;
    }

    Class* getClass() const { 
        return classPtr;
    }

    void display() {
        cout << id << ", " << username << ", " << password << ", " << firstName << ", " << email << ", " << classPtr->name << endl;
    }
};

#endif // STUDENT_H
