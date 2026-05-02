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
