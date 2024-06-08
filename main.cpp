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
// void loadTeachersFromCSV();

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

void loadTeachersFromCSV(const string& filename = "teachers.csv", bool hasHeader = true) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    string line;
    if (hasHeader) {
        getline(file, line); // Lewati baris header
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string id, username, password, firstName, lastName, email;
        getline(ss, id, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, email);

        TEACHERS_DATA.push_back(Teacher(id, username, password, firstName, lastName, email));
    }

    file.close();
}

void loadClassesFromCSV(const string& filename = "classes.csv", bool hasHeader = true) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    string line;
    if (hasHeader) {
        getline(file, line); 
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, teacherId;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, teacherId); // tidak ada koma di akhir baris
        
        Teacher* teacherPtr = nullptr;
        for (Teacher& teacher : TEACHERS_DATA) {
            if (teacher.id == teacherId) {
                teacherPtr = &teacher;
                break;
            }
        }

        Class newClass(id, name, teacherPtr);
        CLASSES_DATA.push_back(newClass);
        if (teacherPtr) {
            teacherPtr->addClass(&newClass); // Tambahkan kelas ke guru
        }

    }

    file.close();
}

void loadStudentsFromCSV(const string& filename = "students.csv", bool hasHeader = true) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    string line;
    if (hasHeader) {
        getline(file, line); // Lewati baris header
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string id, username, password, firstName, lastName, email, classId;
        getline(ss, id, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, email, ',');
        getline(ss, classId); // Baca ID kelas

        // Cari pointer ke objek Class berdasarkan classId
        Class* classPtr = nullptr;
        for (Class& cls : CLASSES_DATA) {
            if (cls.id == classId) {
                classPtr = &cls;
                break;
            }
        }

        STUDENTS_DATA.push_back(Student(id, username, password, firstName, lastName, email));
        if (classPtr) {
            classPtr->addStudent(&STUDENTS_DATA.back()); // Tambahkan siswa ke kelas
        }
    }

    file.close();
}

void loadAssignmentsFromCSV(const string& filename = "assignments.csv", bool hasHeader = true) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    string line;
    if (hasHeader) {
        getline(file, line); // Lewati baris header
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string id, description, dueDate, classId;
        getline(ss, id, ',');
        getline(ss, description, ',');
        getline(ss, dueDate, ',');
        getline(ss, classId); // tidak ada koma di akhir baris

        // Cari pointer ke objek Class berdasarkan classId (perlu diimplementasikan)
        Class* classPtr = nullptr;
        for (Class& cls : CLASSES_DATA) {
            if (cls.id == classId) {
                classPtr = &cls;
                break;
            }
        }

        ASSIGNMENT_DATA.push_back(Assignment(id, description, dueDate, classPtr));
    }

    file.close();
}

void buildRelationships() {
    // Hubungkan Student dengan Class
    for (Student& student : STUDENTS_DATA) {
        for (Class& cls : CLASSES_DATA) {
            if (cls.id == student.classPtr->id) {
                student.setClass(&cls);
                cls.addStudent(&student);
                break; // Asumsikan seorang siswa hanya bisa berada dalam satu kelas
            }
        }
    }

    // Hubungkan Class dengan Teacher
    for (Class& cls : CLASSES_DATA) {
        for (Teacher& teacher : TEACHERS_DATA) {
            if (teacher.id == cls.teacher->id) {
                cls.teacher = &teacher;
                teacher.addClass(&cls);
                break; // Asumsikan satu kelas hanya memiliki satu guru
            }
        }
    }

    // Hubungkan Assignment dengan Class
    for (Assignment& assignment : ASSIGNMENT_DATA) {
        for (Class& cls : CLASSES_DATA) {
                if (cls.id == assignment.classPtr->id) {
                assignment.classPtr = &cls;
                cls.assignments.push_back(&assignment);
                break;
            }
        }
    }
}

int main() {

    // loadTeachersFromCSV();
    // loadClassesFromCSV();
    // buildRelationships();

    while (1) {
    mainMenu();
    cout << "Data Kelas di CLASSES_DATA:" << endl;
    for (Class& cls : CLASSES_DATA) {
        cls.display(); // Atau cetak data guru sesuai kebutuhan
        cout << endl;
    }
    }
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

        Teacher newTeacher(id, username, password, firstName, lastName, email);
        
        TEACHERS_DATA.push_back(newTeacher);
        // TEACHERS_DATA[0].display();
        saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");

        loggedIn.update(true, id, username);
        loggedIn.display();

        cout << "TEACHERS_DATA SEKARANG" << endl;
        for (Teacher& t : TEACHERS_DATA) {
            t.display(); // Atau cetak data guru sesuai kebutuhan
            cout << endl;
        }
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
        cout << "CHECKPOINT1" << endl;
        if (foundTeacher) {
            Class newClass(id, name, foundTeacher); // Buat kelas dengan guru yang ditemukan
            CLASSES_DATA.push_back(newClass);
    
            foundTeacher->addClass(&CLASSES_DATA.back());
            saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");

            saveClassesToCSV(CLASSES_DATA, "classes.csv");
            cout << "Kelas berhasil dibuat." << endl;

            loggedIn.update(true, foundTeacher->id, foundTeacher->username);
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

    Assignment newAssignment(id, description, dueDate, selectedClass);
    ASSIGNMENT_DATA.push_back(newAssignment);

    // Tambahkan assignment ke vektor assignments pada selectedClass
    selectedClass->assignments.push_back(&ASSIGNMENT_DATA.back()); 

    saveAssignmentsToCSV(ASSIGNMENT_DATA, "assignments.csv");
    saveClassesToCSV(CLASSES_DATA, "classes.csv");
}