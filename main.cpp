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
#include "InsertionSort.h"
#include "DisplayData.h"
#include "SequentialSearch.h"

using namespace std;

void teacherMenu();
void studentMenu();
void teacherClassMenu();
void mainMenu();
void seeStudentGrades();
void addAssignment();
void assignmentQueue();
void seeClass();
void joinClass();

// TODO
void displayTeachersData(bool sort, string sortBy, bool showAll); // display teachers_data dengan algoritma sorting
void displayStudentsData(bool sort, string sortBy, bool showAll); // display students_data dari kelas yang diajar guru yang sedang login
void displayClassesData(bool sort, string sortBy, bool showAll); // display kelas
void displayAssignmentsData(bool sort, string sortBy, bool showAll); // display assignment dari kelas tertentu

void searchTeacherInfo(string search, string searchBy = "username");
void searchStudentInfo(string search, string searchBy = "username");

struct LoggedIn {
    bool isTeacher;
    Teacher* teacherPtr;
    Student* studentPtr;

    LoggedIn(bool isTeacher = false, Teacher* teacherPtr = nullptr, Student* studentPtr = nullptr) 
        : isTeacher(isTeacher), teacherPtr(teacherPtr), studentPtr(studentPtr) {}

    void update(bool isTeacher, Teacher* teacher = nullptr, Student* student = nullptr) {
        this->isTeacher = isTeacher;
        this->teacherPtr = teacher;
        this->studentPtr = student;
    }
    
    void display() {
        cout << "Saat ini logged in:" << endl;
        cout << "\t" << (isTeacher ? "Guru" : "Siswa") << endl;

        if (isTeacher) {
            cout << "\tID: " << teacherPtr->id << endl;
            cout << "\tUSERNAME: " << teacherPtr->username << endl;
        } else if (!isTeacher) {
            cout << "\tID: " << studentPtr->id << endl;
            cout << "\tUSERNAME: " << studentPtr->username << endl;
        } else {
            cout << "\tInformasi pengguna tidak ditemukan." << endl;
        }
    }

    void reset() {
        this->isTeacher = false;
        this->teacherPtr = nullptr;
        this->studentPtr = nullptr;
    }
};

LoggedIn loggedIn;
Queue tugasQueue;
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

void displayClassesData(bool sort = false, string sortBy = "alphabetical", bool showAll = false) {
    // Salin data kelas untuk menghindari modifikasi data asli
    Class tempClasses[MAX_DATA];
    copy(CLASSES_DATA, CLASSES_DATA + c, tempClasses);

    // Urutkan data jika diminta
    if (sort) {
        if (sortBy == "alphabetical") {
            sortClass(tempClasses, c, sortBy, [](const Class& a, const Class& b) {
                return a.name < b.name;
            });
        } else if (sortBy == "id") {
            sortClass(tempClasses, c, sortBy, [](const Class& a, const Class& b) {
                return a.id < b.id;
            });
        } else if (sortBy == "teacher") {
            sortClass(tempClasses, c, sortBy, [](const Class& a, const Class& b) {
                return a.teacher->username < b.teacher->username;
            });            
        } // TODO: Tambahkan opsi pengurutan lain jika diperlukan
    }

    cout << "\n--- Daftar Kelas ---" << endl;

    // Tampilkan header tabel
    cout << "ID\tNama\t\tGuru\t\tSiswa\tTugas" << endl;
    cout << "----------------------------------------------------------" << endl;

    for (int i = 0; i < c; i++) {
        Class& cls = tempClasses[i];

        // Filter kelas berdasarkan guru yang sedang login jika showAll = false
        if (!showAll && loggedIn.isTeacher && cls.teacher != loggedIn.teacherPtr) {
            continue;
        }

        cout << cls.id << "\t" << cls.name << "\t\t";

        // Tampilkan nama guru jika ada
        if (cls.teacher) {
            cout << cls.teacher->username;
        } else {
            cout << "-"; // atau "NULL"
        }
        cout << "\t\t";

        // Tampilkan jumlah siswa
        cout << cls.numStudents << "\t";

        // Tampilkan jumlah tugas
        cout << cls.assignments.size() << endl;
        // for (Assignment* assignment : cls.assignments) {
        //     cout << "ID: " << assignment->id << "TUGAS: " << assignment->description  << endl;
        // }
    }   
    cout << endl;
    system("pause"); 
}

