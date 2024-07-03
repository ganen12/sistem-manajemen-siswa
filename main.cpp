#include <iostream>
// #include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>

struct Message;
struct Student;
struct Class;
struct Teacher;
struct Assignment;
struct Pengumpulan;
struct Queue;
struct Stack;

#include "Student.h"
#include "Class.h"
#include "Teacher.h"
#include "Assignment.h"
#include "Pengumpulan.h"
#include "Forum.h"
#include "Nilai.h"
#include "Queue.cpp"
#include "Stack.cpp"
#include "InsertionSort.h"
#include "DisplayData.h"
#include "LoggedIn.h"
#include "SequentialSearch.h"

using namespace std;

void mainMenu();
void loginAsTeacher();
void loginAsStudent();
void teacherMenu();
void studentMenu();
void teacherClassMenu();
void seeStudentGrades();
void addAssignment();
void assignmentQueue();
void seeDiscussionForum(bool isTeacher);
void setNilaiToSubject(Student* foundStudent, Assignment* assignment, float nilai);
void seeClass();
void joinClass();
Class* chooseClass();
void removeClassFromTeacher(Teacher* foundTeacher, Class* classToRemove);
void removeClassFromClassesData(Class* classToRemove);
void removeClassFromStudents(Class* classToRemove);
void removeAssignmentsOfClass(Class* classToRemove);
void removePengumpulanOfClass(Class* classToRemove); 

void searchTeacherInfo(string search, string searchBy = "username");
void searchStudentInfo(string search, string searchBy = "username");

LoggedIn loggedIn;
Queue tugasQueue;
Stack historyStack;
const int MAX_DATA = 200;

int s = 0;
int t = 0;
int c = 0;
int a = 0;
int p = 0;

Student STUDENTS_DATA[MAX_DATA]; 
Teacher TEACHERS_DATA[MAX_DATA];
Class CLASSES_DATA[MAX_DATA];
Assignment ASSIGNMENT_DATA[MAX_DATA];
Pengumpulan PENGUMPULAN_DATA[MAX_DATA];

int main() {
    loggedIn.reset();
    mainMenu();
    return 0;
}

void mainMenu() {
    int option;
    
    do {
        cout << "\t# SISTEM MANAJEMEN SISWA #" << endl;
        cout << char(201) << string(40, char(205)) << char(187) << endl;
        cout << char(186) << " 1. Login sebagai Guru                  " << char(186) << endl;
        cout << char(186) << " 2. Login sebagai Siswa                 " << char(186) << endl;
        cout << char(186) << " 3. Keluar                              " << char(186) << endl;
        cout << char(200) << string(40, char(205)) << char(188) << endl << endl;
        cout << " Pilih opsi: " << endl;
        cout << " > "; cin >> option;
        cout << endl;
        system("CLS");

        switch (option) {
        case 1: {
            loginAsTeacher();
            break;
        }
        case 2: {
            loginAsStudent();
            break;
        }
        case 3: {
            break;
        }
        case 333: {
            system("CLEAR");
            cout << "TEACHERS_DATA: " << endl;
            displayTeachersData(TEACHERS_DATA, t, loggedIn, false, "alphabetical", true);      

            cout << endl;
            cout << "STUDENTS_DATA: " << endl;
            displayStudentsData(STUDENTS_DATA, s, loggedIn, false, "alphabetical", true);
            
            cout << endl;
            cout << "CLASSES_DATA: " << endl;
            displayClassesData(CLASSES_DATA, c, loggedIn, false, "alphabetical", true);
            break;      
        }
        default:
            cout << "Pilihan tidak tersedia." << endl << endl;
            break;
        }
    } while (option != 3);
}

