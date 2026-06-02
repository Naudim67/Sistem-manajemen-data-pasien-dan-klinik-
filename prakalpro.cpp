#include <iostream>
#include <fstream>   // MATERI: FILE I/O
#include <vector>
#include <string>

using namespace std;

// Struktur data pasien
struct Pasien {
    int idPasien;
    string nama;
    string keluhan;
};

// =========================================================================
// 1. MATERI: ARRAY 2D
// =========================================================================
// Array 2D digunakan untuk menyimpan jadwal piket dokter di klinik (3 Baris x 2 Kolom)
// Baris = Hari (Senin, Selasa, Rabu), Kolom = Shift (Pagi, Malam)
string jadwalDokter[3][2] = {
    {"Dr. Andi (Pagi)", "Dr. Budi (Malam)"},    
    {"Dr. Citra (Pagi)", "Dr. Dedi (Malam)"},   
    {"Dr. Eka (Pagi)", "Dr. Farhan (Malam)"}    
};

void tampilkanJadwal() {
    cout << "\n=== JADWAL DOKTER KLINIK ===" << endl;
    cout << "Hari\t\t| Shift Pagi\t\t| Shift Malam" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "0. Senin\t| " << jadwalDokter[0][0] << "\t| " << jadwalDokter[0][1] << endl;
    cout << "1. Selasa\t| " << jadwalDokter[1][0] << "\t| " << jadwalDokter[1][1] << endl;
    cout << "2. Rabu\t\t| " << jadwalDokter[2][0] << "\t| " << jadwalDokter[2][1] << endl;
    cout << "========================================================" << endl;
}

// =========================================================================
// 2. MATERI: POINTER
// =========================================================================
// Fungsi menerima alamat memory (pointer) untuk mencetak detail pasien tanpa boros RAM
void tampilkanDetailPasien(const Pasien* p) {
    if (p == nullptr) {
        cout << "[Sistem] Data pasien tidak ditemukan.\n";
        return;
    }
    cout << "\n=== DETAIL DATA PASIEN (Materi: Pointer) ===" << endl;
    cout << "ID Pasien    : " << p->idPasien << endl;
    cout << "Nama Pasien  : " << p->nama << endl;
    cout << "Keluhan      : " << p->keluhan << endl;
    cout << "Alamat Memori: " << p << endl; // Menampilkan alamat memori pointer
    cout << "=============================================" << endl;
}

// =========================================================================
// 3. MATERI: SEARCHING & REKURSIF
// =========================================================================
// Fungsi Rekursif untuk mencari pasien berdasarkan nama dari indeks akhir ke awal
Pasien* cariPasienRekursif(vector<Pasien>& daftar, const string& target, int indeks) {
    
    if (indeks < 0) {
        return nullptr;
    }
    
    if (daftar[indeks].nama == target) {
        return &daftar[indeks]; 
    }
    
    return cariPasienRekursif(daftar, target, indeks - 1);
}

// =========================================================================
// 4. MATERI: SORTING & REKURSIF
// =========================================================================
// Fungsi Rekursif Bubble Sort untuk mengurutkan Nama Pasien secara alfabet (A-Z)
void urutkanPasienRekursif(vector<Pasien>& daftar, int n) {
    // Base Case: Jika ukuran data tinggal 1, proses pengurutan selesai
    if (n == 1) {
        return;
    }

    // Satu siklus Bubble Sort untuk menggeser nama "terbesar" ke posisi kanan
    for (int i = 0; i < n - 1; i++) {
        if (daftar[i].nama > daftar[i + 1].nama) {
            // Proses Swap (Penukaran posisi)
            Pasien temp = daftar[i];
            daftar[i] = daftar[i + 1];
            daftar[i + 1] = temp;
        }
    }

    // Rekursi: Panggil kembali fungsinya untuk sisa elemen yang belum terurut (n - 1)
    urutkanPasienRekursif(daftar, n - 1);
}

// =========================================================================
// 5. MATERI: FILE I/O (Input/Output File txt)
// =========================================================================
void simpanDataKeFile(const vector<Pasien>& daftar) {
    ofstream fileKeluar("database_pasien.txt");
    if (fileKeluar.is_open()) {
        for (const auto& p : daftar) {
            fileKeluar << p.idPasien << "|" << p.nama << "|" << p.keluhan << "\n";
        }
        fileKeluar.close();
        cout << "[File] Data berhasil disinkronisasi ke 'database_pasien.txt'." << endl;
    } else {
        cout << "[Error] Gagal membuka file untuk menyimpan data." << endl;
    }
}

