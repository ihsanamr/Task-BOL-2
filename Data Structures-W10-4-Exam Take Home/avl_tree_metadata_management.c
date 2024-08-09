#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struktur metadata file
typedef struct {
    char filename[100];
    int size;
    time_t created_at;
    time_t modified_at;
    char file_type[10];
    char permissions[5];
    char file_path[200];
} Metadata;

// Node AVL Tree
typedef struct Node {
    Metadata data;
    struct Node *left, *right;
    int height;
} Node;

// Mendapatkan tinggi node
int getHeight(Node *node) {
    return (node == NULL) ? 0 : node->height;
}

// Mendapatkan nilai maksimum dari dua angka
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Membuat node baru dengan metadata yang diberikan
Node* createNode(Metadata data) {
    Node* node = (Node*)malloc(sizeof(Node)); // Alokasikan memori untuk node
    node->data = data;  // Salin data metadata ke node
    node->left = node->right = NULL;  // Inisialisasi anak kiri dan kanan node sebagai NULL
    node->height = 1;  // Set tinggi node sebagai 1
    return node;  // Kembalikan pointer ke node yang baru dibuat
}

// Rotasi kanan pada node yang diberikan
Node* rightRotate(Node* y) {
    Node* x = y->left;  // Ambil anak kiri dari node y
    Node* T2 = x->right;  // Simpan subtree kanan dari x

    // Lakukan rotasi
    x->right = y;  // Set anak kanan x menjadi y
    y->left = T2;  // Set anak kiri y menjadi subtree kanan dari x

    // Perbarui tinggi node
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;  // Kembalikan root baru
}

// Rotasi kiri pada node yang diberikan
Node* leftRotate(Node* x) {
    Node* y = x->right;  // Ambil anak kanan dari node x
    Node* T2 = y->left;  // Simpan subtree kiri dari y

    // Lakukan rotasi
    y->left = x;  // Set anak kiri y menjadi x
    x->right = T2;  // Set anak kanan x menjadi subtree kiri dari y

    // Perbarui tinggi node
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;  // Kembalikan root baru
}

