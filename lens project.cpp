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

void menu1InputInventaris(LinkedList& ll, BST& bst, Stack& stk) {
    if (!loginAdmin()) { pauseEnter(); return; }

    string pilih = "1";
    while (pilih == "1") {
        cout << "\n[MENU INPUT INVENTARIS - NEW ENTRY]\n";
        string id, nama, kat, spek, rak;
        int stok;

        cout << "1. Nama Alat      : "; cin.ignore(); getline(cin, nama);
        cout << "2. Kategori       : "; getline(cin, kat);
        cout << "3. Spesifikasi    : "; getline(cin, spek);
        cout << "4. Lokasi Rak     : "; getline(cin, rak);
        cout << "5. Jumlah Stok    : "; cin >> stok;

        // Generate ID otomatis
        string prefix = "UNK";
        if (kat == "Lens" || kat == "Lensa")   prefix = "LNS";
        else if (kat == "Lighting")             prefix = "LHT";
        else if (kat == "Support")              prefix = "TRP";
        else if (kat == "Camera")               prefix = "CAM";
        else if (kat == "Audio")                prefix = "MIC";
        id = prefix + "-" + to_string(100 + ll.totalItem + 1);

        cout << "\n >> Sedang memproses data ke Linked List...\n";
        cout << " >> Sinkronisasi dengan " << DB_FILE << "...\n";

        Alat* node = ll.insertNode(id, nama, kat, spek, rak, "Tersedia", stok);
        bst.insertAlat(node);
        simpanKeFile(ll);

        string logDesc = nama + " (ID: " + id + ")";
        stk.push(getWaktuSekarang(), "MASUK", logDesc);
        tulisActivityLog(getWaktuSekarang(), "MASUK", logDesc);

        cout << " >> [DATA BERHASIL DITAMBAHKAN]\n";
        cout << "    ID yang ditetapkan: " << id << "\n";

        cout << "\nOpsi:\n";
        cout << "[1] Tambah Data Lagi\n";
        cout << "[K] Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;
        if (pilih == "K" || pilih == "k") break;
    }
}


void menu2Peminjaman(Queue& q, Stack& stk) {
    string pilih;
    do {
        cout << "\n[TRANSAKSI PEMINJAMAN - Queue System]\n";
        cout << "Prinsip: First In First Out (Pelanggan Terlama Dilayani Lebih Dulu)\n\n";
        cout << "DAFTAR ANTREAN SAAT INI:\n";
        q.tampilkan();

        cout << "\nOpsi Operasi:\n";
        cout << "[1] Tambah Antrean Baru (Enqueue)\n";
        cout << "[2] Proses/Layani Antrean Terdepan (Dequeue)\n";
        cout << "[3] Kosongkan Seluruh Antrean (Clear)\n";
        cout << "[K] Kembali ke Menu Utama\n";
        cout << "Pilih Operasi: ";
        cin >> pilih;

        if (pilih == "1") {
            string nama, alat;
            int waktu;
            cout << "Nama Pelanggan  : "; cin.ignore(); getline(cin, nama);
            cout << "Alat yang Dicari: "; getline(cin, alat);
            cout << "Estimasi Waktu (menit): "; cin >> waktu;
            q.enqueue(nama, alat, waktu);
            stk.push(getWaktuSekarang(), "KELUAR", alat + " (Dipinjam oleh: " + nama + ")");
            tulisActivityLog(getWaktuSekarang(), "PEMINJAMAN", nama + " - " + alat);
            cout << "[SUCCESS] Antrean baru ditambahkan.\n";
        } else if (pilih == "2") {
            QueueNode* node = q.dequeue();
            if (node) {
                cout << "[PROSES] Melayani: " << node->namaPelanggan
                     << " | Alat: " << node->alatDicari << "\n";
                stk.push(getWaktuSekarang(), "MASUK",
                         node->alatDicari + " (Kembali dari: " + node->namaPelanggan + ")");
                tulisActivityLog(getWaktuSekarang(), "SELESAI",
                                 node->namaPelanggan + " - " + node->alatDicari);
                delete node;
            } else {
                cout << "[INFO] Antrean kosong, tidak ada yang diproses.\n";
            }
        } else if (pilih == "3") {
            q.clearQueue();
            cout << "[SUCCESS] Seluruh antrean telah dikosongkan.\n";
        }
    } while (pilih != "K" && pilih != "k");
}


void menu3LogAktivitas(Stack& stk) {
    string pilih;
    do {
        cout << "\n[LOG AKTIVITAS TERAKHIR] - Top of Stack\n";
        stk.tampilkan();
        cout << "[U] Undo Aktivitas Terakhir | [K] Kembali ke Menu\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == "U" || pilih == "u") {
            StackNode* node = stk.pop();
            if (node) {
                cout << "[UNDO] Aktivitas dihapus: ["
                     << node->waktu << "] " << node->jenis
                     << " : " << node->deskripsi << "\n";
                delete node;
            } else {
                cout << "[INFO] Stack kosong, tidak ada yang di-undo.\n";
            }
        }
    } while (pilih != "K" && pilih != "k");
}


