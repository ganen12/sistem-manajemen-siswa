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

    void initialize(string id, string username, string password, string firstName, string lastName, string email) {
        this->id = id;
        this->username = username;
        this->password =  password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
    }

    void addClass(Class* cls) {
        if (numClasses < MAX_CLASSES) {
            this->classes[numClasses] = cls; // Tambahkan kelas ke array dan increment numClasses
            numClasses++; // Increment numClasses
        } else {
            cout << "Maksimal kelas yang bisa diajar sudah tercapai." << endl;
        }
    }

    void removeClass(Class* cls) {
        for (int i = 0; i < numClasses; i++) {
            if (classes[i] != nullptr && classes[i]->id == cls->id) {
                // Hapus kelas dari array
                for (int j = i; j < numClasses - 1; j++) {
                    classes[j] = classes[j + 1];
                }
                classes[numClasses - 1] = nullptr;
                numClasses--;
                cout << "Kelas dengan ID " << cls->id << " berhasil dihapus." << endl;
                return;
            }            
        }
        cout << "Kelas dengan ID " << cls->id << " tidak ditemukan." << endl;
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