// Mendapatkan faktor keseimbangan dari node
int getBalance(Node* node) {
    return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Fungsi insert ke AVL Tree
Node* insert(Node* node, Metadata data) {
    // Jika node kosong, buat node baru dengan metadata yang diberikan
    if (node == NULL) return createNode(data);

    // Jika filename yang akan dimasukkan lebih kecil dari filename pada node ini
    if (strcmp(data.filename, node->data.filename) < 0)
        // Insert ke subtree kiri
        node->left = insert(node->left, data);
    // Jika filename yang akan dimasukkan lebih besar dari filename pada node ini
    else if (strcmp(data.filename, node->data.filename) > 0)
        // Insert ke subtree kanan
        node->right = insert(node->right, data);
    else
        // Filename sudah ada di tree, tidak mengizinkan duplikasi
        return node;

    // Update tinggi node saat ini
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Hitung balance factor untuk memastikan apakah node ini sudah balance
    int balance = getBalance(node);

    // Jika balance factor lebih dari 1, artinya subtree kiri lebih tinggi
    // Periksa apakah subtree kiri sudah lebih berat dari subtree kiri kiri
    if (balance > 1 && strcmp(data.filename, node->left->data.filename) < 0)
        // Rotasi kanan untuk menyeimbangkan
        return rightRotate(node);

    // Jika balance factor kurang dari -1, artinya subtree kanan lebih tinggi
    // Periksa apakah subtree kanan sudah lebih berat dari subtree kanan kanan
    if (balance < -1 && strcmp(data.filename, node->right->data.filename) > 0)
        // Rotasi kiri untuk menyeimbangkan
        return leftRotate(node);

    // Jika balance factor lebih dari 1 dan data.filename lebih besar dari filename pada node kiri
    if (balance > 1 && strcmp(data.filename, node->left->data.filename) > 0) {
        // Lakukan rotasi kiri pada subtree kiri
        node->left = leftRotate(node->left);
        // Lakukan rotasi kanan pada node saat ini
        return rightRotate(node);
    }

    // Jika balance factor kurang dari -1 dan data.filename lebih kecil dari filename pada node kanan
    if (balance < -1 && strcmp(data.filename, node->right->data.filename) < 0) {
        // Lakukan rotasi kanan pada subtree kanan
        node->right = rightRotate(node->right);
        // Lakukan rotasi kiri pada node saat ini
        return leftRotate(node);
    }

    // Kembalikan node yang telah seimbang
    return node;
}

// Fungsi untuk mencari node dengan nama file tertentu di AVL Tree
Node* search(Node* root, const char* filename) {
    // Jika pohon kosong (root == NULL) atau node saat ini memiliki nama file yang cocok
    if (root == NULL || strcmp(root->data.filename, filename) == 0)
        return root;  // Kembalikan node yang ditemukan (NULL jika tidak ditemukan)

    // Jika nama file yang dicari lebih kecil dari nama file di node saat ini
    if (strcmp(filename, root->data.filename) < 0)
        // Cari di subtree kiri (karena nama file yang dicari lebih kecil, harus berada di kiri)
        return search(root->left, filename);
    
    // Jika nama file yang dicari lebih besar dari nama file di node saat ini
    // Cari di subtree kanan (karena nama file yang dicari lebih besar, harus berada di kanan)
    return search(root->right, filename);
}

// Fungsi untuk menghapus node dari AVL Tree
Node* deleteNode(Node* root, const char* filename) {
    // Langkah 1: Jika pohon kosong, kembalikan root NULL
    if (root == NULL) return root;

    // Langkah 2: Jika nama file yang akan dihapus lebih kecil dari root->data.filename,
    // maka hapus dari subtree kiri
    if (strcmp(filename, root->data.filename) < 0)
        root->left = deleteNode(root->left, filename);
    
    // Langkah 3: Jika nama file yang akan dihapus lebih besar dari root->data.filename,
    // maka hapus dari subtree kanan
    else if (strcmp(filename, root->data.filename) > 0)
        root->right = deleteNode(root->right, filename);
    
    // Langkah 4: Jika nama file yang akan dihapus sama dengan root->data.filename
    else {
        // Kasus 1: Node dengan satu atau tidak ada anak
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right; // Ambil anak yang ada (jika ada)
            
            // Jika node tidak memiliki anak, maka set node ke NULL
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp; // Salin data dari anak ke node yang akan dihapus
            
            free(temp); // Hapus node yang telah dipindahkan
        } 
        // Kasus 2: Node dengan dua anak
        else {
            Node* temp = root->right;
            // Temukan node terkecil di subtree kanan (successor)
            while (temp->left != NULL)
                temp = temp->left;
            
            // Salin data dari successor ke node saat ini
            root->data = temp->data;
            // Hapus successor dari subtree kanan
            root->right = deleteNode(root->right, temp->data.filename);
        }
    }

    // Jika pohon menjadi kosong setelah penghapusan
    if (root == NULL) return root;

    // Langkah 5: Perbarui tinggi node saat ini
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    
    // Langkah 6: Hitung keseimbangan node saat ini
    int balance = getBalance(root);

    // Langkah 7: Jika node tidak seimbang, lakukan rotasi untuk menyeimbangkan pohon
    
    // Kasus 1: Jika keseimbangan lebih dari 1 dan anak kiri tidak seimbang ke kiri
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    // Kasus 2: Jika keseimbangan lebih dari 1 dan anak kiri tidak seimbang ke kanan
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left); // Lakukan rotasi kiri pada anak kiri
        return rightRotate(root); // Lakukan rotasi kanan pada node saat ini
    }
    
    // Kasus 3: Jika keseimbangan kurang dari -1 dan anak kanan tidak seimbang ke kanan
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    // Kasus 4: Jika keseimbangan kurang dari -1 dan anak kanan tidak seimbang ke kiri
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right); // Lakukan rotasi kanan pada anak kanan
        return leftRotate(root); // Lakukan rotasi kiri pada node saat ini
    }

    // Kembalikan root yang telah diperbarui
    return root;
}

// Fungsi untuk mencetak metadata file
void printMetadata(Metadata data) {
    printf("Filename: %s\n", data.filename);
    printf("Size: %d bytes\n", data.size);
    printf("Created At: %s", ctime(&data.created_at));
    printf("Modified At: %s", ctime(&data.modified_at));
    printf("File Type: %s\n", data.file_type);
    printf("Permissions: %s\n", data.permissions);
    printf("File Path: %s\n\n", data.file_path);
}

