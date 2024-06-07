// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include "Student.h"
// #include "Teacher.h"
// #include "Class.h"
// #include "Assignment.h"
// #include "Pengumpulan.h"

// using namespace std;

// void loadTeachersFromCSV(const string& filename = "teachers.csv", bool hasHeader = true) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error: Tidak dapat membuka file " << filename << endl;
//         return;
//     }

//     string line;
//     if (hasHeader) {
//         getline(file, line); // Lewati baris header
//     }

//     while (getline(file, line)) {
//         stringstream ss(line);
//         string id, username, password, firstName, lastName, email;
//         getline(ss, id, ',');
//         getline(ss, username, ',');
//         getline(ss, password, ',');
//         getline(ss, firstName, ',');
//         getline(ss, lastName, ',');
//         getline(ss, email, ',');

//         TEACHERS_DATA.push_back(Teacher(id, username, password, firstName, lastName, email));
//     }

//     file.close();
// }