// Class.h
#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include "Assignment.h"
#include "Student.h"
#include "Teacher.h"

using namespace std;

struct Class {
    string id;
    string name; // course name
    Teacher* teacher; // pointer to the teacher of this class
    vector<Student*> students; // pointers to all students enrolled in this class
    vector<Assignment*> assignments; // pointers to all assignments in this class

    Class(string id, string name, Teacher* teacher = nullptr)
    : id(id), name(name), teacher(teacher), students(), assignments() {}

    void display() {
        cout << "Class: " << id << " " << name << endl;
        // cout << "Teacher: " << teacher->id << " " << teacher->name << endl;
        cout << "Students: " << endl;
        // for (Student* student : students) {
        //     cout << "    " << student->id << " " << student->name << endl;
        // }
        cout << "Assignments: " << endl;
        // for (Assignment* assignment : assignments) {
        //     cout << "    " << assignment->id << " " << assignment->description  << endl;
        // }
        cout << endl;
    }
};

struct CSVRecordClass {
    string id;
    string name; 
    // Teacher* teacher; 
    // vector<Student*> students; 
    // vector<Assignment*> assignments; 

    CSVRecordClass(string id, string name)
    : id(id), name(name) {}
        
};

#endif // CLASS_H