// Fungsi untuk mencetak semua metadata dalam AVL Tree
void printAllMetadata(Node* root) {
    if (root == NULL) {
        // Jika pohon kosong
        return;
    }
    
    if (root->left != NULL) {
        printAllMetadata(root->left);  // Cetak subtree kiri
    }
    
    printMetadata(root->data);  // Cetak data node saat ini
    
    if (root->right != NULL) {
        printAllMetadata(root->right);  // Cetak subtree kanan
    }
}

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    printf("\n===========================\n");
    printf("|   FILE METADATA SYSTEM  |\n");
    printf("===========================\n");
    printf("1. Tambah Metadata File\n");
    printf("2. Hapus Metadata File\n");
    printf("3. Cari Metadata File\n");
    printf("4. Tampilkan Semua Metadata\n");
    printf("5. Keluar\n");
    printf("==========================\n");
}

// Fungsi untuk mendapatkan input string
void inputString(const char* prompt, char* buffer, int size) {
    printf("%s", prompt);  // Tampilkan prompt
    
    // Membaca input string hingga newline
    scanf(" %[^\n]", buffer);
    
    // Menghapus newline yang tersisa jika ada
    getchar();
}

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");  // Bersihkan layar untuk Windows
    #else
        system("clear");  // Bersihkan layar untuk sistem berbasis Unix
    #endif
}

// Fungsi utama
int main() {
    Node *root = NULL;  // Root dari AVL Tree
    int choice;  // Pilihan menu
    char filename[100];  // Nama file untuk operasi
    Metadata data;  // Data metadata file
	char strChoice[10];  // Buffer untuk menyimpan input pilihan menu

    do {
        clearScreen();  // Bersihkan layar
        tampilkanMenu();  // Tampilkan menu
        
        do {
            printf("Masukkan pilihan: ");
            scanf(" %[^\n]", strChoice);
            getchar();  // Menghapus newline di akhir input
            
            // Validasi panjang string
            if (strlen(strChoice) != 1) {
                printf("\n------------------------------------\n");
                printf("Pilihan tidak valid. Masukkan angka.\n");
                printf("------------------------------------\n\n");
            } else {
                choice = atoi(strChoice); // Konversi string ke integer
                if (choice < 1 || choice > 5) {
                    printf("\n--------------------------------------\n");
                    printf("Pilihan tidak valid. Harus antara 1-5.\n");
                    printf("--------------------------------------\n\n");
                }
            }
        } while (strlen(strChoice) != 1 || (choice < 1 || choice > 5));  // Validasi input menu
        
        printf("--------------------------\n");

        switch (choice) {
            case 1:
                // Tambah Metadata File
                inputString("Masukkan nama file: ", data.filename, sizeof(data.filename));
                printf("Masukkan ukuran file (dalam byte): ");
                scanf("%d", &data.size);
                getchar();
                data.created_at = time(NULL);  // Set waktu dibuat saat ini
                data.modified_at = time(NULL);  // Set waktu dimodifikasi saat ini
                inputString("Masukkan tipe file: ", data.file_type, sizeof(data.file_type));
                inputString("Masukkan izin akses file (e.g., rw): ", data.permissions, sizeof(data.permissions));
                inputString("Masukkan path file: ", data.file_path, sizeof(data.file_path));
                root = insert(root, data);  // Masukkan metadata ke AVL Tree
                printf("\nMetadata file berhasil ditambahkan!\n");
                break;
            case 2:
                // Hapus Metadata File
                inputString("Masukkan nama file yang akan dihapus: ", filename, sizeof(filename));
                root = deleteNode(root, filename);  // Hapus metadata dari AVL Tree
                printf("\nMetadata file berhasil dihapus (jika ada)!\n");
                break;
            case 3:
                // Cari Metadata File
                inputString("Masukkan nama file yang dicari: ", filename, sizeof(filename));
                Node* result = search(root, filename);  // Cari metadata di AVL Tree
                if (result != NULL) {
                    printf("\nFile ditemukan:\n\n");
                    printMetadata(result->data);  // Tampilkan metadata jika ditemukan
                } else {
                    printf("\nFile tidak ditemukan!\n");
                }
                break;
            case 4:
                // Tampilkan Semua Metadata
			    if (root == NULL) {
			        printf("Tidak ada metadata file yang tersedia.\n");
			    } else {
			        printf("Menampilkan semua metadata file:\n\n");
			        printAllMetadata(root);  // Cetak semua metadata di AVL Tree
			    }
                break;
            case 5:
                // Keluar dari program
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
        
        if (choice != 5) {
            printf("\nTekan Enter untuk melanjutkan...");
            while(getchar() != '\n');  // Tunggu input Enter untuk melanjutkan
        }
    } while (choice != 5);  // Ulangi hingga pengguna memilih keluar

    return 0;  // Keluar dari program
}
