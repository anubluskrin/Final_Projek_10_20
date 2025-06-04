#include <bits/stdc++.h>
using namespace std;

// Struct untuk menyimpan data kendaraan
struct Kendaraan {
    string plat;
    string jenis;
    time_t waktuMasuk;
    string slot;
};

const int MAX_KENDARAAN = 100; // Batas maksimum kendaraan
Kendaraan daftarParkir[MAX_KENDARAAN];
int jumlahParkir = 0;
string slot[7][10]; // Layout slot parkir 7x10
int totalKendaraan = 0;
int totalPendapatan = 0;

// Mengubah format waktu menjadi string terbaca
string formatWaktu(time_t waktu) {
    char buffer[80];
    struct tm * timeinfo = localtime(&waktu);
    strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", timeinfo);
    return string(buffer);
}

// Menghasilkan label slot dari indeks baris dan kolom
string labelSlot(int baris, int kolom) {
    char huruf = 'A' + baris;
    return string(1, huruf) + to_string(kolom + 1);
}

// Mencari slot kosong pertama
pair<int, int> cariSlotKosong() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            if (slot[i][j] == "") return {i, j};
        }
    }
    return {-1, -1}; // Tidak ada slot kosong
}

// Menampilkan layout slot parkir
void tampilkanSlot() {
    cout << "\nLayout Slot Parkir (X = terisi):\n";
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            if (slot[i][j] == "") cout << "[ ] ";
            else cout << "[X] ";
        }
        cout << " <== Baris " << char('A' + i) << endl;
    }
    cout << endl;
}

// Mengecek apakah plat nomor sudah ada di daftar parkir
bool platSudahAda(string plat) {
    for (int i = 0; i < jumlahParkir; ++i) {
        if (daftarParkir[i].plat == plat) return true;
    }
    return false;
}

// Fitur kendaraan masuk ke parkiran
void kendaraanMasuk() {
    if (jumlahParkir >= MAX_KENDARAAN) {
        cout << "Parkiran penuh.\n";
        return;
    }
    Kendaraan k;
    // Input plat nomor dan pastikan tidak duplikat
    do {
    cout << "Plat nomor      : ";
    cin >> k.plat;
    if (platSudahAda(k.plat)) {
        cout << "Plat nomor sudah terdaftar! Silakan masukkan plat yang berbeda.\n";
    }
    } while (platSudahAda(k.plat));

    cout << "Jenis kendaraan : ";
    cin >> k.jenis;
    k.waktuMasuk = time(0);

    tampilkanSlot();
    string pilihan;
    cout << "Ingin pilih slot sendiri? (y/n): ";
    cin >> pilihan;
    int baris = -1, kolom = -1;

    // Pilih slot manual
    if (pilihan == "y" || pilihan == "Y") {
        string pilihSlot;
        while (true) {
            cout << "Masukkan kode slot (misal B5): ";
            cin >> pilihSlot;

            if (pilihSlot.length() < 2 || pilihSlot.length() > 3) {
                cout << " Format slot tidak valid. Contoh: A1, B5, G10\n";
                continue;
            }

            baris = toupper(pilihSlot[0]) - 'A';
            try {
                kolom = stoi(pilihSlot.substr(1)) - 1;
            } catch (...) {
                cout << " Format nomor slot salah. Harus angka setelah huruf.\n";
                continue;
            }

            if (baris < 0 || baris >= 7 || kolom < 0 || kolom >= 10) {
                cout << " Slot tidak tersedia. Pilih dari A1 hingga G10.\n";
                continue;
            }

            if (slot[baris][kolom] != "") {
                cout << " Slot sudah terisi. Silakan pilih slot lain.\n";
                continue;
            }

            break;
        }
    } else { // Pilih slot otomatis
        tie(baris, kolom) = cariSlotKosong();
        if (baris == -1) {
            cout << "Parkiran penuh.\n";
            return;
        }
        cout << "Slot direkomendasikan: " << labelSlot(baris, kolom) << endl;
    }

    slot[baris][kolom] = k.plat;
    k.slot = labelSlot(baris, kolom);
    daftarParkir[jumlahParkir++] = k;
    totalKendaraan++;

    cout << "Kendaraan dicatat masuk pada slot " << k.slot << " pada " << formatWaktu(k.waktuMasuk) << endl;

    // Simpan ke file
    ofstream fileMasuk("data_parkir.txt", ios::app);
    fileMasuk << k.plat << "," << k.jenis << "," << k.slot << "," << k.waktuMasuk << endl;
    fileMasuk.close();
}

// Menghapus data kendaraan dari file berdasarkan plat
void hapusDariFile(const string& platTarget) {
    ifstream fileIn("data_parkir.txt");
    ofstream fileOut("temp.txt");
    string line;
    bool dihapus = false;

    while (getline(fileIn, line)) {
        if (line.find(platTarget + ",") != 0) {
            fileOut << line << endl;
        } else {
            dihapus = true;
        }
    }

    fileIn.close();
    fileOut.close();

    remove("data_parkir.txt");
    rename("temp.txt", "data_parkir.txt");

    if (dihapus) {
        cout << "Data kendaraan dihapus dari file.\n";
    } else {
        cout << "Data kendaraan tidak ditemukan di file.\n";
    }
}

