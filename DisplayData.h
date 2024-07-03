#ifndef DISPLAYDATA_H
#define DISPLAYDATA_H

#include "LoggedIn.h"

const int TEMP_MAX_DATA = 200;

char sudut_kiri_atas = 218;
char garis_hori = 196;
char garis_verti = 179;
char sudut_kanan_atas = 191;
char sudut_kiri_bawah = 192;
char sudut_kanan_bawah = 217;
char tengah_up = 193;
char tengah_down = 194;
char samping_kiri = 195;
char samping_kanan = 180;
char garis_plus = 197;

void displayClassesData(const Class CLASSES_DATA[], int& counter, const LoggedIn& loggedIn, bool sort = false, string sortBy = "alphabetical", bool showAll = false) {
    // Salin data kelas untuk menghindari modifikasi data asli
    Class tempClasses[TEMP_MAX_DATA];
    copy(CLASSES_DATA, CLASSES_DATA + counter, tempClasses);

    // Urutkan data jika diminta
    if (sort) {
        if (sortBy == "alphabetical") {
            sortClass(tempClasses, counter, sortBy, [](const Class& a, const Class& b) {
                return a.name < b.name;
            });
        } else if (sortBy == "id") {
            sortClass(tempClasses, counter, sortBy, [](const Class& a, const Class& b) {
                return a.id < b.id;
            });
        } else if (sortBy == "teacher") {
            sortClass(tempClasses, counter, sortBy, [](const Class& a, const Class& b) {
                return a.teacher->username < b.teacher->username;
            });            
        } 
    }

    cout << "\n--- Daftar Kelas ---" << endl;
    // Tampilkan output tabel
    cout << sudut_kiri_atas;
    for(int i = 1; i <= 8; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 26; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 19; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 18; i++) {
        cout << garis_hori;
    }
     cout << tengah_down;
    for(int i = 1; i <= 18; i++) {
        cout << garis_hori;
    }
    cout << sudut_kanan_atas << endl;
    cout << garis_verti << setw(5) << "ID" << setw(4) << garis_verti << setw(20) << "Mata Pelajaran" << setw(7) << garis_verti;
    cout << setw(12) << "Guru" << setw(8) << garis_verti << setw(15) << "Jumlah Siswa" << setw(4) << garis_verti;
    cout << setw(15) << "Jumlah Tugas" << setw(4) << garis_verti << endl;

    cout << samping_kiri;
    for(int i = 1; i <= 8; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 26; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 19; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 18; i++) {
        cout << garis_hori;
    }
     cout << garis_plus;
    for(int i = 1; i <= 18; i++) {
        cout << garis_hori;
    }
    cout << samping_kanan << endl;

    for (int i = 0; i < counter; i++) {
        Class& cls = tempClasses[i];

        // Filter kelas berdasarkan guru yang sedang login jika showAll = false
        if (!showAll && loggedIn.isTeacher && cls.teacher != loggedIn.teacherPtr) {
            continue;
        }

        cout << garis_verti << cls.id << setw(9 - cls.id.length()); 
        cout << garis_verti << cls.name << setw(27 - cls.name.length()) << garis_verti;

        // Tampilkan nama guru jika ada
        if (cls.teacher) {
            cout << cls.teacher->username;
        } else {
            cout << "-"; // atau "NULL"
        }
        cout << setw(20 - cls.teacher->username.length()) << garis_verti;
        
        // Tampilkan jumlah siswa
        cout << cls.numStudents;
        if(cls.numStudents < 10){
            cout << setw(18);
        }
        else{
            cout << setw(17);
        }
        cout << garis_verti;

        // Tampilkan jumlah tugas
        cout << cls.assignments.size();
        if(cls.assignments.size() < 10){
            cout << setw(18);
        }
        else{
            cout << setw(17);
        }
        cout << garis_verti;
        cout << endl;
    }   

    cout << sudut_kiri_bawah;
    for(int i = 1; i <= 8; i++) {
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 26; i++) {
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 19; i++) {
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 18; i++) {
        cout << garis_hori;
    }
     cout << tengah_up;
    for(int i = 1; i <= 18; i++) {
        cout << garis_hori;
    }
    cout << sudut_kanan_bawah;
    cout << endl;
    
    system("pause"); 
    system("CLEAR"); 
}

