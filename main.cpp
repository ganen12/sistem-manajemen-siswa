#include <iostream>
// #include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>
// #include <queue>
// #include <stack>

struct Student;
struct Class;
struct Teacher;
struct Assignment;
struct Pengumpulan;

#include "Student.h"
#include "Class.h"
#include "Teacher.h"
#include "Assignment.h"
#include "Pengumpulan.h"

using namespace std;

void teacherMenu();
void studentMenu();
void teacherClassMenu();
void mainMenu();
void addAssignment();
void assignmentQueue();
// void loadTeachersFromCSV();

struct LoggedIn {
    bool isTeacher;
    string id;
    string username;
    Teacher* teacherPtr;
    Student* studentPtr;

    LoggedIn(bool isTeacher = false, string id = "", string username = "", Teacher* teacherPtr = nullptr, Student* studentPtr = nullptr) 
        : isTeacher(isTeacher), id(id), username(username), teacherPtr(teacherPtr), studentPtr(studentPtr) {}

    void update(bool isTeacher, string id, string username, Teacher* teacher = nullptr, Student* student = nullptr) {
        this->isTeacher = isTeacher;
        this->id = id;
        this->username = username;
        this->teacherPtr = teacher;
        this->studentPtr = student;
    }
    
    void display() {
        cout << "Saat ini logged in:" << endl;
        cout << "\t" << (isTeacher ? "Guru" : "Siswa") << endl;

        if (isTeacher) {
            cout << "\tID: " << id << endl;
            cout << "\tUSERNAME: " << username << endl;
        } else if (!isTeacher) {
            cout << "\tID: " << id << endl;
            cout << "\tUSERNAME: " << username << endl;
        } else {
            cout << "\tInformasi pengguna tidak ditemukan." << endl;
        }
    }
};

LoggedIn loggedIn;

int s = 0;
int t = 0;
int c = 0;
int a = 0;
int p = 0;

Student STUDENTS_DATA[200]; 
Teacher TEACHERS_DATA[200];
Class CLASSES_DATA[200];
Assignment ASSIGNMENT_DATA[200];
Pengumpulan PENGUMPULAN_DATA[200];

int main() {

    while (1) {
        mainMenu();
        cout << "Data Kelas di CLASSES_DATA:" << endl;
        // for (Class& cls : CLASSES_DATA) {
        //     cls.display(); // Atau cetak data guru sesuai kebutuhan
        //     cout << endl;
        // }
        for (int i = 0; i < c; i++) {
            cout << "Nama kelas: " << CLASSES_DATA[i].name << " - " << CLASSES_DATA[i].id << endl;
            cout << "Oleh "<< CLASSES_DATA[i].teacher->username << endl;
        }
    }
    return 0;
}