void displayStudentsData(bool sort = false, string sortBy = "alphabetical", bool showAll = false) {
    Student tempStudents[MAX_DATA];
    copy(STUDENTS_DATA, STUDENTS_DATA + s, tempStudents);

    if (sort) {
        if (sortBy == "alphabetical") {
            sortUser(tempStudents, s, sortBy, [](const Student& a, const Student& b) {
                return a.firstName < b.firstName;
            });
        } else if (sortBy == "id") {
            sortUser(tempStudents, s, sortBy, [](const Student& a, const Student& b) {
                return a.id < b.id;
            });
        } else if (sortBy == "email") {
            sortUser(tempStudents, s, sortBy, [](const Student& a, const Student& b) {
                return a.email < b.email;
            });
        } else if (sortBy == "fullname") {
            sortUser(tempStudents, s, sortBy, [](const Student& a, const Student& b) {
                return a.firstName + " " + a.lastName < b.firstName + " " + b.lastName;
            });
        }
    }

    cout << "\n--- Daftar Siswa ---" << endl;
    cout << "ID\tUsername\tFull Name\t\tEmail\t\tClass\t\tNilai Akumulasi" << endl; // Header tabel
    cout << "-------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < s; i++) {
        Student& student = tempStudents[i];

        // Filter siswa berdasarkan kelas jika showAll = false (hanya jika loggedIn adalah guru)
        if (!showAll && loggedIn.isTeacher && (student.classPtr == nullptr || student.classPtr->teacher != loggedIn.teacherPtr)) {
            continue;
        }

        cout << student.id << "\t" << student.username << "\t" << student.firstName << " " << student.lastName << "\t\t" << student.email << "\t\t";

        // Tampilkan nama kelas jika siswa sudah terdaftar di kelas
        if (student.classPtr) {
            cout << student.classPtr->name;
        } else {
            cout << "-"; // atau "NULL"
        }
        cout << "\t\t";
        
        // Tampilkan nilai siswa
        cout << student.nilaiRataRata << endl;
    }
    cout << endl;
    system("pause"); 
}

void displayTeachersData(bool sort = false, string sortBy = "alphabetical", bool showAll = false) {
    Teacher tempTeachers[MAX_DATA];
    copy(TEACHERS_DATA, TEACHERS_DATA + t, tempTeachers);

    if (sort) {
        if (sortBy == "alphabetical") {
            sortUser(tempTeachers, t, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.firstName < b.firstName;
            });
        } else if (sortBy == "id") {
            sortUser(tempTeachers, t, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.id < b.id;
            });
        } else if (sortBy == "email") {
            sortUser(tempTeachers, t, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.email < b.email;
            });
        } else if (sortBy == "fullname") {
            sortUser(tempTeachers, t, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.firstName + " " + a.lastName < b.firstName + " " + b.lastName;
            });
        } // TODO: Tambahkan opsi pengurutan lain jika diperlukan
    }

    cout << "\n\t--- Daftar Guru ---" << endl;
    cout << "ID\tUsername\tFull Name\t\tEmail\t\tClasses" << endl; // Header tabel
    cout << "----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < t; i++) {
        Teacher& teacher = tempTeachers[i];
        cout << teacher.id << "\t" << teacher.username << "\t\t" << teacher.firstName << " " << teacher.lastName << "\t\t" << teacher.email << "\t\t";
        for ( Class* cls : teacher.classes) {
            if (cls!= nullptr) {
                cout << cls->name << " ";
            }
        }          
    }
    cout << endl;
    system("pause"); 
}

