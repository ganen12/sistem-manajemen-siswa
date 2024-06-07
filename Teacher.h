// Teacher.h
#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include "Class.h"

using namespace std;

const int MAX_CLASSES = 6;

struct Teacher {
    string id;
    string username;
    string password;
    string firstName, lastName;
    string email;
    Class* classes[MAX_CLASSES]; // Array untuk menyimpan pointer ke kelas
    int numClasses = 0;


    Teacher(string id, string username, string password, string firstName, string lastName, string email)
        : id(id), username(username), password(password), firstName(firstName), lastName(lastName), email(email), classes() {}

    void addClass(Class* cls) {
        if (numClasses < MAX_CLASSES) {
            classes[numClasses++] = cls; // Tambahkan kelas ke array dan increment numClasses
        } else {
            cout << "Maksimal kelas yang bisa diajar sudah tercapai." << endl;
        }
    }

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
