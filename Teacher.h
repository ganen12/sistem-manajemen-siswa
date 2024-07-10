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
    string teachedSubject;
    int teachedSubjectId;
    Class* classes[MAX_CLASSES]; // Array untuk menyimpan pointer ke kelas
    int numClasses = 0;

    void initialize(string id, string username, string password, string firstName, string lastName, string email, string teachedSubject) {
        this->id = id;
        this->username = username;
        this->password =  password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->email = email;
        this->teachedSubject = teachedSubject;
    }

    void addClass(Class* cls) {
        if (numClasses < MAX_CLASSES) {
            if (cls->subject == teachedSubject) {
                this->classes[numClasses] = cls; // Tambahkan kelas ke array dan increment numClasses
                numClasses++; // Increment numClasses           
            } else {
                cout << "Anda tidak mengajar mata pelajaran ini." << endl;
            }
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
                return;
            }            
        }
        cout << "Kelas dengan ID " << cls->id << " tidak ditemukan." << endl;
    }
    
    string fullName() {
        return this->firstName + " " + this->lastName;
    }

    void displayInfo() {
        system("CLEAR");
        cout << "\n+--- Informasi Guru -------------------+\n";
        cout << "> ID            : " << this->id << endl;
        cout << "> Username      : " << this->username << endl;
        cout << "> Nama Lengkap  : " << this->fullName() << endl;
        cout << "> Email         : " << this->email << endl;
        cout << "> Mapel         : " << this->teachedSubject << endl;
        cout << "> Kelas yang diajar: ";
        if (this->numClasses == 0) {
            cout << "Tidak ada kelas yang diajar." << endl;
        } else {
            cout << endl;
            for (int i = 0; i < this->numClasses; i++) {
                cout << "  - " << classes[i]->fullClassName() << endl;
            }
        }
        cout << "+---------------------------------------+" << endl;
    }

    void editInfo() {
        int option;
        string newUsername, newPassword, newFirstName, newLastName, newEmail;
        do {
            this->displayInfo();
            cout << "\n--- Edit Informasi Siswa ---\n";
            cout << "1. Ubah Username\n";
            cout << "2. Ubah Password\n";
            cout << "3. Ubah Nama Lengkap\n";
            cout << "4. Ubah Email\n";
            cout << "0. Kembali\n";
            cout << "Pilih opsi: ";

            cin >> option;
            system("CLEAR");
            switch (option) {
            case 1:
                cout << "Masukkan username baru (tanpa spasi):\n> "; cin >> newUsername;
                if (newUsername.find(' ')!= string::npos) {
                    cout << "Username tidak boleh mengandung spasi." << endl;
                    break;
                }
                this->username = newUsername;
                break;
            case 2:
                cout << "Masukkan password lama:\n> "; cin >> newPassword;
                if (newPassword != this->password) {
                    cout << "Password salah";
                    system("PAUSE");
                    break;
                }
                cout << "Masukkan password baru:\n> "; cin >> newPassword;
                if (newUsername.find(' ')!= string::npos) {
                    cout << "Password tidak boleh mengandung spasi." << endl;
                    break;
                }
                this->password = newPassword;
                break;
            case 3:
                cout << "Masukkan first name baru (tanpa spasi):\n> "; cin >> newFirstName;
                cout << "Masukkan last name baru (tanpa spasi):\n> "; cin >> newLastName;
                if (newFirstName.find(' ')!= string::npos || newLastName.find(' ')!= string::npos) {
                    cout << "first name atau last name tidak boleh mengandung spasi." << endl;
                    break;
                }
                this->firstName = newFirstName;
                this->lastName = newLastName;
                break;
            case 4:
                cout << "Masukkan email baru:\n> "; cin >> newEmail;
                if (newEmail.find(' ')!= string::npos) {
                    cout << "first name atau last name tidak boleh mengandung spasi." << endl;
                    break;
                }
                this->email = newEmail;
                break;
            case 0:
                break; // Kembali ke menu sebelumnya
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
            }
        } while (option != 0);
    }
};


#endif // TEACHER_H