void mainMenu() {
    int option;
    string in, passIn;
    string id, username, password, firstName, lastName, email;
    
    do {
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
                    loggedIn.update(true, &TEACHERS_DATA[i]);
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
            for (int i = 0; i < s; i++) {
                if ((STUDENTS_DATA[i].username == in || STUDENTS_DATA[i].email == in) && STUDENTS_DATA[i].password == passIn) {
                    loggedIn.update(false, nullptr, &STUDENTS_DATA[i]);
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

            TEACHERS_DATA[t].initialize(id, username, password, firstName, lastName, email);

            // saveTeachersToCSV(TEACHERS_DATA, "teachers.csv");
            loggedIn.update(true, &TEACHERS_DATA[t]);
            t++;
            loggedIn.display();

            cout << "TEACHERS_DATA SEKARANG: " << endl;
            displayTeachersData(false, "alphabetical", true);
            
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
            
            STUDENTS_DATA[s].initialize(id, username, password, firstName, lastName, email); // TODO: ubah ID menjadi otomatis dan bukan inputan

            loggedIn.update(false, nullptr, &STUDENTS_DATA[s]);    
            s++;        
            loggedIn.display();

            studentMenu();
            break; 
        }
        default: {
            break;
        }
        }
    } while (option != 5);
    cout << endl;
}

void teacherMenu() {
    int option;

    do {
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
            loggedIn.reset();
            break;
        }
        default: {
            break;
        }
        }
    } while (option != 5);
}

void studentMenu() {
    int option;

    do {
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
        case 3: {
            loggedIn.reset();
            break;
        }
        default: {
            break;
        }
        }
    } while (option != 3);
}

