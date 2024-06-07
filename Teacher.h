// Teacher.h
#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include "Class.h"

using namespace std;

struct Teacher {
    string id;
    string username;
    string password;
    string firstName, lastName;
    string email;
    vector<Class*> classes; // pointers to classes the teacher is teaching

    Teacher(string id, string username, string password, string firstName, string lastName, string email)
        : id(id), username(username), password(password), firstName(firstName), lastName(lastName), email(email), classes() {}

    void display() {
        cout << "Teacher ID: " << id << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " <<  password << endl;
        cout << "Name: " << firstName << endl;
        cout << "email: " << email << endl;
        cout << "Classes: " << endl;
        // for (int i = 0; i < classes.size(); i++) {
        //     classes[i]->display();
        // }
    }

};

struct CSVRecordTeacher {
    string id;
    string username;
    string password;
    string name;
    string email;

    CSVRecordTeacher(string id, string username, string password, string name, string email)
    : id(id), username(username), password(password), name(name), email(email) {}     
};

#endif // TEACHER_H
