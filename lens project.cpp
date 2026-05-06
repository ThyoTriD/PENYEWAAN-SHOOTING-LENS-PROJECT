#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

//blm 1 fng

struct Alat {
    string id;
    string nama;
    string kategori;
    string spesifikasi;
    string lokasiRak;
    string status;
    int    stok;
    Alat*  next;   
};

struct QueueNode {
    string namaPelanggan;
    string alatDicari;
    int    waktuTunggu; 
    QueueNode* next;
};

struct StackNode {
    string waktu;
    string jenis;   
    string deskripsi;
    StackNode* next;
};

class LinkedList {
public:
    Alat* head;
    int   totalItem;

    LinkedList() : head(nullptr), totalItem(0) {}

    
    Alat* insertNode(string id, string nama, string kategori,
                     string spesifikasi, string lokasiRak,
                     string status, int stok) {
        Alat* baru = new Alat();
        baru->id           = id;
        baru->nama         = nama;
        baru->kategori     = kategori;
        baru->spesifikasi  = spesifikasi;
        baru->lokasiRak    = lokasiRak;
        baru->status       = status;
        baru->stok         = stok;
        baru->next         = nullptr;

        if (head == nullptr) {
            head = baru;
        } else {
            Alat* curr = head;
            while (curr->next != nullptr)
                curr = curr->next;
            curr->next = baru;
        }
        totalItem++;
        return baru;
    }

Alat* cariById(string id) {
        Alat* curr = head;
        while (curr != nullptr) {
            if (curr->id == id) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    bool hapusById(string id) {
        if (head == nullptr) return false;
        if (head->id == id) {
            Alat* temp = head;
            head = head->next;
            delete temp;
            totalItem--;
            return true;
        }
        Alat* curr = head;
        while (curr->next != nullptr) {
            if (curr->next->id == id) {
                Alat* temp = curr->next;
                curr->next = temp->next;
                delete temp;
                totalItem--;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

 
    void sortByNama() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            Alat* curr = head;
            while (curr->next != nullptr) {
                if (curr->nama > curr->next->nama) {
               
                    swap(curr->id,          curr->next->id);
                    swap(curr->nama,        curr->next->nama);
                    swap(curr->kategori,    curr->next->kategori);
                    swap(curr->spesifikasi, curr->next->spesifikasi);
                    swap(curr->lokasiRak,   curr->next->lokasiRak);
                    swap(curr->status,      curr->next->status);
                    swap(curr->stok,        curr->next->stok);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }
void sortById() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            Alat* curr = head;
            while (curr->next != nullptr) {
                if (curr->id > curr->next->id) {
                    swap(curr->id,          curr->next->id);
                    swap(curr->nama,        curr->next->nama);
                    swap(curr->kategori,    curr->next->kategori);
                    swap(curr->spesifikasi, curr->next->spesifikasi);
                    swap(curr->lokasiRak,   curr->next->lokasiRak);
                    swap(curr->status,      curr->next->status);
                    swap(curr->stok,        curr->next->stok);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }


    void tampilkan() {
        cout << string(74, '-') << "\n";
        cout << left
             << setw(10) << "ID Alat"
             << "| " << setw(30) << "Nama Alat"
             << "| " << setw(10) << "Kategori"
             << "| " << setw(10) << "Status"
             << "| Stok\n";
        cout << string(74, '-') << "\n";
        Alat* curr = head;
        while (curr != nullptr) {
            cout << left
                 << setw(10) << curr->id
                 << "| " << setw(30) << curr->nama
                 << "| " << setw(10) << curr->kategori
                 << "| " << setw(10) << curr->status
                 << "| " << curr->stok << "\n";
            curr = curr->next;
        }
        cout << string(74, '-') << "\n";
        cout << "Total Item dalam Linked List: " << totalItem << " Item\n";
    }

    ~LinkedList() {
        Alat* curr = head;
        while (curr) {
            Alat* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }
};