void seeClass() {
    Student* foundStudent = loggedIn.studentPtr; // Inisialisasi dengan nullptr

    if (foundStudent->classPtr != nullptr) {
        int opt;
        do {
            cout << "-- INFO KELAS -- " << endl;
            cout << "Nama Kelas: " << foundStudent->classPtr->name << endl;
            cout << "ID: " << foundStudent->classPtr->id << endl;
            cout << "Guru: " << foundStudent->classPtr->teacher->username << endl << endl;

            cout << "1. Lihat tugas" << endl;
            cout << "2. Lihat akumulasi nilai anda" << endl;
            cout << "3. Kembali" << endl;
            cout << "Pilih opsi: "; cin >> opt;

            switch (opt) {
            case 1: {
                string inputId;
    
                if (foundStudent->classPtr->assignments.empty()) { // TODO
                    cout << "Saat ini Anda tidak memiliki tugas" << endl;
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
                cin >> inputId; // TODO: input mungkin akan diubah menjadi pilihan nomor dari daftar tugas
                
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
            case 2: {
                cout << "Nilai akumulasi anda: " << foundStudent->nilaiRataRata << endl;
                cout << "                      --" << endl;
                break;
            }
            default: {
                break;
            }    
            }
        } while (opt != 3);
    } else {
        char opt;
        cout << "Anda belum memiliki kelas. Ikuti kelas? (y/n)\n->";
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
    if (c == 0) {
        cout << "Belum ada kelas yang tersedia." << endl;
        return;
    }
    
    for (int i = 0; i < c; i++) {
        cout << "Id: " << CLASSES_DATA[i].id << " - Nama: " << CLASSES_DATA[i].name << endl;
    }
    cout << "Masukkan ID kelas: ";
    cin >> id;

    for (int i = 0; i < c; i++) {
        if (CLASSES_DATA[i].id == id) {
            CLASSES_DATA[i].addStudent(loggedIn.studentPtr);
            loggedIn.studentPtr->setClass(&CLASSES_DATA[i]);
            foundClass = true;
            cout << "Berhasil mengikuti kelas " << CLASSES_DATA[i].name << endl;
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

    if (!foundTeacher || foundTeacher->numClasses == 0) {
        cout << "Error: Anda tidak memiliki kelas" << endl;
        return;
    }

    cout << "Pilih kelas yang mana: " << endl;
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

    cout << endl;
    cout << "1. Tampilkan semua nilai siswa di kelas " << selectedClass->name << endl;
    cout << "2. Cari nilai satu siswa di kelas " << selectedClass->name << endl;
    cout << "Pilih opsi:\n-> ";
    cin >> opt; 

    switch (opt) {
    case 1: {
        displayStudentsData(false, "alphabetical", false);
        break;
    }
    case 2: {
        string key;
        cout << "Masukkan ID atau nama lengkap siswa: ";
        cin.ignore();
        getline(cin, key);

        Student* foundStudent = searchStudent(key, selectedClass);

        if (foundStudent) {
            cout << "\nNilai siswa " << foundStudent->firstName << " " << foundStudent->lastName << ": " << foundStudent->nilaiRataRata << endl;
        } else {
            cout << "Siswa dengan ID atau nama " << key << " tidak ditemukan di kelas ini." << endl;
        }
        break;
    }
    default: {
        break;
    }
    }
    return;
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
                        foundStudent->nilaiRataRata += nilai;

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
    string id, name;
    Teacher* foundTeacher = loggedIn.teacherPtr; // foundTeacher adalah yang sedang login saat ini


    do {
        cout << "--- MANAJEMEN KELAS ---" << endl;
        cout << "1. Membuat kelas" << endl;
        cout << "2. Mengedit kelas" << endl;
        cout << "3. Menghapus kelas" << endl;
        cout << "4. Melihat kelas yang Anda ajar" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih opsi:\n-> ";

        cin >> option;

        switch (option) {
        case 1: {
            cout << "Masukkan ID kelas: ";
            cin >> id; cin.ignore();
            cout << "Masukkan Nama kelas: ";
            getline(cin, name);

            if (foundTeacher) {
                CLASSES_DATA[c].initialize(id, name);
                CLASSES_DATA[c].setTeacher(foundTeacher);
        
                foundTeacher->addClass(&CLASSES_DATA[c]);
                c++;
                
                cout << "Kelas berhasil dibuat." << endl;
                
                loggedIn.update(true, foundTeacher);
            } else {
                cout << "Error: Guru yang sedang login tidak ditemukan." << endl;
            }        
            
            break;
        }
        case 2: {
            string newName, newId;
            if (!foundTeacher || foundTeacher->numClasses == 0) {
                cout << "Error: Anda tidak memiliki kelas" << endl;
                break;
            }

            cout << "Pilih kelas yang mana: " << endl;
            for (int i = 0; i < foundTeacher->numClasses; ++i) {
                cout << i + 1 << ". " << foundTeacher->classes[i]->id << " - " << foundTeacher->classes[i]->name << endl;
            }
            
            int pilihanKelas;
            cout << "-> "; cin >> pilihanKelas; cin.ignore();
            // Validasi input pilihan kelas
            if (pilihanKelas < 1 || pilihanKelas > foundTeacher->numClasses) {
                cout << "Pilihan tidak valid." << endl;
                return;
            }
            Class* selectedClass = foundTeacher->classes[pilihanKelas - 1];

            cout << "Masukkan nama kelas baru (tekan '0' untuk membatalkan):\n-> "; 
            getline(cin, newName);
            if (newName != "0") {
                selectedClass->name = newName;
            }   

            cout << "Masukkan id kelas baru (tekan '0' untuk membatalkan):\n-> ";
            cin >> newId;

            if (newId != "0") {
                selectedClass->id = newId;
            }   
            break;
            // TODO
        }
        case 3: {
            // TODO
        }
        case 4: {
            displayClassesData(false, "alphabetical", false);
        }
        default: {
            break;
        }
        }
    } while (option != 5);
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
    cout << "Tugas ini untuk kelas apa? (Pilih nomor): " << endl; 

    for (int i = 0; i < foundTeacher->numClasses; ++i) {
        cout << i + 1 << ". " << foundTeacher->classes[i]->id << " - " << foundTeacher->classes[i]->name << endl;
    }
    
    int pilihanKelas;
    cout << "\n-> "; cin >> pilihanKelas;
    // Validasi input pilihan kelas
    if (pilihanKelas < 1 || pilihanKelas > foundTeacher->numClasses) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    Class* selectedClass = foundTeacher->classes[pilihanKelas - 1];

    ASSIGNMENT_DATA[a].initialize(id, description, dueDate);
    ASSIGNMENT_DATA[a].setClass(selectedClass);
    
    // Tambahkan assignment ke vektor assignments pada selectedClass
    selectedClass->assignments.push_back(&ASSIGNMENT_DATA[a]); 
    cout << "Tugas berhasil ditambahkan oleh " << ASSIGNMENT_DATA[a].classPtr->teacher->username << endl;

    a++;    
    // saveClassesToCSV(CLASSES_DATA, "classes.csv");
}