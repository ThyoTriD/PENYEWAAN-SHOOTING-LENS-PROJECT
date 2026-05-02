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