void menu4PencarianCepat(BST& bst, LinkedList& ll) {
    string pilih;
    do {
        cout << "\n[PENCARIAN CEPAT - Binary Search Tree]\n";
        cout << "Cari Nama Alat: \"";
        string cari;
        cin.ignore();
        getline(cin, cari);
        cout << "\"\n";

        Alat* hasil = bst.cariByNama(cari);
        if (hasil) {
            cout << "\n[SEARCH RESULT - Binary Search Tree Path Found]\n";
            cout << string(60, '-') << "\n";
            cout << left << setw(18) << "ID Alat"     << ": " << hasil->id         << "\n";
            cout << left << setw(18) << "Nama"        << ": " << hasil->nama       << "\n";
            cout << left << setw(18) << "Spesifikasi" << ": " << hasil->spesifikasi<< "\n";
            cout << left << setw(18) << "Status"      << ": " << hasil->status     << "\n";
            cout << left << setw(18) << "Stok"        << ": " << hasil->stok       << "\n";
            cout << left << setw(18) << "Lokasi Rak"  << ": " << hasil->lokasiRak  << "\n";
            cout << string(60, '-') << "\n";
            cout << "Tekan 'E' untuk Edit Spesifikasi | Tekan 'ESC' untuk Kembali\n";
            cout << "Pilih: ";
            cin >> pilih;
            if (pilih == "E" || pilih == "e") {
                string spekBaru;
                cout << "Spesifikasi Baru: ";
                cin.ignore();
                getline(cin, spekBaru);
                hasil->spesifikasi = spekBaru;
                cout << "[SUCCESS] Spesifikasi berhasil diperbarui.\n";
            }
        } else {
            // Fallback: cari dengan partial match di linked list
            bool found = false;
            Alat* curr = ll.head;
            while (curr) {
                if (curr->nama.find(cari) != string::npos ||
                    curr->id.find(cari)   != string::npos) {
                    cout << "\n[SEARCH RESULT - Linear Search]\n";
                    cout << string(60, '-') << "\n";
                    cout << left << setw(18) << "ID Alat"     << ": " << curr->id          << "\n";
                    cout << left << setw(18) << "Nama"        << ": " << curr->nama        << "\n";
                    cout << left << setw(18) << "Spesifikasi" << ": " << curr->spesifikasi << "\n";
                    cout << left << setw(18) << "Status"      << ": " << curr->status      << "\n";
                    cout << left << setw(18) << "Stok"        << ": " << curr->stok        << "\n";
                    cout << left << setw(18) << "Lokasi Rak"  << ": " << curr->lokasiRak   << "\n";
                    cout << string(60, '-') << "\n";
                    found = true;
                    break;
                }
                curr = curr->next;
            }
            if (!found)
                cout << "[NOT FOUND] Alat dengan nama \"" << cari << "\" tidak ditemukan.\n";
        }

        cout << "\nCari lagi? [Y/N]: ";
        cin >> pilih;
    } while (pilih == "Y" || pilih == "y");
}


void menu5LaporanKerusakan(LinkedList& ll, Stack& stk) {
    
    cout << "\n[DAFTAR UNIT PERLU SERVIS]\n";
    cout << string(60, '-') << "\n";

    ifstream fileIn(SERVICE_FILE);
    bool adaData = false;
    if (fileIn.is_open()) {
        string line;
        int no = 1;
        while (getline(fileIn, line)) {
            if (!line.empty()) {
                cout << no++ << ". " << line << "\n";
                adaData = true;
            }
        }
        fileIn.close();
    }
    if (!adaData)
        cout << "  (Belum ada laporan kerusakan)\n";
    cout << string(60, '-') << "\n";

    char c;
    cout << "Input Unit Baru untuk Servis? (y/n): ";
    cin >> c;

    if (c == 'y' || c == 'Y') {
        string idAlat, deskripsi;
        cout << "Masukkan ID Alat: ";
        cin >> idAlat;
        cin.ignore();
        cout << "Masukkan Deskripsi Kerusakan: ";
        getline(cin, deskripsi);

        // Validasi ID
        Alat* cek = ll.cariById(idAlat);
        if (!cek) {
            cout << "[WARNING] ID tidak ditemukan di inventaris, tetap dicatat.\n";
        }

        tulisServiceLog(idAlat, deskripsi);
        stk.push(getWaktuSekarang(), "UPDATE",
                 idAlat + " (Laporan: " + deskripsi + ")");
        cout << "[SISTEM]: Data berhasil ditulis ke '" << SERVICE_FILE << "'.\n";
    }

    // Opsi hapus laporan (DELETE operation)
    cout << "\nHapus semua laporan lama? (y/n): ";
    cin >> c;
    if (c == 'y' || c == 'Y') {
        ofstream fileOut(SERVICE_FILE, ios::trunc);
        fileOut.close();
        cout << "[SUCCESS] Semua laporan dihapus.\n";
    }

    pauseEnter();
}

