// Nilai.h
#ifndef NILAI_H
#define NILAI_H

#include <vector>

using namespace std;

enum MataPelajaran {
    BAHASA_INDONESIA,
    BAHASA_INGGRIS,
    MATEMATIKA,
    IPA,
    IPS,
    PKN,
    SENI_BUDAYA,
    PENJASKES,
    // ... mata pelajaran lainnya
};

struct Nilai {
    bool initialized = false;
    vector<float> nilaiMataPelajaran;

    Nilai(int jumlahMataPelajaran) : nilaiMataPelajaran(jumlahMataPelajaran, 0.0) {}

    void setNilai(MataPelajaran mataPelajaran, float nilai) {
        nilaiMataPelajaran[mataPelajaran] += nilai; 
        initialized = true;
    }

    float getNilai(MataPelajaran mataPelajaran) {
        if (!this->initialized || nilaiMataPelajaran[mataPelajaran] == 0.0) {
            return 0.0; // Atau nilai default lainnya jika belum ada nilai yang diinput
        }
        return nilaiMataPelajaran[mataPelajaran];
    }

    float getSumOfNilai() {
        if (!this->initialized) {
            return 0.0;
        }

        float totalNilai = 0.0;
        for (float nilai : this->nilaiMataPelajaran) {
            totalNilai += nilai;
        }

        return totalNilai / this->nilaiMataPelajaran.size();
    }
};

// struct Nilai {
//     float bahasaIndonesia;
//     float bahasaInggris;
//     float matematika;
//     float ipa;
//     float ips;
//     float pkn;
//     float seniBudaya;
//     float penjaskes;
//     // ... (tambahkan mata pelajaran lain sesuai kebutuhan)

//     void setInd(float nilai) {
//         this->bahasaIndonesia = nilai;
//     }
//     void setIng(float nilai) {
//         this->bahasaInggris = nilai;
//     }
//     void setMatematika(float nilai) {
//         this->matematika = nilai;
//     }
//     void setIpa(float nilai) {
//         this->ipa = nilai;
//     }
//     void setIps(float nilai) {
//         this->ips = nilai;
//     }
//     void setPkn(float nilai) {
//         this->pkn = nilai;
//     }
//     void setSeniBudaya(float nilai) {
//         this->seniBudaya = nilai;
//     }
//     void setPenjaskes(float nilai) {
//         this->penjaskes = nilai;
//     }    

// };

#endif // NILAI_H
