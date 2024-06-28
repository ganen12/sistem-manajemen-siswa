// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "Class.h"
#include "Nilai.h"

using namespace std;

struct Student {
    string id;
    string username;
    string password;
    string firstName, lastName;
    string email;
    float nilaiRataRata=0;
    Nilai* nilaiPtr;
    Class* classPtr; // pointer to the class the student is enrolled in

    // Student(string id, string username, string password, string firstName, string lastName, string email, Class* classPtr = nullptr)
    // : id(id), username(username), password(password), firstName(firstName), lastName(lastName), email(email), classPtr(classPtr), Ipk() {}   

    void initialize(string id, string username, string password, string firstName, string lastName, string email, Nilai* nilaiPtr = nullptr) {
        this->id = id;
        this->username = username;
        this->password =  password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
        this->nilaiPtr = nilaiPtr;
    }

    void setClass(Class* cls) {
        this->classPtr = cls;
        this->nilaiRataRata = 0;
        if(this->nilaiPtr == nullptr){
            this->nilaiPtr = new Nilai(8);
        }
    }

    void removeClass(Class* cls) {
        this->classPtr = nullptr;
        this->nilaiRataRata = 0;
    }

    void setNilaiPtr(Nilai* nilaiPtr) {
        this->nilaiPtr = nilaiPtr;
    }

    Class* getClass() const { 
        return classPtr;
    }

    string fullName() {
        return this->firstName + " " + this->lastName;
    }

    void display() {
        cout << id << ", " << username << ", " << password << ", " << firstName << ", " << email << ", " << classPtr->name << endl;
    }
};

#endif // STUDENT_H
