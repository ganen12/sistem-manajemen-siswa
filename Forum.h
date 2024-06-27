#ifndef FORUM_H
#define FORUM_H

#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "Class.h"
#include "Teacher.h"

using namespace std;

struct Message {
    Student* studentPtr;
    Teacher* teacherPtr;
    string messageContent;
    string timeSent; // Format: dd-mm-yyyy hh:mm:ss (contoh: 27-06-2024 22:30:15)

    void setMessage(Student* student = nullptr, Teacher* teacher = nullptr, string messageContent = "") {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        string timeSent = to_string(ltm->tm_mday) + "-" + 
                            to_string(1 + ltm->tm_mon) + "-" + 
                            to_string(1900 + ltm->tm_year) + " " + 
                            to_string(ltm->tm_hour) + ":" + 
                            to_string(ltm->tm_min);

        this->studentPtr = student;
        this->teacherPtr = teacher;
        this->messageContent = messageContent;
        this->timeSent = timeSent;
    }

    void display() {
        if (this->studentPtr != nullptr) {
            cout << "From: " << this->studentPtr->username << " " << char(249) << " At: " << this->timeSent << endl;
        } else if (this->teacherPtr != nullptr) {
            cout << "From: " << this->teacherPtr->username << " " << char(249) << " At: " << this->timeSent << endl;
        } 
        cout << "> " << this->messageContent << endl;
        cout << endl;
    }
};

#endif // FORUM_H