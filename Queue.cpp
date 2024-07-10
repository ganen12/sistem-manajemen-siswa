#include "Queue.h"
#include <iostream>

using namespace std;

void Queue::enqueue(Pengumpulan* data) {
    if (isFull()) {
        cout << "Queue sudah penuh !!!" << endl << endl;
        return;
    }

    depan = 0;
    belakang++;
    this->data[belakang] = data;

    // cout << "\nAntrian yang Menunggu : " << belakang + 1 << endl << endl; // Tampilkan jumlah antrian
}

void Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue masih kosong !!!" << endl;
        return;
    }
    for (int i = depan; i < belakang; i++) {
        data[i] = data[i + 1];
    }
    belakang--;
    if (isEmpty()) {
        depan = -1; // Reset depan jika queue menjadi kosong
    }
}

void Queue::clear() {
    if (isEmpty()) {
        cout << "Queue masih kosong !!!" << endl << endl;
        return;
    }
    depan = belakang = -1;
    cout << "Queue sudah dikosongkan" << endl << endl;
}

bool Queue::isEmpty() {
    return (belakang == -1);
}

bool Queue::isFull() {
    return (belakang >= (MAX_QUEUE - 1));
}

void Queue::print(Teacher* currentTeacher) {
    if (isEmpty()) {
        cout << "Queue masih kosong" << endl;
        return;
    } 
    // Ambil pointer ke guru yang sedang login

    cout << "Isi Queue Tugas Anda:" << endl;
    for (int i = depan; i <= belakang; i++) {
        // Cari tugas berdasarkan tugasId
        Assignment* assignment = nullptr;
        for (int j = 0; j < a; j++) {
            if (ASSIGNMENT_DATA[j].id == data[i]->tugasId) {
                assignment = &ASSIGNMENT_DATA[j];
                break;
            }
        }

        // Tampilkan hanya jika tugas diajarkan oleh guru yang sedang login
        if (assignment && assignment->classPtr->teacher == currentTeacher) {
            cout << endl;
            cout << "+----------------------------------+" << endl;
            cout << i + 1 << ". ID Tugas: " << data[i]->tugasId << " - Dikumpulkan oleh " << data[i]->studentName << endl;
            cout << "   " << data[i]->description << endl;
            cout << "+----------------------------------+" << endl;
        }
    }
}