void loginAsTeacher() {
    int option;
    string in, passIn;
    string id, username, password, firstName, lastName, email;
    
    do {
        cout << "\t> GURU < " << endl;
        cout << char(201) << string(40, char(205)) << char(187) << endl;
        cout << char(186) << " 1. Login                               " << char(186) << endl;
        cout << char(186) << " 2. Sign Up                             " << char(186) << endl;
        cout << char(186) << " 3. Kembali                             " << char(186) << endl;
        cout << char(200) << string(40, char(205)) << char(188) << endl << endl;
        cout << " Pilih opsi:                            " << endl;
        cout << " > "; cin >> option;
        cout << endl;
        system("CLS");

        switch (option) {
        case 1: {
            cout << "\t> LOGIN SEBAGAI GURU <" << endl << endl;
            cout << "Username/Email:\n> ";
            cin >> in;
            cout << "Password:\n> ";
            cin >> passIn;

            bool loginSuccess = false;
            for (int i = 0; i < t; i++) {
                if ((TEACHERS_DATA[i].username == in || TEACHERS_DATA[i].email == in) && TEACHERS_DATA[i].password == passIn) {
                    loggedIn.update(true, &TEACHERS_DATA[i]);
                    loggedIn.display();
                    loginSuccess = true;   
                    historyStack.push("(GURU) " + TEACHERS_DATA[i].fullName() + " berhasil login"); 

                    break;
                }
            }
            if (!loginSuccess) {
                cout << "\nUsername atau Password salah." << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
            system("CLS");
            teacherMenu();

            break;
        }
        case 2: {   
            cout << "\t> SIGN UP SEBAGAI GURU <" << endl << endl;
            cout << "Masukkan ID:\n> ";
            cin >> id;
            cout << "Masukkan Username (tanpa spasi):\n> ";
            cin >> username;
            cout << "Masukkan Password:\n> ";
            cin >> password;
            cout << "Masukkan First Name:\n> ";
            cin >> firstName;
            cout << "Masukkan Last Name:\n> ";
            cin >> lastName;
            cout << "Masukkan Email:\n> ";
            cin >> email;

            TEACHERS_DATA[t].initialize(id, username, password, firstName, lastName, email);

            // saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");
            loggedIn.update(true, &TEACHERS_DATA[t]);
            historyStack.push("(GURU) " + TEACHERS_DATA[t].fullName() + " berhasil sign up"); 

            t++;
            loggedIn.display();
            system("PAUSE");
            system("CLEAR");
            teacherMenu();
            break; 
        }
        case 3: {
            break;
        }
        default: {
            cout << "Pilihan tidak tersedia." << endl << endl;
            break;
        }
        }
    } while (option != 3);
}

void loginAsStudent() {
    int option;
    string in, passIn;
    string id, username, password, firstName, lastName, email;
    
    do {
        cout << "\t> SISWA < " << endl;
        cout << char(201) << string(40, char(205)) << char(187) << endl;
        cout << char(186) << " 1. Login                               " << char(186) << endl;
        cout << char(186) << " 2. Sign Up                             " << char(186) << endl;
        cout << char(186) << " 3. Kembali                             " << char(186) << endl;
        cout << char(200) << string(40, char(205)) << char(188) << endl << endl;
        cout << " Pilih opsi:                            " << endl;
        cout << " > "; cin >> option;
        cout << endl;
        system("CLS");

        switch (option) {
        case 1: {
            cout << "\t> LOGIN SEBAGAI SISWA <" << endl << endl;
            cout << "Username/Email:\n> ";
            cin >> in;
            cout << "Password:\n> ";
            cin >> passIn;

            bool loginSuccess = false;
            for (int i = 0; i < s; i++) {
                if ((STUDENTS_DATA[i].username == in || STUDENTS_DATA[i].email == in) && STUDENTS_DATA[i].password == passIn) {
                    loggedIn.update(false, nullptr, &STUDENTS_DATA[i]);
                    loggedIn.display();
                    loginSuccess = true;
                    historyStack.push("(SISWA) " + STUDENTS_DATA[i].fullName() + " berhasil login"); 

                    break;
                } 
            }
            if (!loginSuccess) {
                cout << "\nUsername atau Password salah." << endl;
                system("PAUSE");
                system("CLS");
                break;                
            }
            system("CLEAR");   
            studentMenu();  

            break;
        }
        case 2: {   
            cout << "\t> SIGN UP SEBAGAI SISWA <" << endl << endl;
            cout << "Masukkan ID:\n> ";
            cin >> id;
            cout << "Masukkan Username (tanpa spasi):\n> ";
            cin >> username;
            cout << "Masukkan Password:\n> ";
            cin >> password;
            cout << "Masukkan First Name:\n> ";
            cin >> firstName;
            cout << "Masukkan Last Name:\n> ";
            cin >> lastName;
            cout << "Masukkan Email:\n> ";
            cin >> email;
            
            Nilai* nilaiPtr =  new Nilai(8);
            STUDENTS_DATA[s].initialize(id, username, password, firstName, lastName, email, nilaiPtr); // TODO: ubah ID menjadi otomatis dan bukan inputan

            loggedIn.update(false, nullptr, &STUDENTS_DATA[s]);   
            historyStack.push("(SISWA) " + STUDENTS_DATA[s].fullName() + " berhasil sign up");  
            
            s++;        
            loggedIn.display();

            system("CLEAR");
            studentMenu();
            break; 
        }
        case 3: {
            break;
        }
        default: {
            cout << "Pilihan tidak tersedia." << endl << endl;
            break;
        }
        }
    } while (option != 3);
}

void teacherMenu() {
    int option;

    do {
        cout << endl;
        cout << char(218) << string(4, char(196)) << " MENU GURU " << string(20, char(196)) << char(191) << endl;
        cout << char(179) << " 1. Melihat nilai siswa dari kelas "  <<char(179) << endl;
        cout << char(179) << " 2. Lihat queue tugas              " <<char(179) << endl;
        cout << char(179) << " 3. Menambah tugas                 " <<char(179) << endl;
        cout << char(179) << " 4. Manajemen kelas                " <<char(179) << endl;
        cout << char(179) << " 5. Melihat history log            " <<char(179) << endl;
        cout << char(179) << " 6. Forum Diskusi                  " <<char(179) << endl;
        cout << char(179) << " 7. Keluar                         " <<char(179) << endl;
        cout << char(192) << string(35, char(196)) << char(217) << endl;
        cout << " Pilih opsi:\n > ";
        cin >> option;

        system("CLEAR");
        switch (option) {
        case 1: {
            seeStudentGrades(); 
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
            break;
        }
        case 5: {
            historyStack.printHistory(true);
            break;
        }
        case 6: {
            seeDiscussionForum(true);
            break;
        }
        case 7: {
            loggedIn.reset();
            historyStack.push("(GURU) " + TEACHERS_DATA[t].fullName() + " berhasil log out"); 
            break;
        }
        default: {
            cout << "Error: Pilihan tidak tersedia" << endl << endl;
            break;
        }
        }
    } while (option != 7);
}

void studentMenu() {
    int option;

    do {
        cout << endl;
        cout << char(218) << string(4, char(196)) << " MENU SISWA " << string(19, char(196)) << char(191) << endl;
        cout << char(179) << " 1. Melihat kelas                  " << char(179) <<endl;
        cout << char(179) << " 2. Join kelas                     " << char(179) <<endl;
        cout << char(179) << " 3. Melihat history log            " << char(179) <<endl;
        cout << char(179) << " 4. Forum Diskusi                  " << char(179) <<endl;
        cout << char(179) << " 5. Keluar                         " << char(179) <<endl;
        cout << char(192) << string(35, char(196)) << char(217) << endl;

        cout << " Pilih opsi:\n > ";
        cin >> option;
        
        system("CLEAR");
        switch (option) { 
        case 1: {
            seeClass();
            break;
        }
        case 2: {
            joinClass();
            break;  
        }
        case 3: {
            historyStack.printHistory(false);
            break;
        }
        case 4: {
            seeDiscussionForum(false);
            break;
        }
        case 5: {
            loggedIn.reset();
            historyStack.push("(SISWA) " + TEACHERS_DATA[t].fullName() + " berhasil log out"); 
            break;
        }
        default: {
            break;
        }
        }
    } while (option != 5);
}

void seeClass() {
    Student* foundStudent = loggedIn.studentPtr; // Inisialisasi dengan nullptr

    if (foundStudent->classPtr != nullptr || foundStudent->classPtr != NULL) {
        historyStack.push("(SISWA) " + foundStudent->fullName() + " melihat info kelas " + foundStudent->classPtr->name);
        int opt;
        do {
            cout << "+--- INFO KELAS ------------------+" << endl;
            cout << "> Nama Kelas : " << foundStudent->classPtr->name << endl << endl;
            cout << "> ID         : " << foundStudent->classPtr->id << endl << endl;
            cout << "> Guru       : " << foundStudent->classPtr->teacher->username << endl;
            cout << "+---------------------------------+" << endl << endl;

            cout << char(218) << string(4, char(196)) << " MENU KELAS " << string(19, char(196)) << char(191) << endl;
            cout << char(179) <<" 1. Lihat tugas                    " << char(179) <<endl;
            cout << char(179) <<" 2. Lihat akumulasi nilai anda     " << char(179) <<endl;
            cout << char(179) <<" 3. Kembali                        " << char(179) << endl;
            cout << char(192) << string(35, char(196)) << char(217)  << endl;
        
            cout << " Pilih opsi:\n > "; 
            cin >> opt;

            system("CLEAR");
            switch (opt) {
            case 1: {
                string inputId;

                if (foundStudent->classPtr->assignments.empty()) { // TODO: belum dilakukan pengetesan
                    cout << "Saat ini Anda tidak memiliki tugas" << endl << endl;
                    system("PAUSE");
                    break;            
                }
                
                for (int i = 0; i < foundStudent->classPtr->assignments.size(); i++) { // menampilkan semua tugas yang belum dikumpul
                    bool isFinished = false;
                    for (int j = 0; j < p; j++) {
                        if (PENGUMPULAN_DATA[j].studentId == foundStudent->id && PENGUMPULAN_DATA[j].tugasId == foundStudent->classPtr->assignments[i]->id) {
                            isFinished = true;
                            break; 
                        }           
                    }
                    if (!isFinished) {
                        cout << "Tugas " << i+1 << endl;
                        foundStudent->classPtr->assignments[i]->display();
                    }                
                }

                cout << "Tekan 0 untuk kembali" << endl;
                cout << "Masukkan ID tugas yang ingin dikumpulkan:\n-> ";  
                cin >> inputId; // TODO: input (mungkin) akan diubah menjadi pilihan nomor dari daftar tugas
                
                if (inputId == "0") break; // TODO: validasi input

                // Buat objek pengumpulan
                PENGUMPULAN_DATA[p].tugasId = inputId;
                PENGUMPULAN_DATA[p].studentId = foundStudent->id;
                PENGUMPULAN_DATA[p].studentName = foundStudent->firstName + " " + foundStudent->lastName;
                for (int i = 0; i < foundStudent->classPtr->assignments.size(); i++) {
                    if (foundStudent->classPtr->assignments[i]->id == inputId) {
                        PENGUMPULAN_DATA[p].subjectId = foundStudent->classPtr->assignments[i]->subjectId;
                        PENGUMPULAN_DATA[p].subject = foundStudent->classPtr->assignments[i]->subject;
                        PENGUMPULAN_DATA[p].description = foundStudent->classPtr->assignments[i]->id;
                        break;
                    }  
                }
                tugasQueue.enqueue(&PENGUMPULAN_DATA[p]);
                p++;

                cout << "Tugas berhasil dikumpulkan" << endl;   
                historyStack.push("(SISWA) " + foundStudent->fullName() + " berhasil mengumpulkan tugas " + inputId);
                break;
            }
            case 2: {
                
                cout << "Nilai akumulasi setiap mapel: " << endl << endl;
                cout << "  MAPEL              |   NILAI   " << endl;
                cout << "---------------------+-----------+" << endl;
                cout << "  Bahasa Indonesia   |  " << foundStudent->nilaiPtr->getNilai(BAHASA_INDONESIA) << endl;
                cout << "  Bahasa Inggris     |  " << foundStudent->nilaiPtr->getNilai(BAHASA_INGGRIS) << endl;
                cout << "  Matematika         |  " << foundStudent->nilaiPtr->getNilai(MATEMATIKA) << endl;
                cout << "  IPA                |  " << foundStudent->nilaiPtr->getNilai(IPA) << endl;
                cout << "  IPS                |  " << foundStudent->nilaiPtr->getNilai(IPS) << endl;
                cout << "  PKN                |  " << foundStudent->nilaiPtr->getNilai(PKN) << endl;
                cout << "  Seni Budaya        |  " << foundStudent->nilaiPtr->getNilai(SENI_BUDAYA) << endl;
                cout << "  Penjaskes          |  " << foundStudent->nilaiPtr->getNilai(PENJASKES) << endl;
                cout << "  Total Rata-Rata    |  " << foundStudent->nilaiPtr->getSumOfNilai() << endl << endl;
                system("PAUSE");
                break;
            }
            case 3: {
                break;
            }
            default: {
                cout << "Error: Pilihan tidak tersedia" << endl;
                break;
            }    
            }
        } while (opt != 3);
    } else {
        char opt;
        cout << "Anda belum memiliki kelas. Ikuti kelas? (y/n)\n> ";
        cin >> opt;
        if (opt == 'y' || opt == 'Y') {
            joinClass();
        }
    }
}

void joinClass() {
    system("CLEAR");
    string id;
    bool foundClass = false;

    if (c == 0) {
        cout << "Belum ada kelas yang tersedia." << endl;
        return;
    }

    if (loggedIn.studentPtr->classPtr != nullptr) {
        cout << "Anda sudah memiliki kelas." << endl;
        return;
    }
        
    cout << "Kelas yang tersedia:" << endl;    
    for (int i = 0; i < c; i++) {
        cout << "> ID: " << CLASSES_DATA[i].id << " -- Nama: " << CLASSES_DATA[i].name << endl;
    }
    cout << "\nMasukkan ID kelas:\n> ";
    cin >> id;

    for (int i = 0; i < c; i++) {
        if (CLASSES_DATA[i].id == id) {
            CLASSES_DATA[i].addStudent(loggedIn.studentPtr);
            loggedIn.studentPtr->setClass(&CLASSES_DATA[i]);
            foundClass = true;
            cout << "Berhasil mengikuti kelas " << CLASSES_DATA[i].name << endl;
            historyStack.push("(SISWA) " + loggedIn.studentPtr->fullName() + " berhasil join ke kelas " + CLASSES_DATA[i].name);
            break; 
        } 
    }

    if (!foundClass) {
        cout << "Kelas tidak ditemukan. ID yang Anda masukkan salah." << endl;
    }
    cout << endl;    
}

void seeStudentGrades() {
    int opt;
    Teacher* foundTeacher = loggedIn.teacherPtr;

    Class* selectedClass = chooseClass();
    if (selectedClass == nullptr || selectedClass == NULL) return;
    
    do {
        cout << endl;
        cout << char(218) << string(4, char(196)) << " LIHAT AKUMULASI NILAI SISWA " << string(13, char(196)) << char(191) << endl;
        cout << char(179) <<" 1. Tampilkan semua nilai siswa di kelas ini  " << char(179) << endl;
        cout << char(179) <<" 2. Cari nilai satu siswa di kelas            " << char(179) << endl;
        cout << char(192) << string(46, char(196)) << char(217) << endl;
       
        cout << " Pilih opsi:\n > ";
        cin >> opt; 

        switch (opt) {
        case 1: {
            displayStudentsData(STUDENTS_DATA, s, loggedIn, false, "alphabetical", false);
            historyStack.push("(GURU) " + foundTeacher->fullName() + " melihat semua nilai siswa di kelas " + selectedClass->name);

            break;
        }
        case 2: {
            string key;
            cout << "Masukkan ID atau nama lengkap siswa:\n> ";
            cin.ignore();
            getline(cin, key);

            Student* foundStudent = searchStudent(key, selectedClass);

            if (foundStudent) {
                cout << "Nama siswa: " << foundStudent->fullName() << endl;
                cout << "Nilai akumulasi setiap mapel: " << endl << endl;
                cout << "  MAPEL              |   NILAI   " << endl;
                cout << "---------------------+-----------+" << endl;
                cout << "  Bahasa Indonesia   |  " << foundStudent->nilaiPtr->getNilai(BAHASA_INDONESIA) << endl;
                cout << "  Bahasa Inggris     |  " << foundStudent->nilaiPtr->getNilai(BAHASA_INGGRIS) << endl;
                cout << "  Matematika         |  " << foundStudent->nilaiPtr->getNilai(MATEMATIKA) << endl;
                cout << "  IPA                |  " << foundStudent->nilaiPtr->getNilai(IPA) << endl;
                cout << "  IPS                |  " << foundStudent->nilaiPtr->getNilai(IPS) << endl;
                cout << "  PKN                |  " << foundStudent->nilaiPtr->getNilai(PKN) << endl;
                cout << "  Seni Budaya        |  " << foundStudent->nilaiPtr->getNilai(SENI_BUDAYA) << endl;
                cout << "  Penjaskes          |  " << foundStudent->nilaiPtr->getNilai(PENJASKES) << endl << endl;

                cout << "Total Rata-Rata      |  " << foundStudent->nilaiPtr->getSumOfNilai() << endl;
                system("PAUSE");
            } else {
                cout << "Siswa dengan ID atau nama " << key << " tidak ditemukan di kelas ini." << endl;
            }
            historyStack.push("(GURU) " + foundTeacher->fullName() + " melihat nilai dari siswa  " + foundStudent->fullName());
            break;
        }
        default: {
            break;
        }
        }
        return;
    } while (opt != 3);
}

void assignmentQueue() {
    int option;
    Teacher* foundTeacher = loggedIn.teacherPtr;

    do {
        cout << char(218) << string(4, char(196)) << " ANTRIAN TUGAS " << string(16, char(196)) << char(191) << endl;
        cout << char(179) <<" 1. Lihat queue tugas              " << char(179) <<endl;
        cout << char(179) <<" 2. Cek tugas dari queue terdepan  " << char(179) << endl;
        cout << char(179) <<" 3. Keluar                         " << char(179) << endl;
        cout << char(192) << string(35, char(196)) << char(217)  << endl;

        cout << " Pilih opsi:\n > ";
        cin >> option;

        system("CLEAR");
        switch (option) {
        case 1: { // Lihat antrian tugas
            tugasQueue.print(); // Tampilkan semua tugas di antrian
            historyStack.push("(GURU) " + foundTeacher->fullName() + " melihat queue tugas");

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
                        cout << "ID Tugas: " << assignment->id << endl;
                        cout << "Mapel: " << assignment->subject << endl;
                        cout << "Deskripsi: " << assignment->description << endl;
                        cout << "Kelas: " << assignment->classPtr->name << endl;
                        cout << "Dikumpulkan oleh: " << foundStudent->firstName << " " << foundStudent->lastName << " (" << foundStudent->id << ")" << endl;

                        float nilai;
                        
                        cout << "Masukkan nilai (1-100): ";
                        cin >> nilai;

                        while (nilai < 1 || nilai > 100) {
                            cout << "Nilai tidak valid. Harus antara 1-100. Masukkan lagi: ";
                            cin >> nilai;
                        }

                        try {
                            setNilaiToSubject(foundStudent, assignment, nilai); // Update nilai siswa

                            cout << "Nilai berhasil ditambahkan." << endl;
                            historyStack.push("(GURU) " + foundTeacher->fullName() + " berhasil menambahkan nilai ke siswa " + foundStudent->fullName());
                            tugasQueue.dequeue(); // Hapus tugas dari antrian setelah dinilai
                        } catch(const exception& e) {
                            cerr << e.what() << '\n';
                        }
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
    string id, name;
    Teacher* foundTeacher = loggedIn.teacherPtr; // foundTeacher adalah yang sedang login saat ini

    do {
        cout << "\n" << char(218) << string(4, char(196)) << " MANAJEMEN KELAS " << string(14, char(196)) << char(191) << endl;
        cout << char(179) << " 1. Membuat kelas                  " << char(179) <<endl;
        cout << char(179) << " 2. Mengedit kelas                 " << char(179) <<endl;
        cout << char(179) << " 3. Menghapus kelas                " << char(179) <<endl;
        cout << char(179) << " 4. Menghapus siswa dari kelas     " << char(179) <<endl;
        cout << char(179) << " 5. Melihat kelas yang Anda ajar   " << char(179) <<endl;
        cout << char(179) << " 6. Keluar                         " << char(179) << endl;
        cout << char(192) << string(35, char(196)) << char(217)  << endl;
        cout << " Pilih opsi:\n > ";

        cin >> option;

        system("CLEAR");
        switch (option) {
        case 1: {
            cout << " > MEMBUAT KELAS < " << endl;
            cout << "Masukkan ID kelas:\n> ";
            cin >> id; cin.ignore();
            cout << "Masukkan Nama kelas:\n> ";
            getline(cin, name);

            if (foundTeacher) {
                CLASSES_DATA[c].initialize(id, name);
                CLASSES_DATA[c].setTeacher(foundTeacher);
        
                foundTeacher->addClass(&CLASSES_DATA[c]);

                cout << "\nKelas berhasil dibuat." << endl;
                historyStack.push("(GURU) " + foundTeacher->fullName() + " berhasil membuat kelas: " + CLASSES_DATA[c].name);
                c++;

                loggedIn.update(true, foundTeacher);
            } else {
                cout << "Error: Guru yang sedang login tidak ditemukan." << endl;
            }        
            
            break;
        }
        case 2: {
            string newName, newId;
            cout << "> MENGEDIT KELAS <" << endl;
            Class* selectedClass = chooseClass();
            cin.ignore();

            if (selectedClass == nullptr || selectedClass == NULL) break;

            cout << "Masukkan nama kelas baru (tekan '0' untuk membatalkan):\n> "; 
            getline(cin, newName);
            if (newName != "0") {
                selectedClass->name = newName;
            }   

            cout << "Masukkan id kelas baru (tekan '0' untuk membatalkan):\n> ";
            cin >> newId;

            if (newId != "0") {
                selectedClass->id = newId;
            }

            if (newId != "0" && newName != "0") {
                cout << "\nKelas berhasil diedit." << endl;
                historyStack.push("(GURU) " + foundTeacher->fullName() + " berhasil mengedit kelas: " + selectedClass->name);
            }
            system("PAUSE");
            break;
        }
        case 3: {
            char choice;
            cout << "> MENGHAPUS KELAS <" << endl;
            Class* selectedClass = chooseClass();
            
            if (selectedClass == nullptr || selectedClass == NULL) break;

            cout << "\nYakin ingin menghapus kelas ini? (y/n):\n> "; cin >> choice;

            if (choice != 'y') break;
            try {
                removeClassFromTeacher(foundTeacher, selectedClass);
                removeClassFromClassesData(selectedClass);
                removeClassFromStudents(selectedClass);
                removeAssignmentsOfClass(selectedClass);
                removePengumpulanOfClass(selectedClass);

                cout << "Kelas berhasil dihapus." << endl;
                historyStack.push("(GURU) " + foundTeacher->fullName() + " berhasil menghapus kelas: " + selectedClass->name);
                system("PAUSE");
                break;
            }
            catch(const exception& e) {
                cerr << e.what() << '\n';
            }
        }
        case 4: {
            int pilihanSiswa;
            cout << "> MENGHAPUS SISWA DARI KELAS < " << endl;
            Class* selectedClass = chooseClass();
            if (selectedClass == nullptr || selectedClass == NULL) break;

            if (selectedClass->numStudents == 0) {
                cout << "Tidak ada siswa di kelas ini." << endl;
                break;
            }
            
            cout << "\nPilih siswa yang ingin dihapus dari kelas (pilih nomor): " << endl;
            for (int i = 0; i < selectedClass->numStudents; ++i) {
                cout << i + 1 << ". " << selectedClass->students[i]->firstName << " " << selectedClass->students[i]->lastName << " - " << selectedClass->students[i]->id << endl;
            }

            cout << "\n> "; cin >> pilihanSiswa;
            if (pilihanSiswa < 1 || pilihanSiswa > selectedClass->numStudents) {
                cout << "Pilihan tidak valid." << endl;
                break;
            }            

            Student* selectedStudent = selectedClass->students[pilihanSiswa - 1];
            selectedClass->removeStudent(selectedStudent);
            selectedStudent->removeClass(selectedClass);

            cout << "Siswa bernama" + selectedStudent->fullName() + " berhasil dihapus dari kelas ini." << endl;
            historyStack.push("(GURU) " + foundTeacher->fullName() + " berhasil menghapus siswa bernama " + selectedStudent->fullName() + " dari kelas " + selectedClass->name);
            system("PAUSE");
            break;
        }
        case 5: {
            displayClassesData(CLASSES_DATA, c, loggedIn, false, "alphabetical", false);
            break;
        }
        default: {
            break;
        }
        }
    } while (option != 6);
}

void addAssignment() {
    string id, description, dueDate, classId;
    int subjectNum;

    Teacher* foundTeacher = loggedIn.teacherPtr; // Inisialisasi dengan nullptr
    if (loggedIn.studentPtr) {
        cout << "Anda tidak berhak menambahkan tugas" << endl;
        return;
    }
    if (!foundTeacher || foundTeacher->numClasses == 0) {
        cout << "Error: Anda tidak bisa membuat tugas karena Anda tidak memiliki kelas" << endl;
        return;
    }

    cout << "> MEMBUAT TUGAS <" << endl;
    cout << "Masukkan ID Tugas:\n> ";
    cin >> id;
    cout << "Masukkan Mata Pelajaran:" << endl;
    cout << "1. Bahasa Indonesia\n2. Bahasa Inggris\n3. Matematika\n4. IPA\n5. IPS\n6. PKN\n7. Seni Budaya\n8. Penjaskes" << endl;
    cout << "Pilih nomor:\n> ";
    cin >> subjectNum;
    if (subjectNum == 0 || subjectNum > 8) {
        cout << "Pilihan mata pelajaran tidak valid." << endl;
        return;
    }
    cout << "Masukkan Nama/Deskripsi Tugas:\n> ";
    getline(cin >> ws, description);
    cout << "Tanggal tenggat Tugas (format: dd-mm-yy):\n> ";
    cin >> dueDate;

    Class* selectedClass = chooseClass();

    if (selectedClass == nullptr || selectedClass == NULL) return;

    ASSIGNMENT_DATA[a].initialize(id, subjectNum, description, dueDate);
    ASSIGNMENT_DATA[a].setSubject();
    ASSIGNMENT_DATA[a].setClass(selectedClass);
    
    // Tambahkan assignment ke vektor assignments pada selectedClass
    selectedClass->assignments.push_back(&ASSIGNMENT_DATA[a]); 
    // selectedClass->addAssignment(&ASSIGNMENT_DATA[a]);
    cout << "Tugas berhasil ditambahkan oleh " << ASSIGNMENT_DATA[a].classPtr->teacher->username << endl;
    historyStack.push("(GURU) " + foundTeacher->fullName() + " berhasil menambahkan tugas " + ASSIGNMENT_DATA[a].id + "ke kelas: " + selectedClass->name);
    a++;    
    // saveClassesToCSV(CLASSES_DATA, "classes.csv");
}

Class* chooseClass() {
    Teacher* foundTeacher = loggedIn.teacherPtr;
    if (!foundTeacher || foundTeacher->numClasses == 0) {
        cout << "Error: Anda tidak memiliki kelas." << endl;
        return nullptr;
    }

    cout << "Pilih untuk kelas yang mana: " << endl;
    for (int i = 0; i < foundTeacher->numClasses; ++i) {
        cout << i + 1 << ". " << foundTeacher->classes[i]->id << " - " << foundTeacher->classes[i]->name << endl;
    }

    int pilihanKelas;
    cout << "\n> "; cin >> pilihanKelas;

    if (pilihanKelas < 1 || pilihanKelas > foundTeacher->numClasses) {
        cout << "Pilihan tidak valid." << endl;
        return nullptr;
    }

    return foundTeacher->classes[pilihanKelas - 1];
}

void removeClassFromTeacher(Teacher* foundTeacher, Class* classToRemove) {
    classToRemove->deleteForum();
    foundTeacher->removeClass(classToRemove); // Panggil metode removeClass pada objek teacherPtr   
}

void removeClassFromClassesData(Class* classToRemove) {
    for (int i = 0; i < c; ++i) {
        if (CLASSES_DATA[i].id == classToRemove->id) {
            // Geser elemen-elemen setelah kelas yang dihapus ke depan
            for (int j = i; j < c - 1; ++j) {
                CLASSES_DATA[j] = CLASSES_DATA[j + 1];
            }
            c--; // Kurangi jumlah kelas
            break;
        }
    }
}

void removeClassFromStudents(Class* classToRemove) {
    for (Student& student : STUDENTS_DATA) {
        if (student.classPtr == classToRemove) {
            student.removeClass(classToRemove);
        }
    }    
}

void removeAssignmentsOfClass(Class* classToRemove) {
    for (int i = 0; i < a; ++i) {
        if (ASSIGNMENT_DATA[i].classPtr == classToRemove) {
            // Hapus tugas dari array ASSIGNMENT_DATA (geser elemen)
            for (int j = i; j < a - 1; ++j) {
                ASSIGNMENT_DATA[j] = ASSIGNMENT_DATA[j + 1];
            }
            a--;
            i--; // Perbaiki indeks setelah penghapusan
        }
    }
}

void removePengumpulanOfClass(Class* classToRemove) {
    for (int i = 0; i < p; ++i) {
        // Cari tugas berdasarkan tugasId
        Assignment* foundAssignment = nullptr;
        for (int j = 0; j < a; j++) {
            if (ASSIGNMENT_DATA[j].id == PENGUMPULAN_DATA[i].tugasId) {
                foundAssignment = &ASSIGNMENT_DATA[j];
                break;
            }
        }

        // Jika tugas ditemukan dan kelasnya sesuai dengan classToRemove
        if (foundAssignment && foundAssignment->classPtr == classToRemove) { 
            for (int j = i; j < p - 1; ++j) {
                PENGUMPULAN_DATA[j] = PENGUMPULAN_DATA[j + 1]; // geser elemen
            }
            p--;
            i--; // Perbaiki indeks setelah penghapusan
        }
    }
}

void seeDiscussionForum(bool isTeacher) {
    system("CLEAR");
    string messageContent;
    if (isTeacher) {
        Teacher* foundTeacher = loggedIn.teacherPtr;
        Class* selectedClass = chooseClass();
        if (selectedClass == nullptr || selectedClass == NULL) return;

        do {
            system("CLEAR");
            cout << "\t> FORUM DISKUSI KELAS " << selectedClass->name << " <" << endl<< endl;
            if (selectedClass->discussionForum.empty()) {
                cout << "Forum kosong." << endl;
            }

            for (int i = 0; i < selectedClass->discussionForum.size(); ++i) {
                selectedClass->discussionForum[i].display();
            }

            cout << "\nKirim pesan:\t\t\tKetik '.exit' untuk keluar\n> ";
            getline(cin >> ws, messageContent);

            if (messageContent != ".exit") {
                Message newChat;
                newChat.setMessage(nullptr, foundTeacher, messageContent);
                selectedClass->addMessage(&newChat);
            }

        } while (messageContent != ".exit");
    } else {
        Student* foundStudent = loggedIn.studentPtr; 
        if (foundStudent->classPtr == nullptr || foundStudent->classPtr == NULL) {
            cout << "Anda belum memiliki kelas." << endl;
            return;
        }
        do {
            system("CLEAR");
            cout << "\t== FORUM DISKUSI KELAS " << foundStudent->classPtr->name << " ==" << endl<< endl;

            if (foundStudent->classPtr->discussionForum.empty()) {
                cout << "Forum kosong." << endl;
            }
            for (int i = 0; i < foundStudent->classPtr->discussionForum.size(); ++i) {
                foundStudent->classPtr->discussionForum[i].display();
            }

            cout << "\nKirim pesan:\t\t\tKetik '.exit' untuk keluar\n> ";
            getline(cin >> ws, messageContent);
            
            if (messageContent != ".exit") {
                Message newChat;
                newChat.setMessage(foundStudent, nullptr, messageContent);
                foundStudent->classPtr->addMessage(&newChat);    
            }        
        } while (messageContent != ".exit");
    }
}

void setNilaiToSubject(Student* foundStudent, Assignment* assignment, float nilai) {

    switch (assignment->subjectId) {
    case 0: {
        foundStudent->nilaiPtr->setNilai(BAHASA_INDONESIA, nilai);
        break;
    }
    case 1: {
        foundStudent->nilaiPtr->setNilai(BAHASA_INGGRIS, nilai);
        break;
    }
    case 2: {
        foundStudent->nilaiPtr->setNilai(MATEMATIKA, nilai);
        break;
    }
    case 3: {
        foundStudent->nilaiPtr->setNilai(IPA, nilai);
        break;
    }
    case 4: {
        foundStudent->nilaiPtr->setNilai(IPS, nilai);
        break;
    }
    case 5: {
        foundStudent->nilaiPtr->setNilai(PKN, nilai);
        break;
    }
    case 6: {
        foundStudent->nilaiPtr->setNilai(SENI_BUDAYA, nilai);
        break;
    }
    case 7: {
        foundStudent->nilaiPtr->setNilai(PENJASKES, nilai);
        break;
    }
    default:
        break;
    }
}