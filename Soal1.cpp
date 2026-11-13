
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//single linked list
struct Mahasiswa {
    string nim;
    string nama;
    double nilai;
    Mahasiswa* next;
};

class SistemMahasiswa {
private:
    // Pointer Linked List
    Mahasiswa* head;
    Mahasiswa* tail;
    // Dynamic Array
    double* daftarNilai;
    int jumlahNilai;
    int kapasitas;

    bool sudahDiurutkan;

    // Memperbesar kapasitas Dynamic Array
    void tambahKapasitas() {
        int kapasitasBaru = kapasitas * 2;

        double* arrayBaru = new double[kapasitasBaru];

        for (int i = 0; i < jumlahNilai; i++) {
            arrayBaru[i] = daftarNilai[i];
        }

        delete[] daftarNilai;

        daftarNilai = arrayBaru;
        kapasitas = kapasitasBaru;
    }

public:

    //constructor
    SistemMahasiswa() {
        head = nullptr;
        tail = nullptr;

        jumlahNilai = 0;
        kapasitas = 2;

        daftarNilai = new double[kapasitas];

        sudahDiurutkan = false;
    }

    //destrutor
    ~SistemMahasiswa() {
        Mahasiswa* hapus;

        while (head != nullptr) {
            hapus = head;
            head = head->next;
            delete hapus;
        }

        delete[] daftarNilai;
    }

    //prosedur untuk menambah data mahasiswanya
    void tambahMahasiswa() {
        Mahasiswa* baru = new Mahasiswa;

        cout << "\nMasukkan NIM   : ";
        cin >> baru->nim;

        // Meriksa NIM yg udah terdaftar
        if (cariNIM(baru->nim, false)) {
            cout << "NIM sudah terdaftar!\n";
            delete baru;
            return;
        }

        cin.ignore();

        cout << "Masukkan Nama  : ";
        getline(cin, baru->nama);

        cout << "Masukkan Nilai : ";
        cin >> baru->nilai;

        if (baru->nilai < 0 || baru->nilai > 100) {
            cout << "Nilai harus berada antara 0-100!\n";
            delete baru;
            return;
        }

        baru->next = nullptr;

        // nambahin data ke sibgle linked list
        if (head == nullptr) {
            head = baru;
            tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }

        // Memastikan kapasitas Dynamic Array cukup
        if (jumlahNilai == kapasitas) {
            tambahKapasitas();
        }

        // Menambahkan nilai ke Dynamic Array
        daftarNilai[jumlahNilai] = baru->nilai;
        jumlahNilai++;

        sudahDiurutkan = false;

        cout << "\nData mahasiswa berhasil ditambahkan!\n";
    }

   
    //Linear search berdasarkan NIM 
    bool cariNIM(string nimCari, bool tampilkan = true) {
        Mahasiswa* bantu = head;

        while (bantu != nullptr) {
            if (bantu->nim == nimCari) {

                if (tampilkan) {
                    cout << "\nMahasiswa ditemukan!\n";
                    cout << "NIM   : " << bantu->nim << endl;
                    cout << "Nama  : " << bantu->nama << endl;
                    cout << "Nilai : " << bantu->nilai << endl;
                }

                return true;
            }

            bantu = bantu->next;
        }

        if (tampilkan) {
            cout << "\nMahasiswa dengan NIM "
                 << nimCari << " tidak ditemukan.\n";
        }

        return false;
    }

    void menuCariNIM() {
        string nimCari;

        if (head == nullptr) {
            cout << "\nBelum ada data mahasiswa!\n";
            return;
        }

        cout << "\nMasukkan NIM yang ingin dicari: ";
        cin >> nimCari;

        cariNIM(nimCari);
    }

