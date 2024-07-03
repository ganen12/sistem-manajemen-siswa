// Pengumpulan.h
#ifndef PENGUMPULAN_H
#define PENGUMPULAN_H

#include <string>
#include <ctime>

using namespace std;

struct Pengumpulan {
    string tugasId;
    int subjectId;
    string subject;
    string description;
    string studentId;
    string studentName;
    time_t timestamp;

    void initialize(string tugasId, int subjectId, string description, string studentId, string studentName) {
        this->tugasId = tugasId;
        this->subjectId = subjectId;
        this->description = description;
        this->studentId = studentId;
        this->studentName = studentName;
        // this->timestamp = time(0);
    }
};

#endif // PENGUMPULAN_H
