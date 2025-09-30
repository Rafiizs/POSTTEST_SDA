#include <iostream>
#include <string>
using namespace std;

struct Gear {
    int id;
    string nama;
    string kategori;
    int jumlah;
    Gear* next;
    Gear* prev;
};


const int JUMLAH_AWAL = 95;
const int POSISI_SISIP = (5==0?2:5+1);

Gear* head = nullptr;
Gear* tail = nullptr;
int autoID = 1;

Gear* buatGear(const string& n, const string& k) {
    Gear* g = new Gear;
    g->id = autoID++;
    g->nama = n;
    g->kategori = k;
    g->jumlah = JUMLAH_AWAL;
    g->next = nullptr;
    g->prev = nullptr;
    return g;
}

void tambahGear() {
    string n, k;
    cout << "Nama Gear : "; cin.ignore(); getline(cin, n);
    cout << "Kategori  : "; getline(cin, k);

    Gear* g = buatGear(n,k);
    if (!head) {
        head = tail = g;
    } else {
        tail->next = g;
        g->prev = tail;
        tail = g;
    }
    cout << ">> Gear \"" << n << "\" berhasil ditambahkan (" << JUMLAH_AWAL << " unit)\n";
}

void sisipGear() {
    string n,k;
    cout << "Nama Gear : "; cin.ignore(); getline(cin, n);
    cout << "Kategori  : "; getline(cin, k);
    Gear* g = buatGear(n,k);

    if (!head) {
        head = tail = g;
        cout << ">> Gear disisip di posisi awal (karena gudang kosong)\n";
        return;
    }

    if (POSISI_SISIP <= 1) {
        g->next = head;
        head->prev = g;
        head = g;
    } else {
        Gear* p = head;
        int pos = 1;
        while (p->next && pos < POSISI_SISIP-1) {
            p = p->next; pos++;
        }
        g->next = p->next;
        g->prev = p;
        if (p->next) p->next->prev = g;
        else tail = g;
        p->next = g;
    }
    cout << ">> Gear disisip otomatis di posisi ke-" << POSISI_SISIP << "\n";
}

void hapusTerakhir() {
    if (!tail) { cout << "Gudang kosong!\n"; return; }
    cout << ">> Buang: " << tail->nama << "\n";
    Gear* del = tail;
    if (tail->prev) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        head = tail = nullptr;
    }
    delete del;
}

void gunakanGear() {
    if (!head) { cout << "Gudang kosong!\n"; return; }
    string cari;
    cout << "Nama gear yang digunakan: "; cin.ignore(); getline(cin, cari);

    Gear* p = head;
    while (p && p->nama != cari) p = p->next;

    if (!p) { cout << "Gear tidak ditemukan!\n"; return; }
    p->jumlah--;
    cout << ">> Menggunakan 1 " << p->nama << ". Sisa: " << p->jumlah << "\n";
    if (p->jumlah <= 0) {
        cout << ">> Persediaan " << p->nama << " habis, node dihapus.\n";
        if (p == head && p == tail) {
            head = tail = nullptr;
        } else if (p == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (p == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        delete p;
    }
}

void tampilDepan() {
    if (!head) { cout << "Gudang kosong!\n"; return; }
    cout << "\n==== DAFTAR GEAR (Depan -> Belakang) ====\n";
    for (Gear* p = head; p; p = p->next)
        cout << p->id << ". " << p->nama
             << " | Kategori: " << p->kategori
             << " | Jumlah: " << p->jumlah << "\n";
}

void tampilBelakang() {
    if (!tail) { cout << "Gudang kosong!\n"; return; }
    cout << "\n==== DAFTAR GEAR (Belakang -> Depan) ====\n";
    for (Gear* p = tail; p; p = p->prev)
        cout << p->id << ". " << p->nama
             << " | Kategori: " << p->kategori
             << " | Jumlah: " << p->jumlah << "\n";
}

void cariGear() {
    if (!head) { cout << "Gudang kosong!\n"; return; }
    string target;
    cout << "Masukkan nama gear yang dicari: ";
    cin.ignore(); getline(cin, target);

    Gear* p = head;
    while (p) {
        if (p->nama == target) {
            cout << "\n=== DETAIL GEAR ===\n";
            cout << "ID       : " << p->id << endl;
            cout << "Nama     : " << p->nama << endl;
            cout << "Kategori : " << p->kategori << endl;
            cout << "Jumlah   : " << p->jumlah << endl;
            return;
        }
        p = p->next;
    }
    cout << "Gear tidak ditemukan!\n";
}

int main() {
    int pilih;
    do {
        cout << "\n####################################################\n";
        cout << "  ZOMBIE APOCALYPSE SURVIVAL INVENTORY SYSTEM (DLL)\n";
        cout << "  Survivor : Muhammad Rafii Zaidan S. | NIM 2409106095\n";
        cout << "####################################################\n";
        cout << " 1. Tambah Gear Baru (Add Last)\n";
        cout << " 2. Sisipkan Gear (posisi otomatis)\n";
        cout << " 3. Buang Gear Terakhir\n";
        cout << " 4. Gunakan Gear\n";
        cout << " 5. Lihat Gudang (Depan -> Belakang)\n";
        cout << " 6. Lihat Gudang (Belakang -> Depan)\n";
        cout << " 7. Cari Gear (berdasarkan Nama)\n";
        cout << " 0. Keluar\n";
        cout << "----------------------------------------------------\n";
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahGear(); break;
            case 2: sisipGear(); break;
            case 3: hapusTerakhir(); break;
            case 4: gunakanGear(); break;
            case 5: tampilDepan(); break;
            case 6: tampilBelakang(); break;
            case 7: cariGear(); break;
            case 0: cout << "Tetap waspada, para zombie tidak tidur!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);
    return 0;
}