#include <iostream>
#include <string>
#include <vector>
using namespace std;

//knnstanta untuk ukuran  hash tablenya 
const int TABLE_SIZE = 20;

// Struktur untuk menyimpan data Mahasiswa (Key: NIM, Value: Nama)
struct Mahasiswa {
    long long nim;
    string nama;
    bool isOccupied; // Untuk nandain apakah slotnya sudah terisi data atau belum 
    bool isDeleted;  // Menandakan apakah slot pernah dihapus atau tidak
    Mahasiswa() {
        nim = -1;
        nama = "";
        isOccupied = false;
        isDeleted = false;
    }
};

class HashTable {
private:
    vector<Mahasiswa> table;
    int currentSize;

    // Hash Function 1: Hash1(key) = key % 20
    int hash1(long long key) {
        return key % TABLE_SIZE;
    }

    // Hash Function 2: Hash2(key) = 19 - (key % 19)
    int hash2(long long key) {
        return 19 - (key % 19);
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        currentSize = 0;
    }

    // Fitur Insert: Menambahkan data mahasiswa
    void insert(long long nim, string nama) {
        if (currentSize >= TABLE_SIZE) {
            cout << "[Error] Hash Table penuh! Tidak dapat memasukkan NIM " << nim << "\n";
            return;
        }

        int h1 = hash1(nim);
        int h2 = hash2(nim);
        int index = h1;
        int i = 0;

        // Mencari slot kosong menggunakan double hashing
        while (table[index].isOccupied && table[index].nim != nim) {
            i++;
            index = (h1 + i * h2) % TABLE_SIZE;
            if (i >= TABLE_SIZE) {
                cout << "[Error] Terjadi infinite loop atau tabel penuh.\n";
                return;
            }
        }

        // Jika NIM sudah ada, update namanya
        if (table[index].nim == nim) {
            table[index].nama = nama;
            cout << "[Update] Data mahasiswa dengan NIM " << nim << " berhasil diperbarui.\n";
            return;
        }

        // Masukkan data baru ke slot kosong
        table[index].nim = nim;
        table[index].nama = nama;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
        currentSize++;
        cout << "[Sukses] Berhasil memasukkan: (" << nim << " - " << nama << ") pada indeks " << index << "\n";
    }

    // Fitur Search: Mencari data mahasiswa berdasarkan NIM
    void search(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);
        int index = h1;
        int i = 0;
        int originalIndex = index;

        while (table[index].isOccupied || table[index].isDeleted) {
            if (table[index].isOccupied && table[index].nim == nim) {
                cout << "[Ditemukan] NIM: " << table[index].nim << " | Nama: " << table[index].nama << " (Indeks: " << index << ")\n";
                return;
            }
            i++;
            index = (h1 + i * h2) % TABLE_SIZE;
            if (index == originalIndex || i >= TABLE_SIZE) {
                break;
            }
        }

        cout << "[Tidak Ditemukan] Mahasiswa dengan NIM " << nim << " tidak ada dalam sistem.\n";
    }

    // Fitur Remove: Menghapus data mahasiswa berdasarkan NIM
    void remove(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);
        int index = h1;
        int i = 0;
        int originalIndex = index;

        while (table[index].isOccupied || table[index].isDeleted) {
            if (table[index].isOccupied && table[index].nim == nim) {
                table[index].nim = -1;
                table[index].nama = "";
                table[index].isOccupied = false;
                table[index].isDeleted = true; // Tandai sebagai deleted untuk menjaga rantai probing
                currentSize--;
                cout << "[Sukses] Data dengan NIM " << nim << " berhasil dihapus dari indeks " << index << "\n";
                return;
            }
            i++;
            index = (h1 + i * h2) % TABLE_SIZE;
            if (index == originalIndex || i >= TABLE_SIZE) {
                break;
            }
        }

        cout << "[Gagal Hapus] Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }

    // Fitur Display: Menampilkan seluruh isi Hash Table
    void display() {
        cout << "\n=========================================\n";
        cout << "            STATUS HASH TABLE            \n";
        cout << "=========================================\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Indeks " << (i < 10 ? " " : "") << i << " : ";
            if (table[i].isOccupied) {
                cout << "[NIM: " << table[i].nim << " | Nama: " << table[i].nama << "]\n";
            } else if (table[i].isDeleted) {
                cout << "<DELETED>\n";
            } else {
                cout << "<KOSONG>\n";
            }
        }
        cout << "=========================================\n\n";
    }
};

int main() {
    HashTable ht;

    // Pengujian dengan minimal 15 data mahasiswa (mencakup kondisi collision & penghapusan)
    cout << "--- TAHAP INSERTION (PENAMBAHAN 15 DATA) ---\n";
    ht.insert(251401134, "Frans Eikel");
    ht.insert(251401065, "Aditya Nugraha");
    ht.insert(251401071, "Febrian Al");
    ht.insert(251401089, "Daniel Audrey");
    ht.insert(251401122, "Rafly Syahputra");
    ht.insert(251401001, "Budi Santoso");
    ht.insert(251401002, "Siti Aminah");
    ht.insert(251401003, "Ahmad Fauzi");
    ht.insert(251401004, "Dewi Lestari");
    ht.insert(251401005, "Joko Widodo");
    ht.insert(251401006, "Rina Setiawati");
    ht.insert(251401007, "Eko Prasetyo");
    ht.insert(251401008, "Siti Rahma");
    ht.insert(251401009, "Rizky Ramadhan");
    ht.insert(251401010, "Putri Ananda");

    // Menampilkan tabel setelah 15 data dimasukkan
    ht.display();

    cout << "--- TAHAP PENGUJIAN PENCARIAN (SEARCH) ---\n";
    ht.search(251401089); // Mencari data yang ada
    ht.search(999999999); // Mencari data yang tidak ada

    cout << "\n--- TAHAP PENGUJIAN PENGHAPUSAN (REMOVE) ---\n";
    ht.remove(251401071); // Menghapus data
    ht.search(251401071); // Memastikan data sudah hilang

    // Menampilkan tabel setelah penghapusan
    ht.display();

    cout << "--- TAHAP TEST COLLISION LANJUTAN & RE-INSERT ---\n";
    ht.insert(251401071, "Febrian Al-Katammi (Updated)"); // Memasukkan kembali data baru pada slot bekas/collision
    ht.display();

    return 0;
}