// Fitur kendaraan keluar dari parkiran
void kendaraanKeluar() {
    string plat;
    cout << "Masukkan plat nomor kendaraan yang keluar: ";
    cin >> plat;
    bool ditemukan = false;

    for (int i = 0; i < jumlahParkir; ++i) {
        if (daftarParkir[i].plat == plat) {
            time_t waktuKeluar = time(0);
            double durasiJam = difftime(waktuKeluar, daftarParkir[i].waktuMasuk) / 3600.0;
            int biaya = max(1, (int)ceil(durasiJam)) * 2000;

            // Tampilkan detail
            cout << "\nDetail Parkir:\n";
            cout << "Plat nomor      : " << daftarParkir[i].plat << endl;
            cout << "Jenis kendaraan : " << daftarParkir[i].jenis << endl;
            cout << "Slot            : " << daftarParkir[i].slot << endl;
            cout << "Waktu masuk     : " << formatWaktu(daftarParkir[i].waktuMasuk) << endl;
            cout << "Waktu keluar    : " << formatWaktu(waktuKeluar) << endl;
            cout << fixed << setprecision(2);
            cout << "Durasi parkir   : " << durasiJam << " jam\n";
            cout << "Biaya parkir    : Rp " << biaya << "\n";

            int baris = daftarParkir[i].slot[0] - 'A';
            int kolom = stoi(daftarParkir[i].slot.substr(1)) - 1;
            slot[baris][kolom] = "";

            totalPendapatan += biaya;
            for (int j = i; j < jumlahParkir - 1; ++j) {
                daftarParkir[j] = daftarParkir[j + 1];
            }
            jumlahParkir--;
            ditemukan = true;
            hapusDariFile(plat);
            break;
        }
    }

    if (!ditemukan) {
        cout << "Kendaraan tidak ditemukan.\n";
    }
}

// Menampilkan data kendaraan dengan pointer
void tampilkanDenganPointer() {
    cout << "\nDaftar kendaraan (menggunakan pointer):\n";
    Kendaraan* ptr = daftarParkir;
    for (int i = 0; i < jumlahParkir; ++i) {
        cout << "- Plat: " << (ptr + i)->plat << ", Jenis: " << (ptr + i)->jenis
             << ", Slot: " << (ptr + i)->slot << ", Masuk: " << formatWaktu((ptr + i)->waktuMasuk) << endl;
    }
}

// Mengurutkan data kendaraan berdasarkan plat
void sortKendaraanByPlat() {
    for (int i = 0; i < jumlahParkir - 1; i++) {
        for (int j = i + 1; j < jumlahParkir; j++) {
            if (daftarParkir[i].plat > daftarParkir[j].plat) {
                swap(daftarParkir[i], daftarParkir[j]);
            }
        }
    }
    cout << "\nData parkir telah diurutkan berdasarkan plat nomor.\n";
}

// Menghitung jumlah kendaraan secara rekursif
int hitungKendaraan(int i) {
    if (i == jumlahParkir) return 0;
    return 1 + hitungKendaraan(i + 1);
}

// Tampilkan semua kendaraan yang masih parkir
void tampilkanParkir() {
    cout << "\nDaftar kendaraan yang sedang parkir:\n";
    if (jumlahParkir == 0) {
        cout << "Tidak ada kendaraan.\n";
    } else {
        tampilkanDenganPointer();
    }
}

// Statistik harian
void tampilkanStatistik() {
    cout << "\n=== Statistik Harian ===\n";
    cout << "Total kendaraan hari ini : " << totalKendaraan << endl;
    cout << "Total pendapatan hari ini: Rp " << totalPendapatan << endl;
    cout << "Kendaraan saat ini       : " << hitungKendaraan(0) << " \n"; //dihitung rekursif
}

// Simpan laporan harian ke file laporan.txt
void simpanLaporanHarian() {
    ofstream file("laporan.txt", ios::app);
    time_t now = time(0);
    file << "Tanggal: " << formatWaktu(now) << "\n";
    file << "Jumlah kendaraan: " << totalKendaraan << "\n";
    file << "Pendapatan: Rp " << totalPendapatan << "\n";
    file << "--------------------------\n";
    file.close();
}

int main() {
    int pilihan;
    do {
        system("cls");
        cout << "====================\n";
        cout << "||    Parkiran    ||\n";
        cout << "====================\n";
        cout << "1. Kendaraan Masuk\n";
        cout << "2. Kendaraan Keluar\n";
        cout << "3. Tampilkan Data Parkir\n";
        cout << "4. Tampilkan Slot Parkir\n";
        cout << "5. Statistik & Laporan Harian\n";
        cout << "6. Urutkan Data Parkir (Plat Nomor)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                kendaraanMasuk();
                break;
            case 2:
                kendaraanKeluar();
                break;
            case 3:
                tampilkanParkir();
                break;
            case 4:
                tampilkanSlot();
                break;
            case 5:
                tampilkanStatistik();
                break;
            case 6:
                sortKendaraanByPlat();
                break;
            case 0: {
                int keluarOpsi;
                cout << "\nKeluar:\n";
                cout << "1. Simpan data ke file dan keluar\n";
                cout << "2. Hapus data file dan keluar\n";
                cout << "Pilihan: ";
                cin >> keluarOpsi;

                if (keluarOpsi == 1) {
                    simpanLaporanHarian();
                    cout << "Data disimpan. Terima kasih.\n";
                } else if (keluarOpsi == 2) {
                    if (remove("data_parkir.txt") == 0)
                        cout << "File data_parkir.txt berhasil dihapus.\n";
                    else
                        cout << "Gagal menghapus file atau file tidak ditemukan.\n";
                } else {
                    cout << "Pilihan tidak valid. Keluar tanpa simpan atau hapus.\n";
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid.\n";
        }
        system("pause");

    } while (pilihan != 0);

    return 0;
}
