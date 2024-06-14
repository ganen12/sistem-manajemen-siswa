#ifndef SEQUENTIALSEARCH_H
#define SEQUENTIALSEARCH_H
#include "Teacher.h"

Student* searchStudent(string key, const Class* selectedClass) {
    Student* foundStudent = nullptr;
    for (int i = 0; i < selectedClass->numStudents; i++) {
        if (key == selectedClass->students[i]->id ||
            key == selectedClass->students[i]->username || 
            key == selectedClass->students[i]->email) {
            foundStudent = selectedClass->students[i];
            break;            
        }
    }
    return foundStudent; 
}

#endif