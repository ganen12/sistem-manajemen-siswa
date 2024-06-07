// Pengumpulan.h
#ifndef PENGUMPULAN_H
#define PENGUMPULAN_H

#include <string>
#include <ctime>

using namespace std;

struct Pengumpulan {
    int tugasId;
    string description;
    string studentId;
    time_t timestamp;
};

#endif // PENGUMPULAN_H