void mainMenu() {

    int option;
    string in, passIn;
    string id, username, password, firstName, lastName, email;
    
    cout << ">>> Sistem Manajemen Siswa <<<" << endl;
    cout << "1. Login sebagai Guru" << endl;
    cout << "2. Login sebagai Siswa" << endl;
    cout << "3. Sign Up sebagai Guru" << endl;
    cout << "4. Sign Up sebagai Siswa" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih opsi:\n-> ";
    cin >> option;
    
    switch (option) {
    case 1: {
        cout << "Username/Email:\n-> ";
        cin >> in;
        cout << "Password:\n-> ";
        cin >> passIn;

        bool loginSuccess = false;
        for (int i = 0; i < t; i++) {
            if ((TEACHERS_DATA[i].username == in || TEACHERS_DATA[i].email == in) && TEACHERS_DATA[i].password == passIn) {
                loggedIn.update(true, TEACHERS_DATA[i].id, TEACHERS_DATA[i].username, &TEACHERS_DATA[i]);
                loggedIn.display();
                loginSuccess = true;                
                teacherMenu();
                break;
            }
        }
        if (!loginSuccess) {
            cout << "Username atau Password salah." << endl;
        }
        break;
    }
    case 2: {
        cout << "Username/Email:\n-> ";
        cin >> in;
        cout << "Password:\n-> ";
        cin >> passIn;

        bool loginSuccess = false;
        for (int i = 0; i < t; i++) {
            if ((STUDENTS_DATA[i].username == in || STUDENTS_DATA[i].email == in) && STUDENTS_DATA[i].password == passIn) {
                loggedIn.update(false, STUDENTS_DATA[i].id, STUDENTS_DATA[i].username, nullptr, &STUDENTS_DATA[i]);
                loggedIn.display();
                loginSuccess = true;
                studentMenu();
                break;
            } 
        }
        if (!loginSuccess) {
            cout << "Username atau Password salah." << endl;
        }        
        break;
    }
    case 3: {   
        cout << "Masukkan ID: ";
        cin >> id;
        cout << "Masukkan Username (tanpa spasi): ";
        cin >> username;
        cout << "Masukkan Password: ";
        cin >> password;
        cout << "Masukkan First Name: ";
        cin >> firstName;
        cout << "Masukkan Last Name: ";
        cin >> lastName;
        cout << "Masukkan Email: ";
        cin >> email;

        TEACHERS_DATA[t].id = id;
        TEACHERS_DATA[t].username = username;
        TEACHERS_DATA[t].password =  password;
        TEACHERS_DATA[t].firstName = firstName;
        TEACHERS_DATA[t].lastName = lastName;
        TEACHERS_DATA[t].email = email;
        t++;
        // saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");

        loggedIn.update(true, id, username, &TEACHERS_DATA[t-1]);
        loggedIn.display();

        cout << "TEACHERS_DATA SEKARANG: " << endl;

        for (int i = 0; i < t; i++) {
            TEACHERS_DATA[i].display();
            cout << endl;
        }
        
        teacherMenu();
        break; 
    }
    case 4: {   
        cout << "Masukkan ID: ";
        cin >> id;
        cout << "Masukkan Username (tanpa spasi): ";
        cin >> username;
        cout << "Masukkan Password: ";
        cin >> password;
        cout << "Masukkan First Name: ";
        cin >> firstName;
        cout << "Masukkan Last Name: ";
        cin >> lastName;
        cout << "Masukkan Email: ";
        cin >> email;
        cout << "Masukkan Kelas: " << endl;

        // Student newStudent(id, username, password, firstName, lastName, email);
        
        STUDENTS_DATA[s].id = id;
        STUDENTS_DATA[s].username = username;
        STUDENTS_DATA[s].password =  password;
        STUDENTS_DATA[s].firstName = firstName;
        STUDENTS_DATA[s].lastName = lastName;
        STUDENTS_DATA[s].email = email;
        s++;

        loggedIn.update(false, id, username, nullptr, &STUDENTS_DATA[s-1]);    
        loggedIn.display();

        studentMenu();
        break; 
    }
    default: {
        break;
    }
    }
    cout << endl;
}

void teacherMenu() {
    int option;
    bool isTeacher = true;

    cout << "--- MENU GURU ---" << endl;
    cout << "1. Melihat nilai dari kelas" << endl;
    cout << "2. Lihat queue tugas" << endl;
    cout << "3. Menambah tugas" << endl;
    cout << "4. Manajemen kelas" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih opsi:\n-> ";
    cin >> option;

    switch (option) {
    // case 1: {
    //     if ()
    //     break;
    // }
    case 3: {
        addAssignment();
        break;
    }
    case 4: {
        teacherClassMenu();
        teacherClassMenu();
        addAssignment();
        break;
    }
    default: {
        break;
    }
    }
}

void studentMenu() {
    int option;
    bool isTeacher = false;

    cout << "--- MENU SISWA ---" << endl;
    cout << "1. Melihat kelas" << endl;
    cout << "2. Keluar" << endl;
    cout << "Pilih opsi:\n-> ";
    cin >> option;
    
    switch (option) {
    case 1: {
        Student* foundStudent = loggedIn.studentPtr; // Inisialisasi dengan nullptr
        // for (Student& student : STUDENTS_DATA) {
        //     if (student.id == loggedIn.id || student.username == loggedIn.username) {
        //         foundStudent = &student; // Temukan siswa yang sesuai
        //         break;
        //     }
        // }  
        // for (int i = 0; i < s; i++) {
        //     if (STUDENTS_DATA[i].id == loggedIn.id || STUDENTS_DATA[i].username == loggedIn.username) {
        //         foundStudent = &STUDENTS_DATA[i]; // Temukan siswa yang sesuai
        //         break;
        //     }            
        // }
        
        if (foundStudent->classPtr != nullptr) {
            int opt;
            cout << "-- KELAS -- " << endl;
            cout << "Nama Kelas: " << foundStudent->classPtr->name << endl;
            cout << "ID: " << foundStudent->classPtr->id << endl;
            cout << "Guru: " << foundStudent->classPtr->teacher->username << endl << endl;

            cout << "1. Lihat tugas" << endl;
            cout << "2. Lihat akumulasi nilai anda" << endl;

            switch (opt) {
            case 1: {
                for (Assignment* ass : foundStudent->classPtr->assignments) {
                    ass->display();
                    ass->classPtr->name;
                    break;
                }
            }
            default:
                break;
            }
        } else {
            cout << "Anda belum memiliki kelas." << endl;
        }
        
        break;
    }
    default:
        break;
    }
}