void displayStudentsData(const Student STUDENTS_DATA[], int& counter, const LoggedIn& loggedIn, bool sort = false, string sortBy = "alphabetical", bool showAll = false) {
    Student tempStudents[TEMP_MAX_DATA];
    copy(STUDENTS_DATA, STUDENTS_DATA + counter, tempStudents);

    if (sort) {
        if (sortBy == "alphabetical") {
            sortUser(tempStudents, counter, sortBy, [](const Student& a, const Student& b) {
                return a.firstName < b.firstName;
            });
        } else if (sortBy == "id") {
            sortUser(tempStudents, counter, sortBy, [](const Student& a, const Student& b) {
                return a.id < b.id;
            });
        } else if (sortBy == "email") {
            sortUser(tempStudents, counter, sortBy, [](const Student& a, const Student& b) {
                return a.email < b.email;
            });
        } else if (sortBy == "fullname") {
            sortUser(tempStudents, counter, sortBy, [](const Student& a, const Student& b) {
                return a.firstName + " " + a.lastName < b.firstName + " " + b.lastName;
            });
        }
    }

    cout << "\n--- Daftar Siswa ---" << endl;
    // Tabel output
    cout << sudut_kiri_atas;
    for(int i = 1; i <= 8; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 22; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 25; i++) {
        cout << garis_hori;
    }
     cout << tengah_down;
    for(int i = 1; i <= 34; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 23; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 21; i++) {
        cout << garis_hori;
    }
    cout << sudut_kanan_atas;
    cout << endl;
    
    cout << garis_verti << setw(5) << "ID" << setw(4)<< garis_verti << setw(15) << "Username" << setw(8);
    cout << garis_verti << setw(17) << "Full Name" << setw(9) << garis_verti << setw(20) << "Email" << setw(15);
    cout << garis_verti << setw(15) << "Class" << setw(9) << garis_verti << setw(18) << "Nilai Akumulasi" << setw(4) << garis_verti << endl;

    cout << samping_kiri;
    for(int i = 1; i <= 8; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 22; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 25; i++) {
        cout << garis_hori;
    }
     cout << garis_plus;
    for(int i = 1; i <= 34; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 23; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 21; i++) {
        cout << garis_hori;
    }
    cout << samping_kanan << endl;

    for (int i = 0; i < counter; i++) {
        Student& student = tempStudents[i];

        // Filter siswa berdasarkan kelas jika showAll = false (hanya jika loggedIn adalah guru)
        if (!showAll && loggedIn.isTeacher && (student.classPtr == nullptr || student.classPtr->teacher != loggedIn.teacherPtr)) {
            continue;
        }

        cout << garis_verti << student.id << setw(9 - student.id.length()) << garis_verti << student.username << setw(23 - student.username.length()) << garis_verti;
        cout << student.firstName << " " << student.lastName;
        if(student.firstName.length() >= 8 && student.lastName.length() >= 8){
            int setw2 = student.firstName.length() + student.lastName.length();
            if(setw2 >= 16){
                cout << setw(25 - (setw2));
            }         
        }
        else if(student.lastName.length() > 8 && student.firstName.length() < 8){
            int setw1 = student.lastName.length() - 8;
            cout << setw(student.lastName.length() - setw1 + student.firstName.length());
        }
        else if(student.firstName.length() > 8 && student.lastName.length() < 8){
            int setw3 = student.firstName.length() - 8;
            cout << setw(student.firstName.length() - setw3 + student.lastName.length());
        }
        else if(student.firstName.length() < 8 && student.lastName.length() < 8){
            cout << setw(25 - (student.firstName.length() + student.lastName.length()));
        }

        cout << garis_verti << student.email << setw(35 - student.email.length()) << garis_verti;

        // Tampilkan nama kelas jika siswa sudah terdaftar di kelas
        if (student.classPtr) {
            cout << student.classPtr->name << setw(24 - student.classPtr->name.length()) << garis_verti;
        } else {
            cout << "-" << setw(23) << garis_verti; // atau "NULL"
        }
        
        // Tampilkan nilai siswa
        cout << student.nilaiPtr->getSumOfNilai();
        if(student.nilaiPtr->getSumOfNilai() < 10){
            cout << setw(21);
        }
        else if(student.nilaiPtr->getSumOfNilai() < 100){
            cout << setw(22);
        }
        else {
            cout << setw(19);
        }
        cout << garis_verti << endl;
    }

    cout << sudut_kiri_bawah;
    for(int i = 1; i <= 8; i++) {
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 22; i++) {
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 25; i++) {
        cout << garis_hori;
    }
     cout << tengah_up;
    for(int i = 1; i <= 34; i++) {
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 23; i++) {
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 21; i++) {
        cout << garis_hori;
    }
    cout << sudut_kanan_bawah << endl;
    cout << endl;

    system("pause"); 
    system("CLEAR"); 

}

