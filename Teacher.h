// Teacher.h
#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include "Class.h"
#include <array> 

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

    void addClass(Class* cls) {
        if (numClasses < MAX_CLASSES) {
            this->classes[numClasses] = cls; // Tambahkan kelas ke array dan increment numClasses
            numClasses++; // Increment numClasses
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
        for ( Class* cls : classes ) {
            if (cls!= nullptr) {
                cout << cls->name << endl;
            } else {
                cout << "Tidak ada kelas" << endl;
            }
        }
        
    }

};


#endif // TEACHER_H
