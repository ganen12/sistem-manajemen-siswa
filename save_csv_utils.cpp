#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "Student.h"
#include "Teacher.h"
#include "Class.h"
#include "Assignment.h"

void saveTeachersToCSV(const vector<Teacher>& data, const string& filename  = "teachers.csv", bool includeHeader = true) {
    const int vectorSize = data.size() - 1;

    if (filename.empty()) {
        cerr << "Error: Nama file tidak boleh kosong." << endl;
        return;
    }

    // Menggunakan direktori kerja saat ini
    filesystem::path currentDir = filesystem::current_path();
    filesystem::path filePath = currentDir / filename;

    ofstream file(filePath, ios::out); // Buka file dalam mode overwrite (ios::out)

    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    // Write header jika diminta
    if (includeHeader) {
        file << "ID,Username,Password,First Name,Last Name,Email,Class" << endl;
    }

    // Write data
    for (const Teacher& teacher : data) {
        file << teacher.id << ","
             << teacher.username << ","
             << teacher.password << ","
             << teacher.firstName << ","
             << teacher.lastName << ","
             << teacher.email << ",";

        bool hasClasses = false; // Flag untuk menandai apakah guru mengajar kelas
        for (int i = 0; i < 6; ++i) {
            if (teacher.classes[i] != nullptr) {
                hasClasses = true;
                file << teacher.classes[i]->name; // Tulis nama kelas jika ada
                if (i < teacher.numClasses - 1) { // Tambahkan koma jika bukan kelas terakhir
                    file << ",";
                }
            }
        }
        if (!hasClasses) {
            file << "NULL"; // Jika tidak ada kelas yang diajar
        }
        file << endl;
    }

    file.close(); // Tutup file
    cout << "Data berhasil disimpan ke " << filename << endl;
}

void saveStudentsToCSV(const vector<Student>& data, const string& filename = "students.csv", bool includeHeader = true) {
    if (filename.empty()) {
        cerr << "Error: Nama file tidak boleh kosong." << endl;
        return;
    }

    filesystem::path currentDir = filesystem::current_path();
    filesystem::path filePath = currentDir / filename;

    ofstream file(filePath, ios::out); 

    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    if (includeHeader) {
        file << "ID,Username,Password,First Name,Last Name,Email,Class" << endl;
    }

    for (const Student& student : data) {
        file << student.id << ","
             << student.username << ","
             << student.password << ","
             << student.firstName << ","
             << student.lastName << ","
             << student.email << ","
             << (student.classPtr ? student.classPtr->name : "NULL") << endl; 
    }

    file.close();
    cout << "Data berhasil disimpan ke " << filename << endl;
}

void saveClassesToCSV(const vector<Class>& data, const string& filename = "classes.csv", bool includeHeader = true) {
    if (filename.empty()) {
        cerr << "Error: Nama file tidak boleh kosong." << endl;
        return;
    }

    filesystem::path currentDir = filesystem::current_path();
    filesystem::path filePath = currentDir / filename;

    ofstream file(filePath, ios::out);

    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    if (includeHeader) {
        file << "ID,Name,Teacher,Assignments" << endl; // Header untuk Class
    }

    for (const Class& cls : data) {
        file << cls.id << ","
             << cls.name << ","
             << (cls.teacher ? cls.teacher->username : "NULL") << endl; // Ambil ID guru jika ada, atau NULL
    }

    file.close();
    cout << "Data berhasil disimpan ke " << filename << endl;
}

void saveAssignmentsToCSV(const vector<Assignment>& data, const string& filename = "assignments.csv", bool includeHeader = true) {
    if (filename.empty()) {
        cerr << "Error: Nama file tidak boleh kosong." << endl;
        return;
    }

    filesystem::path currentDir = filesystem::current_path();
    filesystem::path filePath = currentDir / filename;

    ofstream file(filePath, ios::out);

    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        return;
    }

    if (includeHeader) {
        file << "ID,Description,Duedate" << endl; // Header untuk Class
    }

    for (const Assignment& ass : data) {
        file << ass.id << ","
             << ass.description << ","
             << ass.dueDate << ","
             << (ass.classPtr ? ass.classPtr->id : "NULL") << endl; // Ambil ID guru jika ada, atau NULL
    }

    file.close();
    cout << "Data berhasil disimpan ke " << filename << endl;
}