void displayTeachersData(const Teacher TEACHERS_DATA[], int& counter, const LoggedIn& loggedIn, bool sort = false, string sortBy = "alphabetical", bool showAll = false) {
    Teacher tempTeachers[TEMP_MAX_DATA];
    copy(TEACHERS_DATA, TEACHERS_DATA + counter, tempTeachers);

    if (sort) {
        if (sortBy == "alphabetical") {
            sortUser(tempTeachers, counter, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.firstName < b.firstName;
            });
        } else if (sortBy == "id") {
            sortUser(tempTeachers, counter, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.id < b.id;
            });
        } else if (sortBy == "email") {
            sortUser(tempTeachers, counter, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.email < b.email;
            });
        } else if (sortBy == "fullname") {
            sortUser(tempTeachers, counter, sortBy, [](const Teacher& a, const Teacher& b) {
                return a.firstName + " " + a.lastName < b.firstName + " " + b.lastName;
            });
        }
    }

    cout << "\n\t--- Daftar Guru ---" << endl;
    // tabel output setelah sign up
    cout << sudut_kiri_atas;
    for(int i = 1; i <= 7; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 22; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 25; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 34; i++) {
        cout << garis_hori;
    }
    cout << tengah_down;
    for(int i = 1; i <= 21; i++) {
        cout << garis_hori;
    }
    cout << sudut_kanan_atas << endl;
    cout << garis_verti << setw(4) << "ID" << setw(4) << garis_verti << setw(15) << "Username" << setw(8) << garis_verti << setw(17) << "Full Name" << setw(9) << garis_verti;
    cout << setw(20) << "Email" << setw(15) << garis_verti << setw(15) << "Classes" << setw(7) << garis_verti << endl; // Header tabel
    cout << samping_kiri;

    for(int i = 1; i <= 7; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 22; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 25; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 34; i++) {
        cout << garis_hori;
    }
    cout << garis_plus;
    for(int i = 1; i <= 21; i++) {
        cout << garis_hori;
    }

    cout << samping_kanan;
    cout << endl;

    for (int i = 0; i < counter; i++) {
        Teacher& teacher = tempTeachers[i];

        cout << garis_verti << teacher.id << "\t" << garis_verti << teacher.username << setw(23 - teacher.username.length());;
        cout << garis_verti << teacher.firstName << " " << teacher.lastName;
        
        // setw buat nama
        if(teacher.firstName.length() >= 8 && teacher.lastName.length() >= 8){
            int setw2 = teacher.firstName.length() + teacher.lastName.length();
            if(setw2 >= 16){
                cout << setw(25 - (setw2));
            }         
        }
        else if(teacher.lastName.length() > 8 && teacher.firstName.length() < 8){
            int setw1 = teacher.lastName.length() - 8;
            cout << setw(teacher.lastName.length() - setw1 + teacher.firstName.length());
        }
        else if(teacher.firstName.length() > 8 && teacher.lastName.length() < 8){
            int setw3 = teacher.firstName.length() - 8;
            cout << setw(teacher.firstName.length() - setw3 + teacher.lastName.length());
        }
        else if(teacher.firstName.length() < 8 && teacher.lastName.length() < 8){
            cout << setw(25 - (teacher.firstName.length() + teacher.lastName.length()));
        }

        cout << garis_verti << teacher.email << setw(35 - teacher.email.length()) << garis_verti;

        for ( Class* cls : teacher.classes) {
            if (cls != nullptr) {
                cout << cls->name << setw(22 - cls->name.length()) << garis_verti;
                break;
            }
            else {
                cout << setw(22) << garis_verti;
                break;
            }
        }
        cout << endl;          
    }

    cout << sudut_kiri_bawah;
    for(int i = 1; i <= 7; i++){
        
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 22; i++){
        
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 25; i++){
        
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 34; i++){
        
        cout << garis_hori;
    }
    cout << tengah_up;
    for(int i = 1; i <= 21; i++){
        
        cout << garis_hori;
    }
    cout << sudut_kanan_bawah << endl;
    cout << endl;
    system("pause"); 
    system("CLEAR"); 
}


#endif