// void seeAssignments() {

// }

void teacherClassMenu() {
    int option;
    string id, name, teacher;

    cout << "--- MANAJEMEN KELAS ---" << endl;
    cout << "1. Membuat kelas" << endl;
    cout << "2. Mengedit kelas" << endl;
    cout << "3. Menghapus kelas" << endl;
    cout << "4. Keluar" << endl;
    cout << "Pilih opsi:\n-> ";

    cin >> option;

    switch (option) {
    case 1: {
        cout << "Masukkan ID kelas: ";
        cin >> id;
        cout << "Masukkan Nama kelas: ";
        cin >> name;

        Teacher* foundTeacher = loggedIn.teacherPtr; // Inisialisasi dengan nullptr
        // for (Teacher& teacher : TEACHERS_DATA) {
        //     if (teacher.id == loggedIn.id || teacher.username == loggedIn.username) {
        //         foundTeacher = &teacher; // Temukan guru yang sesuai
        //         break;
        //     }
        // }

        if (foundTeacher) {
            // Class newClass(id, name); // Buat kelas dengan guru yang ditemukan
            CLASSES_DATA[c].id = id;
            CLASSES_DATA[c].name = name;
            CLASSES_DATA[c].setTeacher(foundTeacher);
            c++;
    
            foundTeacher->addClass(&CLASSES_DATA[c-1]);
            // for (size_t i = 0; i < 200; i++) {
            //     if (TEACHERS_DATA[i].id == loggedIn.id || TEACHERS_DATA[i].username == loggedIn.username) {
            //         TEACHERS_DATA[i].addClass(&CLASSES_DATA[c-1]);
            //         break;
            //     }
                
            // }
            cout << "Kelas berhasil dibuat." << endl;

            loggedIn.update(true, foundTeacher->id, foundTeacher->username, foundTeacher);
        } else {
            cout << "Error: Guru yang sedang login tidak ditemukan." << endl;
        }        
        
        break;
    }
    default: {
        break;
    }
    }
}

void addAssignment() {
    string id, description, dueDate, classId;

    Teacher* foundTeacher = loggedIn.teacherPtr; // Inisialisasi dengan nullptr
    // for (Teacher& teacher : TEACHERS_DATA) {
    //     if (teacher.id == loggedIn.id || teacher.username == loggedIn.username) {
    //         foundTeacher = &teacher; // Temukan guru yang sesuai
    //         break;
    //     }
    // }    

    if (!foundTeacher || foundTeacher->numClasses == 0) {
        cout << "Error: Anda tidak bisa membuat tugas karena Anda tidak memiliki kelas" << endl;
        return;
    }

    cout << "--- Buat Tugas ---" << endl;
    cout << "Masukkan ID Tugas: ";
    cin >> id;
    cout << "Masukkan Nama/Deskripsi Tugas:\n";
    getline(cin >> ws, description);
    cout << "Tanggal tenggat Tugas (format: dd-mm-yy): ";
    cin >> dueDate;
    cout << "Tugas ini untuk kelas mana? (Pilih nomor)\n-> " << endl; 

    for (int i = 0; i < foundTeacher->numClasses; ++i) {
        cout << i + 1 << ". " << foundTeacher->classes[i]->id << " - " << foundTeacher->classes[i]->name << endl;
    }
    
    int pilihanKelas;
    cin >> pilihanKelas;
    // Validasi input pilihan kelas
    if (pilihanKelas < 1 || pilihanKelas > foundTeacher->numClasses) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    Class* selectedClass = foundTeacher->classes[pilihanKelas - 1];

    // Assignment newAssignment(id, description, dueDate, selectedClass);
    ASSIGNMENT_DATA[a].id = id;
    ASSIGNMENT_DATA[a].description = description;
    ASSIGNMENT_DATA[a].dueDate = dueDate;
    ASSIGNMENT_DATA[a].classPtr = selectedClass;
    a++;
    
    // Tambahkan assignment ke vektor assignments pada selectedClass
    selectedClass->assignments.push_back(&ASSIGNMENT_DATA[a-1]); 

    cout << "Tugas berhasil ditambahkan oleh " << ASSIGNMENT_DATA[a-1].classPtr->teacher->username << endl;
    // saveClassesToCSV(CLASSES_DATA, "classes.csv");
}