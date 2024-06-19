// Pengumpulan.h
#ifndef PENGUMPULAN_H
#define PENGUMPULAN_H

#include <string>
#include <ctime>

using namespace std;

struct Pengumpulan {
    string tugasId;
    string description;
    string studentId;
    string studentName;
    time_t timestamp;

    void initialize(string tugasId, string description, string studentId, string studentName) {
        this->tugasId = tugasId;
        this->description = description;
        this->studentId = studentId;
        this->studentName = studentName;
        // this->timestamp = time(0);
    }
};

#endif // PENGUMPULAN_H
