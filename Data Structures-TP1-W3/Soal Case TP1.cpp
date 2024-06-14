/*

NIM - Nama  : 2702350592 - Ihsan Amri Muyassar
Kelas       : JCCA
Mata Kuliah : Data Structures

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

struct node {
    int employeeID;
    char namaLengkap[31];
    char tempatLahir[31];
    char tanggalLahir[11];
    char jabatan[51];
    struct node *next;
};

struct node *head = NULL, *tail = NULL;

// Fungsi untuk clear screen
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi untuk memvalidasi string hanya berisi huruf dan spasi
int isAlphaSpace(const char *str) {
    while (*str) {
        if (!isalpha(*str) && *str != ' ') {
            return 0;  // Bukan huruf atau spasi
        }
        str++;
    }
    return 1;  // Hanya huruf dan spasi
}

// Fungsi untuk memvalidasi string hanya berisi angka
int isNum(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;  // Bukan angka
        }
        str++;
    }
    return 1;  // Hanya angka
}

// Fungsi untuk membuat node baru
struct node *create_newnode(int employeeID, char namaLengkap[], char tempatLahir[], char tanggalLahir[], char jabatan[]) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->employeeID = employeeID;
    strcpy(new_node->namaLengkap, namaLengkap);
    strcpy(new_node->tempatLahir, tempatLahir);
    strcpy(new_node->tanggalLahir, tanggalLahir);
    strcpy(new_node->jabatan, jabatan);
    new_node->next = NULL;

    return new_node;
}

// Fungsi untuk menambahkan node ke belakang linked list
void insert_back(int employeeID, char namaLengkap[], char tempatLahir[], char tanggalLahir[], char jabatan[]) {
    struct node *new_node = create_newnode(employeeID, namaLengkap, tempatLahir, tanggalLahir, jabatan);

    if (head == NULL) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

// Fungsi untuk mengurutkan linked list secara ascending berdasarkan employeeID
void sort_ascending() {
    struct node *curr, *ncurr;
    int tempID;
    char tempNamaLengkap[31], tempTempatLahir[31], tempTanggalLahir[11], tempJabatan[51];

    if (head != NULL) {
        for (curr = head; curr->next != NULL; curr = curr->next) {
            for (ncurr = curr->next; ncurr != NULL; ncurr = ncurr->next) {
                if (curr->employeeID > ncurr->employeeID) {
                    // Swap employeeID
                    tempID = curr->employeeID;
                    curr->employeeID = ncurr->employeeID;
                    ncurr->employeeID = tempID;

                    // Swap namaLengkap
                    strcpy(tempNamaLengkap, curr->namaLengkap);
                    strcpy(curr->namaLengkap, ncurr->namaLengkap);
                    strcpy(ncurr->namaLengkap, tempNamaLengkap);

                    // Swap tempatLahir
                    strcpy(tempTempatLahir, curr->tempatLahir);
                    strcpy(curr->tempatLahir, ncurr->tempatLahir);
                    strcpy(ncurr->tempatLahir, tempTempatLahir);

                    // Swap tanggalLahir
                    strcpy(tempTanggalLahir, curr->tanggalLahir);
                    strcpy(curr->tanggalLahir, ncurr->tanggalLahir);
                    strcpy(ncurr->tanggalLahir, tempTanggalLahir);

                    // Swap jabatan
                    strcpy(tempJabatan, curr->jabatan);
                    strcpy(curr->jabatan, ncurr->jabatan);
                    strcpy(ncurr->jabatan, tempJabatan);
                }
            }
        }
    } else {
        printf("------------------\nLinked list kosong\n------------------\n");
    }
}

// Fungsi untuk memvalidasi format tanggal lahir
int validateTanggalLahir(char *tanggalLahir) {
    // Panjang string harus 10 karakter
    if (strlen(tanggalLahir) != 10) {
        return 0;
    }

    // Format harus DD-MM-YYYY
    if (tanggalLahir[2] != '-' || tanggalLahir[5] != '-') {
        return 0;
    }

    // Memvalidasi setiap karakter apakah digit atau bukan
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue;  // Melewati '-' agar sesuai format
        }
        if (!isdigit(tanggalLahir[i])) {
            return 0;  // Bukan digit
        }
    }

    return 1;  // Format sesuai
}

// Fungsi untuk menghapus node berdasarkan employeeID
void delete_employeeID(int employeeID) {
    struct node *curr = head;
    struct node *pcurr = head;

    // Mencari node dengan employeeID yang sesuai
    while (curr != NULL && curr->employeeID != employeeID) {
        pcurr = curr;
        curr = curr->next;
    }

    // Jika employeeID ditemukan
    if (curr != NULL) {
        // Jika node yang ditemukan adalah node pertama
        if (curr == head) {
            // Jika linked list memiliki lebih dari satu node
            if (tail != head) {
                head = curr->next;
                free(curr);
            } else {
                // Jika linked list hanya memiliki satu node
                head = tail = NULL;
                free(curr);
            }
        } else {
            // Jika node yang ditemukan bukan node pertama
            pcurr->next = curr->next;
            // Jika node yang dihapus adalah node terakhir
            if (curr == tail) {
                tail = pcurr;
            }
            free(curr);
        }
        printf("\n----------------------------------------\nData karyawan dengan ID %d sudah dihapus\n----------------------------------------\n", employeeID);
    } else {
        printf("\n------------------------------------------\nData karyawan dengan ID %d tidak ditemukan\n------------------------------------------\n", employeeID);
    }
}

// Fungsi untuk menghapus semua node dalam linked list
void delete_list() {
    struct node *curr = head;
    struct node *next_node;

    while (curr != NULL) {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    }

    head = tail = NULL;
    printf("------------------------\nSemua data sudah dihapus\n------------------------\n");
}

// Fungsi untuk menampilkan semua node dalam linked list
void display() {
    struct node *curr = head;
    
    while (curr != NULL) {
    	printf("========================================\n");
        printf("Employee ID   : %d\n", curr->employeeID);
        printf("Nama Lengkap  : %s\n", curr->namaLengkap);
        printf("Tempat Lahir  : %s\n", curr->tempatLahir);
        printf("Tanggal Lahir : %s\n", curr->tanggalLahir);
        printf("Jabatan       : %s\n", curr->jabatan);
        printf("----------------------------------------\n");
        curr = curr->next;
    }
    if (head == NULL) {
        printf("");
    } else {
        printf("Akhir dari list karyawan\n");
        printf("========================================\n");
    }
}

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    printf("\n===============================\n");
    printf("|   PROGRAM DATA PEGAWAI      |\n");
    printf("===============================\n");
    printf("1. Tambah Data Pegawai\n");
    printf("2. Hapus Data Pegawai\n");
    printf("3. Hapus Semua Data Pegawai\n");
    printf("4. Tampilkan Semua Data Pegawai\n");
    printf("5. Keluar\n");
    printf("===============================\n");
}

int main() {
    int pilihan;
    int employeeID;
    int dataCount = 0;
    char pilihanStr[100];
    char namaLengkap[100];
    char tempatLahir[100];
    char tanggalLahir[100];
    char jabatan[100];
    char employeeIDStr[100];

    do {
        clearScreen();
        tampilkanMenu();
        
        do {
		    printf("Masukkan pilihan: ");
		    scanf("%1s", pilihanStr);
		    getchar();
		
		    // Validasi panjang string
		    if (strlen(pilihanStr) != 1) {
		        printf("\n----------------------------------\n");
		        printf("Pilihan tidak valid. Masukkan angka.\n");
		        printf("----------------------------------\n");
		    } else {
		        pilihan = atoi(pilihanStr); // Konversi string ke integer
		        if (pilihan < 1 || pilihan > 5) {
		            printf("\n--------------------------------------\n");
		            printf("Pilihan tidak valid. Harus antara 1-5.\n");
		            printf("--------------------------------------\n\n");
		        }
		    }
		} while (strlen(pilihanStr) != 1 || (pilihan < 1 || pilihan > 5));
		
		printf("===============================\n\n");

        switch (pilihan) {
            case 1:
                if (dataCount < 5) {
                    do {
                        printf("Masukkan Employee ID (maks. 5 angka): ");
                        scanf(" %[^\n]", employeeIDStr);
                        getchar();
                        if (!isNum(employeeIDStr) || strlen(employeeIDStr) > 5) {
                            printf("\n---------------------------------------------------------------------\n");
							printf("Employee ID tidak valid. Tolong input ID yang sesuai (maks. 5 angka).\n");
							printf("---------------------------------------------------------------------\n\n");
                        }
                    } while (!isNum(employeeIDStr) || strlen(employeeIDStr) > 5);
                    employeeID = atoi(employeeIDStr);  // Konversi string ke integer
                    
                    do {
					    printf("Masukkan Nama Lengkap (maks. 30 karakter): ");
					    scanf(" %[^\n]", namaLengkap);
					    getchar();
					
					    // Validasi Nama Lengkap
					    if (!isAlphaSpace(namaLengkap) || strlen(namaLengkap) > 30) {
					    	printf("\n-----------------------------------------------------------------------------------\n");
					        printf("Nama Lengkap tidak valid. Harus berisi hanya huruf dan spasi, maksimal 30 karakter.\n");
					        printf("-----------------------------------------------------------------------------------\n\n");
					    }
					} while (!isAlphaSpace(namaLengkap) || strlen(namaLengkap) > 30);

			
					do {
					    printf("Masukkan Tempat Lahir (maks. 30 karakter): ");
					    scanf(" %[^\n]", tempatLahir);
					    getchar();
					
					    // Validasi Tempat Lahir
					    if (!isAlphaSpace(tempatLahir) || strlen(tempatLahir) > 30) {
					        printf("\n-----------------------------------------------------------------------------------\n");
					        printf("Tempat Lahir tidak valid. Harus berisi hanya huruf dan spasi, maksimal 30 karakter.\n");
					        printf("-----------------------------------------------------------------------------------\n\n");
					    }
					} while (!isAlphaSpace(tempatLahir) || strlen(tempatLahir) > 30);
					
			        do {
			            printf("Masukkan Tanggal Lahir (format DD-MM-YYYY): ");
			            scanf(" %[^\n]", tanggalLahir);
			            getchar();
			            if (!validateTanggalLahir(tanggalLahir)) {
			                printf("\n---------------------------------------------------------------------------------------\n");
							printf("Format Tanggal Lahir tidak valid. Tolong input tanggal yang sesuai (format DD-MM-YYYY).\n");
							printf("---------------------------------------------------------------------------------------\n\n");
			            }
			        } while (!validateTanggalLahir(tanggalLahir));

                    do {
					    printf("Masukkan Jabatan (maks. 50 karakter): ");
					    scanf(" %[^\n]", jabatan);
					    getchar();
					
					    // Validasi Jabatan
					    if (strlen(jabatan) > 50) {
					        printf("\n------------------------------------------------\n");
					        printf("Jabatan tidak valid. Harus maksimal 50 karakter.\n");
					        printf("------------------------------------------------\n\n");
					    }
					} while (strlen(jabatan) > 50);

                    insert_back(employeeID, namaLengkap, tempatLahir, tanggalLahir, jabatan);
                    dataCount++;
                    printf("\n-------------------------\nData berhasil ditambahkan\n-------------------------\n");
                } else {
                    printf("\n-------------------------------\nMaksimum data tercapai (5 data)\n-------------------------------\n");
                }
                printf("\nTekan enter untuk melanjutkan...");
                getchar();
                break;

            case 2:
                printf("Masukkan Employee ID yang ingin dihapus: ");
                scanf("%d", &employeeID);
                getchar();
                delete_employeeID(employeeID);
                printf("\nTekan enter untuk melanjutkan...");
                getchar();
                break;

            case 3:
                delete_list();
                dataCount = 0;
                printf("\nTekan enter untuk melanjutkan...");
                getchar();
                break;

            case 4:
                sort_ascending();
                display();
                printf("\nTekan enter untuk melanjutkan...");
                getchar();
                break;

            case 5:
                printf("Keluar dari program\n");
                break;

            default:
                printf("---------------------------------------\nPilihan tidak valid. Silakan coba lagi.\n---------------------------------------\n");
                printf("\nTekan enter untuk melanjutkan...");
                getchar();
                break;
        }
    } while (pilihan != 5);

    return 0;
}

