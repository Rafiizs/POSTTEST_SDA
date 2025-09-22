#include <iostream>
#include <string>
using namespace std;


struct Gear {
    string nama;
    string kategori;
    int jumlah;
    Gear* next;
};


const int JUMLAH_AWAL = 95;
const int POSISI_SISIP = (5==0?2:5+1);

Gear* head = nullptr;


Gear* buatGear(const string& n, const string& k) {
    return new Gear{n, k, JUMLAH_AWAL, nullptr};
}


void tambahGear() {
    string n,k;
    cout << "Nama Gear : "; cin.ignore(); getline(cin, n);
    cout << "Kategori  : "; getline(cin, k);

    Gear* g = buatGear(n,k);
    if (!head) head = g;
    else {
        Gear* p = head;
        while (p->next) p = p->next;
        p->next = g;
    }
    cout << ">> Gear \"" << n << "\" berhasil ditambahkan (" << JUMLAH_AWAL << " unit)\n";
}

void sisipGear() {
    string n,k;
    cout << "Nama Gear : "; cin.ignore(); getline(cin, n);
    cout << "Kategori  : "; getline(cin, k);
    Gear* g = buatGear(n,k);

    if (!head || POSISI_SISIP <= 1) {
        g->next = head;
        head = g;
    } else {
        Gear* p = head;
        int pos = 1;
        while (p->next && pos < POSISI_SISIP - 1) { p = p->next; pos++; }
        g->next = p->next;
        p->next = g;
    }
    cout << ">> Gear disisip otomatis di posisi ke-" << POSISI_SISIP << "\n";
}

void hapusTerakhir() {
    if (!head) { cout << "Gudang kosong!\n"; return; }
    if (!head->next) { cout << ">> Buang: " << head->nama << "\n"; delete head; head=nullptr; return; }

    Gear* p = head;
    while (p->next->next) p = p->next;
    cout << ">> Buang: " << p->next->nama << "\n";
    delete p->next;
    p->next = nullptr;
}

void gunakanGear() {
    if (!head) { cout << "Gudang kosong!\n"; return; }
    string cari;
    cout << "Nama gear yang digunakan: "; cin.ignore(); getline(cin, cari);
    Gear *p = head, *prev = nullptr;
    while (p && p->nama != cari) { prev = p; p = p->next; }

    if (!p) { cout << "Gear tidak ditemukan!\n"; return; }
    p->jumlah--;
    cout << ">> Menggunakan 1 " << p->nama << ". Sisa: " << p->jumlah << "\n";
    if (p->jumlah <= 0) {
        cout << ">> Persediaan " << p->nama << " habis, node dihapus.\n";
        if (!prev) head = p->next;
        else prev->next = p->next;
        delete p;
    }
}

void tampilkanGudang() {
    if (!head) { cout << "Gudang kosong!\n"; return; }
    cout << "\n==== DAFTAR GEAR PERTAHANAN ====\n";
    int i = 1;
    for (Gear* p = head; p; p = p->next, ++i)
        cout << i << ". " << p->nama
             << " | Kategori: " << p->kategori
             << " | Jumlah: " << p->jumlah << "\n";
}


int main() {
    int pilih;
    do {
        cout << "\n####################################################\n";
        cout << "  ZOMBIE APOCALYPSE SURVIVAL INVENTORY SYSTEM\n";
        cout << "  Survivor : Muhammad Rafii Zaidan S. | NIM 2409106095\n";
        cout << "####################################################\n";
        cout << " 1. Tambah Gear Baru\n";
        cout << " 2. Sisipkan Gear (posisi otomatis)\n";
        cout << " 3. Buang Gear Terakhir\n";
        cout << " 4. Gunakan Gear\n";
        cout << " 5. Lihat Gudang Gear\n";
        cout << " 0. Keluar\n";
        cout << "----------------------------------------------------\n";
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahGear(); break;
            case 2: sisipGear(); break;
            case 3: hapusTerakhir(); break;
            case 4: gunakanGear(); break;
            case 5: tampilkanGudang(); break;
            case 0: cout << "Tetap waspada, para zombie tidak tidur!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);
    return 0;
}