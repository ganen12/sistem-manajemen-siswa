// Class.h
#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include "Assignment.h"
#include "Student.h"
// #include "Forum.h"

using namespace std;

const int MAX_STUDENTS = 36;

struct Class {
    string id;
    string name; // class name
    string subject;
    Teacher* teacher; // pointer to the teacher of this class
    vector<Assignment*> assignments; // pointers to all assignments in this class
    Student* students[MAX_STUDENTS]; // Array untuk menyimpan pointer ke siswa
    vector<Message> discussionForum;
    int numStudents = 0;

    // Class(string id, string name) : id(id), name(name) {}

    void initialize(string id, string name) {
        this->id = id;
        this->name = name;
    }

    void setTeacher(Teacher* teacher) {
        this->teacher = teacher;
    }

    void setSubject(string subject) {
        this->subject = subject;
    }

    void addStudent(Student* s) {
        if (numStudents < MAX_STUDENTS) {
            this->students[numStudents] = s; // Tambahkan siswa ke array dan increment numStudents
            numStudents++;
        } else {
            cout << "Kapasitas maksimal siswa sudah tercapai." << endl;
        }
    }

    void addAssignment(Assignment* assignment) {
        this->assignments.push_back(assignment);
    }

    void removeStudent(Student* s) {
        if (numStudents == 0) {
            cout << "Tidak ada siswa dalam kelas ini." << endl;
            return;
        }
        for (int i = 0; i < numStudents; i++) {
            if (students[i] == s) {
                for (int j = i; j < numStudents - 1; j++) {
                    students[j] = students[j + 1];
                }
                numStudents--;
                students[numStudents] = nullptr;
                cout << "Siswa berhasil dihapus." << endl;
            }
        }
    }

    void addMessage(const Message* message) {
        this->discussionForum.push_back(*message);
    }

    void deleteForum() {
        this->discussionForum.clear();
    }

    string fullClassName() {
        return this->name + " " + this->subject;
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
