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
};

#endif // PENGUMPULAN_H
