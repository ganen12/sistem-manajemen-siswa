// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "Class.h"
#include "Nilai.h"

using namespace std;

const int MAX_CLASSES_PER_STUDENT = 8;

struct Student {
    string id;
    string username;
    string password;
    string firstName, lastName;
    string email;
    float nilaiRataRata=0;
    Nilai* nilaiPtr;
    Class* enrolledClasses[MAX_CLASSES_PER_STUDENT]; // pointer to the class the student is enrolled in
    int numClasses = 0;
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

    bool isEnrolledInClass(const Class* cls) const {
        for (int i = 0; i < MAX_CLASSES_PER_STUDENT; i++) {
            if (enrolledClasses[i] == cls) {
                return true;
            }
        }
        return false;
    }

    void addClass(Class* cls) {
        if (numClasses < MAX_CLASSES_PER_STUDENT) {
            if (!isEnrolledInClass(cls)) { // Cek apakah siswa sudah terdaftar di kelas ini
                enrolledClasses[numClasses] = cls;
                numClasses++; // Inisialisasi nilai untuk mata pelajaran baru
            } else {
                cout << "Anda sudah terdaftar di kelas ini." << endl;
            }
        } else {
            cout << "Kapasitas maksimal kelas yang bisa diikuti sudah tercapai." << endl;
        }
        this->nilaiRataRata = 0;
        if(this->nilaiPtr == nullptr) {
            this->nilaiPtr = new Nilai(8);
        }
    }

    void removeClass(Class* cls) {
        for (int i = 0; i < numClasses; i++) {
            if (enrolledClasses[i] == cls) {
                for (int j = i; j < numClasses - 1; j++) {
                    enrolledClasses[j] = enrolledClasses[j + 1];
                }
                enrolledClasses[numClasses - 1] = nullptr;
                numClasses--;
                // nilaiPtr->setNilai(cls->mataPelajaran, 0.0f); // Reset nilai untuk mata pelajaran yang dihapus
                return;
            }
        }
        cout << "Anda tidak terdaftar di kelas" << cls->name << endl;
    }

    void setNilaiPtr(Nilai* nilaiPtr) {
        this->nilaiPtr = nilaiPtr;
    }

    string fullName() {
        return this->firstName + " " + this->lastName;
    }

    Class* findClassById(const string& id) const {
        for (int i = 0; i < numClasses; i++) {
            if (enrolledClasses[i]->id == id) {
                return enrolledClasses[i]; // Kembalikan pointer ke kelas yang ditemukan
            }
        }
        return nullptr; // Kembalikan nullptr jika kelas tidak ditemukan
    }

    void displayInfo() {
        system("CLEAR");
        cout << "\n+--- Informasi Siswa -------------------+\n";
        cout << "> ID            : " << this->id << endl;
        cout << "> Username      : " << this->username << endl;
        cout << "> Nama Lengkap  : " << this->fullName() << endl;
        cout << "> Email         : " << this->email << endl;
        cout << "> Kelas yang diikuti: ";
        if (this->numClasses == 0) {
            cout << "Tidak ada kelas yang diikuti." << endl;
        } else {
            cout << endl;
            for (int i = 0; i < this->numClasses; i++) {
                cout << "  - " << enrolledClasses[i]->fullClassName() << endl;
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

#endif // STUDENT_H
