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

class BST {
public:
    BSTNode* root;
    BST() : root(nullptr) {}

    BSTNode* insert(BSTNode* node, Alat* data) {
        if (node == nullptr) {
            BSTNode* baru = new BSTNode();
            baru->data  = data;
            baru->left  = nullptr;
            baru->right = nullptr;
            return baru;
        }
        if (data->nama < node->data->nama)
            node->left  = insert(node->left,  data);
        else
            node->right = insert(node->right, data);
        return node;
    }

    void insertAlat(Alat* data) {
        root = insert(root, data);
    }

    // Cari berdasarkan nama (Binary Search Tree path)
    Alat* search(BSTNode* node, string namaTarget) {
        if (node == nullptr) return nullptr;
        if (node->data->nama == namaTarget) return node->data;
        if (namaTarget < node->data->nama)
            return search(node->left,  namaTarget);
        else
            return search(node->right, namaTarget);
    }

    Alat* cariByNama(string nama) {
        return search(root, nama);
    }

    void hapusBST(BSTNode* node) {
        if (!node) return;
        hapusBST(node->left);
        hapusBST(node->right);
        delete node;
    }

    ~BST() { hapusBST(root); }
};


class Queue {
public:
    QueueNode* front;
    QueueNode* rear;
    int        size;

    Queue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(string pelanggan, string alat, int waktu) {
        QueueNode* baru = new QueueNode();
        baru->namaPelanggan = pelanggan;
        baru->alatDicari    = alat;
        baru->waktuTunggu   = waktu;
        baru->next          = nullptr;

        if (rear == nullptr) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear       = baru;
        }
        size++;
    }

    QueueNode* dequeue() {
        if (front == nullptr) return nullptr;
        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        size--;
        return temp;
    }

    void clearQueue() {
        while (front != nullptr) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        size = 0;
    }

    void tampilkan() {
        if (front == nullptr) {
            cout << "  (Antrean kosong)\n";
            return;
        }
        cout << string(74, '-') << "\n";
        cout << left
             << setw(5)  << "No."
             << "| " << setw(18) << "Nama Pelanggan"
             << "| " << setw(22) << "Alat yang Dicari"
             << "| Waktu Tunggu\n";
        cout << string(74, '-') << "\n";

        QueueNode* curr = front;
        int no = 1;
        while (curr != nullptr) {
            string posisi = "";
            if (curr == front) posisi = " (FRONT)";
            if (curr == rear  && curr != front) posisi = " (REAR)";
            cout << left
                 << setw(5)  << (to_string(no) + ".")
                 << "| " << setw(18) << curr->namaPelanggan
                 << "| " << setw(22) << curr->alatDicari
                 << "| " << curr->waktuTunggu << " Menit" << posisi << "\n";
            curr = curr->next;
            no++;
        }
        cout << string(74, '-') << "\n";
        cout << "Total Antrean: " << size << " Orang\n";
    }

    ~Queue() { clearQueue(); }
};


class Stack {
public:
    StackNode* top;
    int        size;

    Stack() : top(nullptr), size(0) {}

    void push(string waktu, string jenis, string deskripsi) {
        StackNode* baru = new StackNode();
        baru->waktu      = waktu;
        baru->jenis      = jenis;
        baru->deskripsi  = deskripsi;
        baru->next       = top;
        top              = baru;
        size++;
    }

    StackNode* pop() {
        if (top == nullptr) return nullptr;
        StackNode* temp = top;
        top = top->next;
        size--;
        return temp;
    }

    void tampilkan() {
        if (top == nullptr) {
            cout << "  (Log kosong)\n";
            return;
        }
        cout << string(60, '-') << "\n";
        StackNode* curr = top;
        int tampil = 0;
        while (curr != nullptr && tampil < 5) {
            cout << "[" << curr->waktu << "] "
                 << left << setw(8) << curr->jenis
                 << ": " << curr->deskripsi << "\n";
            curr = curr->next;
            tampil++;
        }
        if (curr != nullptr)
            cout << "[Yesterday] ...\n";
        cout << string(60, '-') << "\n";
    }

    ~Stack() {
        while (top) {
            StackNode* tmp = top->next;
            delete top;
            top = tmp;
        }
    }
};


string getWaktuSekarang() {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%H:%M", t);
    return string(buf);
}

void pauseEnter() {
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void cetakHeader() {
    cout << "============================================================\n";
    cout << "     SYSTEM INFORMASI INVENTARIS - LENS PROJECT 2026\n";
    cout << "============================================================\n";
}


void simpanKeFile(LinkedList& ll) {
    ofstream file(DB_FILE);
    if (!file.is_open()) {
        cout << "[ERROR] Gagal membuka file database!\n";
        return;
    }
    Alat* curr = ll.head;
    while (curr != nullptr) {
        file << curr->id       << "|"
             << curr->nama     << "|"
             << curr->kategori << "|"
             << curr->spesifikasi << "|"
             << curr->lokasiRak   << "|"
             << curr->status      << "|"
             << curr->stok        << "\n";
        curr = curr->next;
    }
    file.close();
}

void muatDariFile(LinkedList& ll, BST& bst) {
    ifstream file(DB_FILE);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, nama, kat, spek, rak, status, stokStr;
        getline(ss, id,     '|');
        getline(ss, nama,   '|');
        getline(ss, kat,    '|');
        getline(ss, spek,   '|');
        getline(ss, rak,    '|');
        getline(ss, status, '|');
        getline(ss, stokStr,'|');
        int stok = stoi(stokStr);
        Alat* node = ll.insertNode(id, nama, kat, spek, rak, status, stok);
        bst.insertAlat(node);
    }
    file.close();
}

void tulisServiceLog(string idAlat, string deskripsi) {
    ofstream file(SERVICE_FILE, ios::app);
    if (!file.is_open()) {
        cout << "[ERROR] Gagal membuka service_log.txt!\n";
        return;
    }
    time_t now = time(nullptr);
    string waktu = ctime(&now);
    waktu.pop_back();
    file << "[" << waktu << "] ID: " << idAlat
         << " | Masalah: " << deskripsi << "\n";
    file.close();
}

void tulisActivityLog(string waktu, string jenis, string deskripsi) {
    ofstream file(LOG_FILE, ios::app);
    if (!file.is_open()) return;
    file << "[" << waktu << "] " << jenis << " : " << deskripsi << "\n";
    file.close();
}

bool loginAdmin() {
    cout << "\n[SISTEM KEAMANAN ADMIN]\n";
    cout << string(60, '-') << "\n";
    cout << "Peringatan: Area ini memerlukan hak akses khusus.\n";
    cout << "Masukkan Password Admin: ";
    string pass;
    cin >> pass;
    cout << "(User mengetik: " << pass << ")\n\n";

    if (pass == ADMIN_PASSWORD) {
        cout << "[SUCCESS] Login Berhasil. Selamat Datang, Admin.\n";
        cout << string(60, '-') << "\n";
        return true;
    } else {
        cout << "[ERROR] Password yang Anda masukkan SALAH.\n";
        cout << "Akses Ditolak. Sesi Anda telah dihentikan (Log Out).\n";
        cout << "Kembali ke Menu Utama...\n";
        cout << string(60, '-') << "\n";
        cout << "(Sistem otomatis menampilkan kembali Tampilan Umum)\n";
        return false;
    }
}