// 
void menu6ManajemenStok(LinkedList& ll, BST& bst, Stack& stk) {
    string pilih;
    do {
        cout << "\n[MANAJEMEN STOK - Linked List View]\n";
        ll.tampilkan();

        cout << "\nOpsi Pengurutan (Sorting):\n";
        cout << "[A] Urutkan berdasarkan Nama (A-Z)\n";
        cout << "[B] Urutkan berdasarkan ID Alat\n";
        cout << "[C] Tambah Stok Baru (Insert Node)\n";
        cout << "[D] Hapus Aset (Delete Node)\n";
        cout << "[K] Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == "A" || pilih == "a") {
            ll.sortByNama();
            cout << "[SUCCESS] Diurutkan berdasarkan Nama (A-Z).\n";
            simpanKeFile(ll);
        } else if (pilih == "B" || pilih == "b") {
            ll.sortById();
            cout << "[SUCCESS] Diurutkan berdasarkan ID Alat.\n";
            simpanKeFile(ll);
        } else if (pilih == "C" || pilih == "c") {
            if (!loginAdmin()) { pauseEnter(); continue; }
            string id, nama, kat, spek, rak;
            int stok;
            cout << "Nama Alat      : "; cin.ignore(); getline(cin, nama);
            cout << "Kategori       : "; getline(cin, kat);
            cout << "Spesifikasi    : "; getline(cin, spek);
            cout << "Lokasi Rak     : "; getline(cin, rak);
            cout << "Jumlah Stok    : "; cin >> stok;

            string prefix = "UNK";
            if (kat == "Lens" || kat == "Lensa") prefix = "LNS";
            else if (kat == "Lighting")          prefix = "LHT";
            else if (kat == "Support")           prefix = "TRP";
            else if (kat == "Camera")            prefix = "CAM";
            else if (kat == "Audio")             prefix = "MIC";
            id = prefix + "-" + to_string(100 + ll.totalItem + 1);

            Alat* node = ll.insertNode(id, nama, kat, spek, rak, "Tersedia", stok);
            bst.insertAlat(node);
            simpanKeFile(ll);
            stk.push(getWaktuSekarang(), "MASUK", nama + " (ID: " + id + ")");
            tulisActivityLog(getWaktuSekarang(), "MASUK", nama);
            cout << "[SUCCESS] Stok baru ditambahkan dengan ID: " << id << "\n";
        } else if (pilih == "D" || pilih == "d") {
            if (!loginAdmin()) { pauseEnter(); continue; }
            if (ll.head == nullptr) {
                cout << "[ERROR 404]: Gagal menghapus data.\n";
                cout << "Penyebab: Pointer 'Head' menunjuk ke NULL (Data Kosong).\n";
                cout << "Silakan isi data terlebih dahulu melalui Menu 1.\n";
                pauseEnter();
                continue;
            }
            string id;
            cout << "Masukkan ID Alat yang akan dihapus: ";
            cin >> id;
            bool ok = ll.hapusById(id);
            if (ok) {
                simpanKeFile(ll);
                stk.push(getWaktuSekarang(), "DELETE", "ID: " + id);
                tulisActivityLog(getWaktuSekarang(), "DELETE", "ID: " + id);
                cout << "[SUCCESS] Aset dengan ID " << id << " berhasil dihapus.\n";
            } else {
                cout << "[ERROR] ID " << id << " tidak ditemukan.\n";
            }
        }
    } while (pilih != "K" && pilih != "k");
}


void tampilkanInfoSistem(LinkedList& ll, Queue& q) {
    int keluar = 0;
    int maintenance = 0;
    Alat* curr = ll.head;
    while (curr) {
        if (curr->status == "Keluar") keluar++;
        curr = curr->next;
    }

    ifstream sf(SERVICE_FILE);
    string ln;
    while (getline(sf, ln)) if (!ln.empty()) maintenance++;
    sf.close();

    int kapasitas = (ll.totalItem > 0) ? (ll.totalItem * 100 / (ll.totalItem + 5)) : 0;

    cout << "[INFO SYSTEM]\n";
    cout << ">> Total Aset Digital    : " << ll.totalItem << " Item\n";
    cout << ">> Alat Sedang Keluar    : " << q.size << " Item (Check Queue)\n";
    cout << ">> Status Penyimpanan    : " << kapasitas << "% Kapasitas Terpakai\n";
    cout << ">> Peringatan            : " << maintenance << " Alat Perlu Maintenance\n";
}
