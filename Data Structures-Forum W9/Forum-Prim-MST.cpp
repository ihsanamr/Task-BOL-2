#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

// Fungsi untuk menemukan vertex dengan nilai kunci minimum
int minKey(int key[], int mstSet[], int vertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Fungsi untuk menampilkan MST yang telah dibangun
void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int totalWeight = 0; // Variabel untuk menghitung total bobot MST

    printf("\nEdge \tBobot\n");
    for (int i = 1; i < vertices; i++) {
        int weight = graph[i][parent[i]];
        totalWeight += weight; // Menambahkan bobot edge ke totalWeight
        printf("%d - %d \t%d\n", parent[i], i, weight);
    }
    
    printf("Total Bobot MST: %d\n", totalWeight); // Menampilkan total bobot MST
}

// Fungsi untuk mengimplementasikan algoritma Prim
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int parent[MAX_VERTICES]; // Array untuk menyimpan struktur MST
    int key[MAX_VERTICES];    // Nilai kunci untuk memilih edge dengan bobot minimum
    int mstSet[MAX_VERTICES]; // Menandai vertex yang sudah termasuk dalam MST

    // Inisialisasi nilai kunci sebagai INFINITY dan mstSet[] sebagai false
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Memulai dengan vertex pertama
    key[0] = 0; // Set nilai kunci 0 untuk vertex pertama
    parent[0] = -1; // Vertex pertama menjadi root MST

    // MST akan memiliki vertices-1 edge
    for (int count = 0; count < vertices - 1; count++) {
        // Pilih vertex dengan nilai kunci terkecil yang belum termasuk dalam MST
        int u = minKey(key, mstSet, vertices);

        // Tandai vertex yang dipilih sebagai bagian dari MST
        mstSet[u] = 1;

        // Perbarui nilai kunci dan parent untuk vertex tetangga
        for (int v = 0; v < vertices; v++) {
            // graph[u][v] non-zero hanya untuk vertex tetangga dari u
            // mstSet[v] false jika vertex v belum termasuk dalam MST
            // Perbarui kunci jika bobot edge graph[u][v] lebih kecil dari kunci vertex v
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;   // Set parent[v] ke u, karena edge (u, v) adalah edge dengan bobot terkecil
                key[v] = graph[u][v]; // Perbarui nilai kunci vertex v dengan bobot edge (u, v)
            }
        }
    }

    // Tampilkan MST yang telah dibangun serta total bobot MST
    printMST(parent, graph, vertices);
}

int main() {
    int vertices;

    // Input jumlah vertex
    printf("Masukkan jumlah vertex dalam graf: ");
    scanf("%d", &vertices);

    // Validasi jumlah vertex
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Jumlah vertex yang dimasukkan tidak valid. Program dihentikan...\n");
        return 1;
    }

    int graph[MAX_VERTICES][MAX_VERTICES];

    // Input matriks adjacency yang merepresentasikan graf
    printf("\nMasukkan bobot untuk setiap edge antara vertex!\n");
    printf("Note: Jika tidak ada edge yang menghubungkan dua vertex, masukkan 0.\n\n");

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                printf("Bobot edge dari vertex %d ke vertex %d: ", i, j);
                scanf("%d", &graph[i][j]);
            } else {
                printf("Bobot edge dari vertex %d ke vertex %d: ", i, j);
                scanf("%d", &graph[i][j]);
            }
        }
    }

    // Jalankan algoritma Prim untuk menemukan MST
    primMST(graph, vertices);

    return 0;
}

