#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *prev;
    int stok;
    float harga;
    char nama[50];
    struct node *next;
};

struct node *head = NULL;

struct node* createNode(char* nama, int stok, float harga) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->nama, nama);
    newNode->stok = stok;
    newNode->harga = harga;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

struct node* tambahBarang(struct node *head, char* nama, int stok, float harga) {
    struct node* newNode = createNode(nama, stok, harga);
    if (head == NULL) {
        head = newNode;
    } else {
        struct node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = newNode;
        newNode->prev = ptr;
    }
    printf("\nBarang %s dengan stok %d dan harga Rp%.2f berhasil ditambahkan!\n\n", nama, stok, harga);
    return head;
}

struct node* hapusBarang(struct node *head, char* nama) {
    struct node* ptr = head;
    while (ptr != NULL) {
        if (strcmp(ptr->nama, nama) == 0) {
            if (ptr->prev != NULL) {
                ptr->prev->next = ptr->next;
            } else {
                head = ptr->next;
            }
            if (ptr->next != NULL) {
                ptr->next->prev = ptr->prev;
            }
            free(ptr);
            printf("Barang %s telah dihapus.\n\n", nama);
            return head;
        }
        ptr = ptr->next;
    }
    printf("Barang %s tidak ditemukan.\n\n", nama);
    return head;
}

struct node* updateBarang(struct node *head, char* nama, int stok, float harga) {
    struct node* ptr = head;
    while (ptr != NULL) {
        if (strcmp(ptr->nama, nama) == 0) {
            ptr->stok = stok;
            ptr->harga = harga;
            printf("Stok dan harga barang %s telah diperbarui menjadi %d dan %.2f.\n\n", nama, stok, harga);
            return head;
        }
        ptr = ptr->next;
    }
    printf("Barang %s tidak ditemukan.\n\n", nama);
    return head;
}

void tampilkanSemuaBarang(struct node *head) {
    struct node* ptr = head;
    if (ptr == NULL) {
        printf("Tidak ada barang yang tersedia.\n\n");
    } else {
        printf("| %-30s | %-10s | %-10s |\n", "Nama", "Stok", "Harga Satuan");
        printf("--------------------------------------------------------------\n");
        while (ptr != NULL) {
            printf("| %-30s | %-10d | %-12.2f |\n", ptr->nama, ptr->stok, ptr->harga);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void cariBarang(struct node *head, char* nama) {
    struct node* ptr = head;
    while (ptr != NULL) {
        if (strcmp(ptr->nama, nama) == 0) {
            printf("\nBarang ditemukan!\nNama: %s, Stok: %d, Harga: %.2f\n\n", ptr->nama, ptr->stok, ptr->harga);
            return;
        }
        ptr = ptr->next;
    }
    printf("\nBarang %s tidak ditemukan.\n\n", nama);
}

void tampilkanMenu() {
    printf("\n==========================\n");
    printf("|   PROGRAM TOKO BARANG  |\n");
    printf("==========================\n");
    printf("1. Tambah Barang Baru\n");
    printf("2. Hapus Barang\n");
    printf("3. Update Stok dan Harga Barang\n");
    printf("4. Tampilkan Semua Barang\n");
    printf("5. Cari Barang\n");
    printf("6. Keluar\n");
    printf("==========================\n");
}

// Fungsi untuk memvalidasi input integer
int inputInt(const char* prompt) {
    int value;
    int result;
    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);
        while(getchar() != '\n');
        if (result == 1) {
            break;
        } else {
            printf("Input tidak valid. Masukkan angka.\n");
        }
    }
    return value;
}

// Fungsi untuk memvalidasi input float
float inputFloat(const char* prompt) {
    float value;
    int result;
    while (1) {
        printf("%s", prompt);
        result = scanf("%f", &value);
        while(getchar() != '\n');
        if (result == 1) {
            break;
        } else {
            printf("Input tidak valid. Masukkan angka desimal.\n");
        }
    }
    return value;
}

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int pilihan;
    char nama[50];
    int stok;
    float harga;

    do {
        clearScreen();
        tampilkanMenu();
        pilihan = inputInt("Masukkan pilihan: ");

        printf("==========================\n\n");

        switch (pilihan) {
            case 1:
                printf("Masukkan nama barang: ");
                scanf(" %[^\n]", nama); getchar();
                stok = inputInt("Masukkan stok: ");
                harga = inputFloat("Masukkan harga per barang: ");
                head = tambahBarang(head, nama, stok, harga);
                break;
            case 2:
                printf("Masukkan nama barang yang akan dihapus: ");
                scanf(" %[^\n]", nama); getchar();
                head = hapusBarang(head, nama);
                break;
            case 3:
                printf("Masukkan nama barang yang akan diupdate: ");
                scanf(" %[^\n]", nama); getchar();
                stok = inputInt("Masukkan stok baru: ");
                harga = inputFloat("Masukkan harga baru: ");
                head = updateBarang(head, nama, stok, harga);
                break;
            case 4:
                tampilkanSemuaBarang(head);
                break;
            case 5:
                printf("Masukkan nama barang yang dicari: ");
                scanf(" %[^\n]", nama); getchar();
                cariBarang(head, nama);
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n\n");
                break;
        }

        if (pilihan != 6) {
            printf("Tekan Enter untuk melanjutkan...");
            while(getchar() != '\n');
        }
    } while (pilihan != 6);

    return 0;
}
