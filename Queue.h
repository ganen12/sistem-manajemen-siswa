#ifndef QUEUE_H
#define QUEUE_H

#include "Pengumpulan.h"
#include <iostream>

const int MAX_QUEUE = 100;

struct Queue {
    int depan = -1;
    int belakang = -1;
    Pengumpulan* data[MAX_QUEUE]; // Ubah tipe data menjadi Pengumpulan*

    void enqueue(Pengumpulan* data);
    void dequeue();
    void clear();
    bool isEmpty();
    bool isFull();
    void print(Teacher* currentTeacher);

    Pengumpulan* peek() const { // Fungsi untuk melihat elemen terdepan tanpa menghapus
        if (belakang == -1) {
            cout << "Queue masih kosong !!!" << endl;
            return nullptr;
        }
        return data[depan];
    }
};

#endif // QUEUE_H