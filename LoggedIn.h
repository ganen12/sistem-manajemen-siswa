// LoggedIn.h
#ifndef LOGGEDIN_H
#define LOGGEDIN_H

#include "Student.h"
#include "Teacher.h"
#include <iostream>

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
        cout << "   > " << (isTeacher ? "Guru" : "Siswa") << endl;

        if (isTeacher) {
            cout << "   > ID: " << teacherPtr->id << endl;
            cout << "   > USERNAME: " << teacherPtr->username << endl;
        } else if (!isTeacher) {
            cout << "   > ID: " << studentPtr->id << endl;
            cout << "   > USERNAME: " << studentPtr->username << endl;
        } else {
            cout << "   > Informasi pengguna tidak ditemukan." << endl;
        }
    }

    void reset() {
        this->isTeacher = false;
        this->teacherPtr = nullptr;
        this->studentPtr = nullptr;
    }
};

#endif // LOGGEDIN_H