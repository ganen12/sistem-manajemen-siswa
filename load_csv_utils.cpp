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
//         getline(ss, email);

//         TEACHERS_DATA.push_back(Teacher(id, username, password, firstName, lastName, email));
//     }

//     file.close();
// }

// void loadClassesFromCSV(const string& filename = "classes.csv", bool hasHeader = true) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error: Tidak dapat membuka file " << filename << endl;
//         return;
//     }

//     string line;
//     if (hasHeader) {
//         getline(file, line); 
//     }

//     while (getline(file, line)) {
//         stringstream ss(line);
//         string id, name, teacherId;
//         getline(ss, id, ',');
//         getline(ss, name, ',');
//         getline(ss, teacherId); // tidak ada koma di akhir baris
        
//         Teacher* teacherPtr = nullptr;
//         for (Teacher& teacher : TEACHERS_DATA) {
//             if (teacher.id == teacherId) {
//                 teacherPtr = &teacher;
//                 break;
//             }
//         }

//         Class newClass(id, name, teacherPtr);
//         CLASSES_DATA.push_back(newClass);
//         if (teacherPtr) {
//             teacherPtr->addClass(&newClass); // Tambahkan kelas ke guru
//         }

//     }

//     file.close();
// }

// void loadStudentsFromCSV(const string& filename = "students.csv", bool hasHeader = true) {
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
//         string id, username, password, firstName, lastName, email, classId;
//         getline(ss, id, ',');
//         getline(ss, username, ',');
//         getline(ss, password, ',');
//         getline(ss, firstName, ',');
//         getline(ss, lastName, ',');
//         getline(ss, email, ',');
//         getline(ss, classId); // Baca ID kelas

//         // Cari pointer ke objek Class berdasarkan classId
//         Class* classPtr = nullptr;
//         for (Class& cls : CLASSES_DATA) {
//             if (cls.id == classId) {
//                 classPtr = &cls;
//                 break;
//             }
//         }

//         STUDENTS_DATA.push_back(Student(id, username, password, firstName, lastName, email));
//         if (classPtr) {
//             classPtr->addStudent(&STUDENTS_DATA.back()); // Tambahkan siswa ke kelas
//         }
//     }

//     file.close();
// }

// void loadAssignmentsFromCSV(const string& filename = "assignments.csv", bool hasHeader = true) {
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
//         string id, description, dueDate, classId;
//         getline(ss, id, ',');
//         getline(ss, description, ',');
//         getline(ss, dueDate, ',');
//         getline(ss, classId); // tidak ada koma di akhir baris

//         // Cari pointer ke objek Class berdasarkan classId (perlu diimplementasikan)
//         Class* classPtr = nullptr;
//         for (Class& cls : CLASSES_DATA) {
//             if (cls.id == classId) {
//                 classPtr = &cls;
//                 break;
//             }
//         }

//         ASSIGNMENT_DATA.push_back(Assignment(id, description, dueDate, classPtr));
//     }

//     file.close();
// }

// void buildRelationships() {
//     // Hubungkan Student dengan Class
//     for (Student& student : STUDENTS_DATA) {
//         for (Class& cls : CLASSES_DATA) {
//             if (cls.id == student.classPtr->id) {
//                 student.setClass(&cls);
//                 cls.addStudent(&student);
//                 break; // Asumsikan seorang siswa hanya bisa berada dalam satu kelas
//             }
//         }
//     }

//     // Hubungkan Class dengan Teacher
//     for (Class& cls : CLASSES_DATA) {
//         for (Teacher& teacher : TEACHERS_DATA) {
//             if (teacher.id == cls.teacher->id) {
//                 cls.teacher = &teacher;
//                 teacher.addClass(&cls);
//                 break; // Asumsikan satu kelas hanya memiliki satu guru
//             }
//         }
//     }

//     // Hubungkan Assignment dengan Class
//     for (Assignment& assignment : ASSIGNMENT_DATA) {
//         for (Class& cls : CLASSES_DATA) {
//                 if (cls.id == assignment.classPtr->id) {
//                 assignment.classPtr = &cls;
//                 cls.assignments.push_back(&assignment);
//                 break;
//             }
//         }
//     }
// }
