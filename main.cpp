#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>
// #include <queue>
// #include <stack>

struct Student;
struct Teacher;
struct Class;
struct Assignment;
struct Pengumpulan;

#include "Student.h"
#include "Teacher.h"
#include "Class.h"
#include "Assignment.h"
#include "Pengumpulan.h"

#include "save_csv_utils.cpp"

using namespace std;

const int MAX_STUDENTS_IN_CLASS = 30;

void teacherMenu();
void teacherClassMenu();
void mainMenu();
void addAssignment();
void assignmentQueue();


struct LoggedIn {
    bool isTeacher;
    string id;
    string username;
    string classId;

    LoggedIn(bool isTeacher = false, string id = "", string username = "") 
        : isTeacher(isTeacher), id(id), username(username) {}

    void update(bool isTeacher, string id, string username) {
        this->isTeacher = isTeacher;
        this->id = id;
        this->username = username;
    }

    void setClass() {
        this->classId = id;
    }
    

    void display() {
        cout << "Currently logged in:" << endl;
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

// menyimpan semua data dari file-file csv pada saat program dijalankan
vector<Student> STUDENTS_DATA; 
vector<Teacher> TEACHERS_DATA;
vector<Class> CLASSES_DATA;
vector<Assignment> ASSIGNMENT_DATA;
vector<Pengumpulan> PENGUMPULAN_DATA;

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int option;
    string id, username, password, firstName, lastName, email;
    bool isTeacher = false;
    
    cout << "Sistem Manajemen Siswa" << endl;
    cout << "1. Login sebagai Guru" << endl;
    cout << "2. Login sebagai Siswa" << endl;
    cout << "3. Sign Up sebagai Guru" << endl;
    cout << "4. Sign Up sebagai Siswa" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih opsi:\n-> ";
    cin >> option;

    switch (option) {
    case 1: {
        isTeacher = true;
        cout << "Username:\n-> ";
        cin >> username;
        cout << "Password:\n-> ";
        cin >> password;
        break;
    }
    case 2: {
        break;
    }
    case 3: {   
        cout << "Masukkan ID: ";
        cin >> id;
        cout << "Masukkan Username: ";
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

        Teacher newTeacher(id, username, password, firstName, lastName, email);
        
        TEACHERS_DATA.push_back(newTeacher);
        // TEACHERS_DATA[0].display();
        saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");

        loggedIn.update(true, TEACHERS_DATA.back().id, TEACHERS_DATA.back().username);
        loggedIn.display();

        teacherMenu();
        break; 
    }
    case 4: {   
        cout << "Masukkan ID: ";
        cin >> id;
        cout << "Masukkan Username: ";
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

        Student newStudent(id, username, password, firstName, lastName, email);
        
        STUDENTS_DATA.push_back(newStudent);
        saveStudentsToCSV(STUDENTS_DATA, "students.csv");

        loggedIn.update(false, STUDENTS_DATA.back().id, STUDENTS_DATA.back().username);    
        // loggedin.display();

        break; 
    }
    default: {
        break;
    }
    }
}

void teacherMenu() {
    int option;
    bool isTeacher = true;

    cout << "--- MENU GURU ---" << endl;
    // cout << "1. Membuatkan akun siswa" << endl;
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
        break;
    }
    default: {
        break;
    }
    }
}

void teacherClassMenu() {
    int option;
    string id, name, teacher;

    cout << "--- MANAJEMEN KELAS ---" << endl;
    // cout << "1. Membuatkan akun siswa" << endl;
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

        Teacher* foundTeacher = nullptr; // Inisialisasi dengan nullptr
        for (Teacher& teacher : TEACHERS_DATA) {
            if (teacher.id == loggedIn.id || teacher.username == loggedIn.username) {
                foundTeacher = &teacher; // Temukan guru yang sesuai
                break;
            }
        }

        if (foundTeacher) {
            Class newClass(id, name, foundTeacher); // Buat kelas dengan guru yang ditemukan
            CLASSES_DATA.push_back(newClass);

            foundTeacher->classes.push_back(&CLASSES_DATA.back());
            saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");

            saveClassesToCSV(CLASSES_DATA, "classes.csv");
            cout << "Kelas berhasil dibuat." << endl;
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

    Teacher* foundTeacher = nullptr; // Inisialisasi dengan nullptr
    for (Teacher& teacher : TEACHERS_DATA) {
        if (teacher.id == loggedIn.id || teacher.username == loggedIn.username) {
            foundTeacher = &teacher; // Temukan guru yang sesuai
            break;
        }
    }    

    if (!foundTeacher || foundTeacher->classes.size() == 0) {
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

    for (size_t i = 0; i < foundTeacher->classes.size(); ++i) {
        cout << i + 1 << ". " << foundTeacher->classes[i]->id << " - " << foundTeacher->classes[i]->name << endl;
    }
    
    int pilihanKelas;
    cin >> pilihanKelas;

    // Validasi input pilihan kelas
    if (pilihanKelas < 1 || pilihanKelas > foundTeacher->classes.size()) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    Class* selectedClass = foundTeacher->classes[pilihanKelas - 1];

    Assignment newAssignment(id, description, dueDate, selectedClass);
    ASSIGNMENT_DATA.push_back(newAssignment);

    saveAssignmentsToCSV(ASSIGNMENT_DATA, "assignments.csv");
}