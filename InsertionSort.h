#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include "Class.h"
#include "Teacher.h"
template <typename T, typename Compare>

void sortUser(T arr[], int n, string sortBy, Compare compare) {
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;

        // Pindahkan elemen arr[0..i-1] yang lebih besar dari key
        // ke satu posisi di depan dari posisi saat ini
        if (sortBy == "alphabetical") {
            while (j >= 0 && arr[j].username > key.username) { 
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;            
        } else if (sortBy == "id") {
            while (j >= 0 && arr[j].id > key.id) { 
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;            
        } else if (sortBy == "fullname") {
            while (j >= 0 && (arr[j].firstName + arr[j].lastName > key.firstName + key.lastName)) { 
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;                     
        } else if (sortBy == "email") {
            while (j >= 0 && arr[j].email > key.email) { 
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;            
        }
        
    }
}

template <typename Compare>
void sortClass(Class arr[], int n, string sortBy, Compare compare) {
    for (int i = 1; i < n; i++) {
        Class key = arr[i];
        int j = i - 1;

        // Pindahkan elemen arr[0..i-1] yang lebih besar dari key
        // ke satu posisi di depan dari posisi saat ini
        if (sortBy == "alphabetical") {
            while (j >= 0 && arr[j].name > key.name) { 
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;            
        } else if (sortBy == "id") {
            while (j >= 0 && arr[j].id > key.id) { 
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;            
        } else if (sortBy == "numStudents") {
            while (j >= 0 && arr[j].numStudents > key.numStudents) { 
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;            
        }
        
    }
}

#endif