void muatDataDariFile(vector<Pasien>& daftar, int& idGenerator) {
    ifstream fileMasuk("database_pasien.txt");
    if (!fileMasuk.is_open()) {
        return; // Jika file belum ada (aplikasi baru pertama kali dijalankan), skip saja
    }
    
    daftar.clear();
    Pasien p;
    string idStr, nama, keluhan;
    
    // Membaca baris demi baris menggunakan pembatas karakter '|'
    while (getline(fileMasuk, idStr, '|') && 
           getline(fileMasuk, nama, '|') && 
           getline(fileMasuk, keluhan)) {
        p.idPasien = stoi(idStr);
        p.nama = nama;
        p.keluhan = keluhan;
        daftar.push_back(p);
        
        if (p.idPasien >= idGenerator) {
            idGenerator = p.idPasien + 1; // Mencegah bentrok ID otomatis
        }
    }
    fileMasuk.close();
}

// =========================================================================
// MAIN PROGRAM
// =========================================================================
int main() {
    vector<Pasien> databasePasien;
    int idGenerator = 101; 
    int pilihan;

    // Membaca database dari file .txt saat program pertama kali dibuka
    muatDataDariFile(databasePasien, idGenerator);

    while (true) {
        cout << "\n=========================================" << endl;
        cout << "  SISTEM MANAJEMEN DATA PASIEN & KLINIK  " << endl;
        cout << "=========================================" << endl;
        cout << "1. Tambah Data Pasien Baru" << endl;
        cout << "2. Tampilkan Semua Pasien" << endl;
        cout << "3. Cari Pasien Berdasarkan Nama " << endl;
        cout << "4. Urutkan Pasien dari A-Z " << endl;
        cout << "5. Lihat Jadwal Piket Dokter " << endl;
        cout << "6. Keluar & Simpan Data " << endl;
        cout << "=========================================" << endl;
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            Pasien pBaru;
            pBaru.idPasien = idGenerator++;
            
            cout << "\n--- Input Pasien Baru ---" << endl;
            cout << "ID Pasien Otomatis: " << pBaru.idPasien << endl;
            cout << "Nama Lengkap Pasien: ";
            getline(cin, pBaru.nama);
            cout << "Keluhan Medis      : ";
            getline(cin, pBaru.keluhan);

            databasePasien.push_back(pBaru);
            cout << "[Sukses] Data pasien berhasil ditambahkan ke memori sementara." << endl;

        } else if (pilihan == 2) {
            cout << "\n--- Daftar Seluruh Pasien ---" << endl;
            if (databasePasien.empty()) {
                cout << "Database kosong." << endl;
            } else {
                cout << "ID\t| Nama Pasien\t\t| Keluhan" << endl;
                cout << "------------------------------------------------" << endl;
                for (const auto& p : databasePasien) {
                    cout << p.idPasien << "\t| " << p.nama << "\t\t| " << p.keluhan << endl;
                }
            }

        } else if (pilihan == 3) {
            if (databasePasien.empty()) {
                cout << "\n[Info] Database masih kosong." << endl;
                continue;
            }
            string namaDicari;
            cout << "\nMasukkan Nama Pasien yang dicari: ";
            getline(cin, namaDicari);

            // Memanggil fungsi searching REKURSIF (dimulai dari indeks paling belakang)
            Pasien* hasilCari = cariPasienRekursif(databasePasien, namaDicari, databasePasien.size() - 1);
            
            // Menampilkan data via POINTER
            tampilkanDetailPasien(hasilCari);

        } else if (pilihan == 4) {
            if (databasePasien.empty()) {
                cout << "\n[Info] Tidak ada data untuk diurutkan." << endl;
            } else {
                // Memanggil fungsi sorting REKURSIF
                urutkanPasienRekursif(databasePasien, databasePasien.size());
                cout << "\n[Sukses] Data pasien berhasil diurutkan berdasarkan nama (A-Z) via Rekursi!" << endl;
            }

        } else if (pilihan == 5) {
            // Memanggil fungsi Array 2D
            tampilkanJadwal();

        } else if (pilihan == 6) {
            // Simpan data terupdate ke file eksternal .txt sebelum program close
            simpanDataKeFile(databasePasien);
            cout << "\nData berhasil diamankan ke file. Keluar dari sistem..." << endl;
            break;
        } else {
            cout << "\nPilihan salah! Masukkan angka 1-6." << endl;
        }
    }
    return 0;
}