    //ngurutin data pakai insertion sortnya 
    void insertionSort() {
        for (int i = 1; i < jumlahNilai; i++) {

            double key = daftarNilai[i];
            int j = i - 1;

            while (j >= 0 && daftarNilai[j] > key) {
                daftarNilai[j + 1] = daftarNilai[j];
                j--;
            }

            daftarNilai[j + 1] = key;
        }

        sudahDiurutkan = true;

        cout << "\nNilai berhasil diurutkan "
             << "dari terkecil ke terbesar!\n";
    }

    //binary serch 
    void binarySearch() {
        if (jumlahNilai == 0) {
            cout << "\nBelum ada nilai mahasiswa!\n";
            return;
        }

        if (!sudahDiurutkan) {
            cout << "\nUrutkan nilai terlebih dahulu "
                 << "menggunakan Insertion Sort!\n";
            return;
        }

        double nilaiCari;

        cout << "\nMasukkan nilai yang ingin dicari: ";
        cin >> nilaiCari;

        int kiri = 0;
        int kanan = jumlahNilai - 1;
        bool ditemukan = false;

        while (kiri <= kanan) {

            int tengah = kiri + (kanan - kiri) / 2;

            if (daftarNilai[tengah] == nilaiCari) {
                ditemukan = true;
                break;
            }

            else if (daftarNilai[tengah] < nilaiCari) {
                kiri = tengah + 1;
            }

            else {
                kanan = tengah - 1;
            }
        }

        if (ditemukan) {
            cout << "\nNilai " << nilaiCari
                 << " ditemukan dalam data mahasiswa!\n";
        } else {
            cout << "\nNilai " << nilaiCari
                 << " tidak ditemukan.\n";
        }
    }

    //prosedur untuk nampilin data mahasiswanya 
    void tampilkanMahasiswa() {
        if (head == nullptr) {
            cout << "\nBelum ada data mahasiswa!\n";
            return;
        }

        Mahasiswa* bantu = head;

        cout << "\n========== DATA MAHASISWA ==========\n";

        cout << left
             << setw(15) << "NIM"
             << setw(25) << "NAMA"
             << setw(10) << "NILAI" << endl;

        cout << "-----------------------------------------------\n";

        while (bantu != nullptr) {
            cout << left
                 << setw(15) << bantu->nim
                 << setw(25) << bantu->nama
                 << setw(10) << bantu->nilai << endl;

            bantu = bantu->next;
        }
    }

    //nampilin hasil setelah diurutkan 
    void tampilkanNilai() {
        if (jumlahNilai == 0) {
            cout << "\nBelum ada nilai mahasiswa!\n";
            return;
        }

        cout << "\n========== DAFTAR NILAI ==========\n";

        if (sudahDiurutkan) {
            cout << "Status: Sudah diurutkan\n";
        } else {
            cout << "Status: Belum diurutkan\n";
        }

        for (int i = 0; i < jumlahNilai; i++) {
            cout << daftarNilai[i] << " ";

        }

        cout << endl;
    }
};


int main() {
    SistemMahasiswa sistem;

    int pilihan;

    do {
        cout << "\n====================================\n";
        cout << "  SISTEM PENGELOLAAN NILAI MAHASISWA\n";
        cout << "====================================\n";

        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Urutkan Nilai (Insertion Sort)\n";
        cout << "4. Cari Mahasiswa berdasarkan NIM\n";
        cout << "5. Cari Nilai (Binary Search)\n";
        cout << "6. Tampilkan Kumpulan Nilai\n";
        cout << "0. Keluar\n";

        cout << "------------------------------------\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {

            case 1:
                sistem.tambahMahasiswa();
                break;

            case 2:
                sistem.tampilkanMahasiswa();
                break;

            case 3:
                sistem.insertionSort();
                break;

            case 4:
                sistem.menuCariNIM();
                break;

            case 5:
                sistem.binarySearch();
                break;

            case 6:
                sistem.tampilkanNilai();
                break;

            case 0:
                cout << "\nTerima kasih telah menggunakan program!\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}
