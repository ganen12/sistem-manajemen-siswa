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
struct Queue;

#include "Student.h"
#include "Class.h"
#include "Teacher.h"
#include "Assignment.h"
#include "Pengumpulan.h"
#include "Queue.cpp"

using namespace std;

void teacherMenu();
void studentMenu();
void teacherClassMenu();
void mainMenu();
void addAssignment();
void assignmentQueue();
void seeClass();
void joinClass();

// TODO
void displayTeachersData(bool sort = false, string sortBy = "alphabetical"); // display teachers_data dengan algoritma sorting
void displayStudentsData(bool sort = false, string sortBy = "alphabetical"); // display students_data dari kelas yang diajar guru yang sedang login
void displayClassesData(bool sort = false, string sortBy = "alphabetical"); // display kelas
void displayAssignmentsData(bool sort = false, string sortBy = "alphabetical"); // display assignment dari kelas tertentu

void searchTeacherInfo(string search, string searchBy = "username");
void searchStudentInfo(string search, string searchBy = "username");

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
Queue tugasQueue;

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
        loggedIn.update(false, "", "", nullptr, nullptr);
        mainMenu();
        // cout << "Data Kelas di CLASSES_DATA:" << endl;

        // for (int i = 0; i < c; i++) {
        //     cout << "Nama kelas: " << CLASSES_DATA[i].name << " - " << CLASSES_DATA[i].id << endl;
        //     cout << "Oleh "<< CLASSES_DATA[i].teacher->username << endl;
        //     cout << "Jumlah siswa: " << CLASSES_DATA[i].numStudents << endl;
        //     cout << "Assignments: " << CLASSES_DATA[i].assignments.size() << endl;
        // }
        // cout << endl;
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

        // saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");
        loggedIn.update(true, id, username, &TEACHERS_DATA[t]);
        t++;
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

        STUDENTS_DATA[s].id = id; // TODO: ubah ID menjadi otomatis dan bukan inputan
        STUDENTS_DATA[s].username = username;
        STUDENTS_DATA[s].password =  password;
        STUDENTS_DATA[s].firstName = firstName;
        STUDENTS_DATA[s].lastName = lastName;
        STUDENTS_DATA[s].email = email;

        loggedIn.update(false, id, username, nullptr, &STUDENTS_DATA[s]);    
        s++;        
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
    cout << "1. Melihat nilai siswa dari kelas" << endl;
    cout << "2. Lihat queue tugas" << endl;
    cout << "3. Menambah tugas" << endl;
    cout << "4. Manajemen kelas" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih opsi:\n-> ";
    cin >> option;

    switch (option) {
    case 1: {
        int opt;
        Teacher* foundTeacher = loggedIn.teacherPtr;

        cout << "Pilih kelas yang mana: " << endl;
        if (!foundTeacher || foundTeacher->numClasses == 0) {
            cout << "Error: Anda tidak bisa membuat tugas karena Anda tidak memiliki kelas" << endl;
            break;
        }

        for (int i = 0; i < foundTeacher->numClasses; ++i) {
            cout << i + 1 << ". " << foundTeacher->classes[i]->id << " - " << foundTeacher->classes[i]->name << endl;
        }
        
        int pilihanKelas;
        cout << "-> "; cin >> pilihanKelas;
        // Validasi input pilihan kelas
        if (pilihanKelas < 1 || pilihanKelas > foundTeacher->numClasses) {
            cout << "Pilihan tidak valid." << endl;
            return;
        }
        Class* selectedClass = foundTeacher->classes[pilihanKelas - 1];

        cout << "1. Tampilkan semua nilai siswa di kelas " << selectedClass->name << endl;
        cout << "2. Cari nilai satu siswa di kelas " << selectedClass->name << endl;
        cout << "Pilih opsi:\n-> " << endl;
        cin >> opt; 

        switch (opt) {
        case 1: {
            // TODO
            break;
        }
        case 2: {
            // TODO
            break;
        }
        default: {
            break;
        }
        }
        break;
    }
    case 2: {
        assignmentQueue();
        break;
    }
    case 3: {
        addAssignment();
        break;
    }
    case 4: {
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
    cout << "2. Join kelas" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih opsi:\n-> ";
    cin >> option;
    
    switch (option) {
    case 1: {
        seeClass();
        break;
    }
    case 2: {
        joinClass();
        break;  
    }
    default:
        break;
    }
}

void seeClass() {
    Student* foundStudent = loggedIn.studentPtr; // Inisialisasi dengan nullptr

    if (foundStudent->classPtr != nullptr) {
        int opt;
        cout << "-- INFO KELAS -- " << endl;
        cout << "Nama Kelas: " << foundStudent->classPtr->name << endl;
        cout << "ID: " << foundStudent->classPtr->id << endl;
        cout << "Guru: " << foundStudent->classPtr->teacher->username << endl << endl;

        cout << "1. Lihat tugas" << endl;
        cout << "2. Lihat akumulasi nilai anda" << endl;
        cout << "Pilih opsi: "; cin >> opt;

        switch (opt) {
        case 1: {
            string inputId;
   
            if (foundStudent->classPtr->assignments.empty()) { // TODO
                cout << "Saat ini Anda tidak memiliki tugas" << endl;
                break;            
            }
            
            for (int i = 0; i < foundStudent->classPtr->assignments.size(); i++) { // menampilkan semua tugas yang belum dikumpul
                bool isCollected = false;
                for (int j = 0; j < p; j++) {
                    if (PENGUMPULAN_DATA[j].studentId == foundStudent->id && PENGUMPULAN_DATA[j].tugasId == foundStudent->classPtr->assignments[i]->id) {
                        isCollected = true;
                        break; 
                    }           
                }
                if (!isCollected) {
                    cout << "Tugas " << i+1 << endl;
                    foundStudent->classPtr->assignments[i]->display();
                }                
            }

            cout << "Tekan 0 untuk kembali" << endl;
            cout << "Masukkan ID Tugas yang ingin dikumpulkan:\n-> "; // TODO: masukan tugas yang baru dikumpulkan ke queue tugas 
            cin >> inputId;
            
            if (inputId == "0") break; // TODO: validasi input

            // Buat objek pengumpulan
            PENGUMPULAN_DATA[p].tugasId = inputId;
            PENGUMPULAN_DATA[p].studentId = foundStudent->id;
            PENGUMPULAN_DATA[p].studentName = foundStudent->firstName + " " + foundStudent->lastName;
            for (int i = 0; i < foundStudent->classPtr->assignments.size(); i++) {
                if (foundStudent->classPtr->assignments[i]->id == inputId) {
                    PENGUMPULAN_DATA[p].description = foundStudent->classPtr->assignments[i]->id;
                    break;
                }  
            }
            tugasQueue.enqueue(&PENGUMPULAN_DATA[p]);
            p++;

            cout << "Tugas berhasil dikumpulkan" << endl;    
        }
        default: {
            break;
        }    
        }
    } else {
        char opt;
        cout << "Anda belum memiliki kelas. Ikuti kelas? (y/n)" << endl;
        cin >> opt;
        if (opt == 'y' || opt == 'Y') {
            joinClass();
        }
    }
}

void joinClass() {
    string id;
    bool foundClass = false;

    cout << "Kelas yang tersedia:" << endl;
    for (int i = 0; i < c; i++) {
        cout << "Id: " << CLASSES_DATA[i].id << " - Nama: " << CLASSES_DATA[i].name << endl;
    }
    cout << "Masukkan ID kelas: ";
    cin >> id;

    for (int i = 0; i < c; i++) {
        if (CLASSES_DATA[i].id == id) {
            CLASSES_DATA[i].addStudent(loggedIn.studentPtr);
            loggedIn.studentPtr->addClass(&CLASSES_DATA[i]);
            foundClass = true;
            cout << "Berhasil mengikuti kelas " << CLASSES_DATA[i].name << endl;
            break;
        } 
    }

    if (!foundClass) {
        cout << "Kelas tidak ditemukan. ID yang Anda masukkan salah." << endl;
    }    
}

void assignmentQueue() {
    int option;

    do {
        cout << "\n--- Queue Tugas ---" << endl;
        cout << "1. Lihat queue tugas" << endl;
        cout << "2. Periksa tugas dari queue terdepan" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih opsi:\n-> ";
        cin >> option;

        switch (option) {
        case 1: { // Lihat antrian tugas
            tugasQueue.print(); // Tampilkan semua tugas di antrian
            break;
        }
        case 2: { // Periksa tugas dari antrian depan
            if (!tugasQueue.isEmpty()) {
                Pengumpulan* pengumpulan = tugasQueue.peek(); // Ambil tugas di depan antrian

                // Cari tugas berdasarkan tugasId
                Assignment* assignment = nullptr;
                for (int i = 0; i < a; i++) {
                    if (ASSIGNMENT_DATA[i].id == pengumpulan->tugasId) {
                        assignment = &ASSIGNMENT_DATA[i];
                        break;
                    }
                }

                // Cari siswa berdasarkan studentId
                Student* foundStudent = nullptr;
                for (int i = 0; i < s; i++) {
                    if (STUDENTS_DATA[i].id == pengumpulan->studentId) {
                        foundStudent = &STUDENTS_DATA[i];
                        break;
                    }
                }

                if (assignment && foundStudent) {
                    // Pastikan guru yang login adalah guru yang mengajar kelas tugas tersebut
                    if (assignment->classPtr->teacher == loggedIn.teacherPtr) {
                        cout << "\n--------------------" << endl;
                        cout << "Tugas: " << assignment->description << endl;
                        cout << "Kelas: " << assignment->classPtr->name << endl;
                        cout << "Dikumpulkan oleh: " << foundStudent->firstName << " " << foundStudent->lastName << " (" << foundStudent->id << ")" << endl;

                        int nilai;
                        cout << "Masukkan nilai (1-100): ";
                        cin >> nilai;

                        while (nilai < 1 || nilai > 100) {
                            cout << "Nilai tidak valid. Harus antara 1-100. Masukkan lagi: ";
                            cin >> nilai;
                        }

                        // Update nilai siswa
                        foundStudent->Ipk += nilai;

                        cout << "Nilai berhasil ditambahkan." << endl;
                        tugasQueue.dequeue(); // Hapus tugas dari antrian setelah dinilai
                    }
                } else {
                    cout << "Tugas atau siswa tidak ditemukan." << endl;
                }
            } else {
                cout << "Antrian tugas kosong." << endl;
            }
            break;
        }
        case 3: { // Keluar
            break; // Keluar dari switch-case
        }
        default: {
            cout << "Pilihan tidak valid." << endl;
            break;
        }
        }
    } while (option != 3); // Lanjutkan selama guru tidak memilih keluar
}

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

        Teacher* foundTeacher = loggedIn.teacherPtr; // foundTeacher adalah yang sedang login saat ini

        if (foundTeacher) {
            // Class newClass(id, name); // Buat kelas dengan guru yang ditemukan
            CLASSES_DATA[c].id = id;
            CLASSES_DATA[c].name = name;
            CLASSES_DATA[c].setTeacher(foundTeacher);
    
            foundTeacher->addClass(&CLASSES_DATA[c]);
            c++;
            
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
    if (loggedIn.studentPtr) {
        cout << "Anda tidak berhak menambahkan tugas" << endl;
        return;
    }
    if (!foundTeacher || foundTeacher->numClasses == 0) {
        cout << "Error: Anda tidak bisa membuat tugas karena Anda tidak memiliki kelas" << endl;
        return;
    }

    cout << "--- Buat Tugas ---" << endl;
    cout << "Masukkan ID Tugas: ";
    cin >> id;
    cout << "Masukkan Nama/Deskripsi Tugas (format: <pelajaran> - <deskripsi>):\n";
    getline(cin >> ws, description);
    cout << "Tanggal tenggat Tugas (format: dd-mm-yy): ";
    cin >> dueDate;
    cout << "Tugas ini untuk kelas mana? (Pilih nomor): " << endl; 

    for (int i = 0; i < foundTeacher->numClasses; ++i) {
        cout << i + 1 << ". " << foundTeacher->classes[i]->id << " - " << foundTeacher->classes[i]->name << endl;
    }
    
    int pilihanKelas;
    cout << "\n-> ";cin >> pilihanKelas;
    // Validasi input pilihan kelas
    if (pilihanKelas < 1 || pilihanKelas > foundTeacher->numClasses) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    Class* selectedClass = foundTeacher->classes[pilihanKelas - 1];

    ASSIGNMENT_DATA[a].id = id;
    ASSIGNMENT_DATA[a].description = description;
    ASSIGNMENT_DATA[a].dueDate = dueDate;
    ASSIGNMENT_DATA[a].classPtr = selectedClass;
    
    // Tambahkan assignment ke vektor assignments pada selectedClass
    selectedClass->assignments.push_back(&ASSIGNMENT_DATA[a]); 
    cout << "Tugas berhasil ditambahkan oleh " << ASSIGNMENT_DATA[a].classPtr->teacher->username << endl;

    a++;    
    // saveClassesToCSV(CLASSES_DATA, "classes.csv");
}