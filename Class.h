// Class.h
#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include "Assignment.h"
#include "Student.h"


using namespace std;

const int MAX_STUDENTS = 36;

struct Class {
    string id;
    string name; // course name
    Teacher* teacher; // pointer to the teacher of this class
    vector<Assignment*> assignments; // pointers to all assignments in this class
    Student* students[MAX_STUDENTS]; // Array untuk menyimpan pointer ke siswa
    int numStudents = 0;

    // Class(string id, string name, Teacher* teacher = nullptr)
    // : id(id), name(name), teacher(teacher), students(), assignments() {}

    void initialize(string id, string name) {
        this->id = id;
        this->name = name;
    }

    void setTeacher(Teacher* teacher) {
        this->teacher = teacher;
    }

    void addStudent(Student* s) {
        if (numStudents < MAX_STUDENTS) {
            this->students[numStudents] = s; // Tambahkan siswa ke array dan increment numStudents
            numStudents++;
        } else {
            cout << "Kapasitas maksimal siswa sudah tercapai." << endl;
        }
    }

    void display() {
        cout << "Class: " << id << " " << name << endl;
        if (teacher != nullptr) {
            // cout << "Teacher: " << teacher->id << " " << teacher->username << endl;
        } else {
            cout << "Teacher: Tidak ada" << endl;
        }
        
        cout << "Students: " << endl;
        // for (Student* student : students) {
        //     cout << "ID: " << student->id << "\tName: " << student->username << endl;
        // }
        cout << "Assignments: " << endl;
        for (Assignment* assignment : assignments) {
            cout << "    " << assignment->id << " " << assignment->description  << endl;
        }
    }
};


#endif // CLASS_H
