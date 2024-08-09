#include <stdio.h>    
#include <stdlib.h>   

// Mendefinisikan jumlah node yang ada dalam graph
#define NODE_COUNT 5  // Jumlah node: D, K1, K2, P1, P2

// Struktur untuk merepresentasikan sebuah edge (sisi) dalam graph
struct Edge {
    int src, dest, weight;  // src: node asal, dest: node tujuan, weight: bobot/jarak antara kedua node
};

// Struktur untuk merepresentasikan graph dengan edge-edge (sisi)
struct Graph {
    int nodeCount, edgeCount;  // Jumlah node dan edge dalam graph
    struct Edge* edge;         // Pointer ke array edge (sisi)
};

// Struktur untuk mewakili subset untuk algoritma union-find
struct subset {
    int parent;  // Menyimpan parent dari elemen
    int rank;    // Menyimpan rank (tingkat kedalaman) dari tree subset
};

// Fungsi utilitas untuk membuat graph baru dengan jumlah node dan edge yang ditentukan
struct Graph* createGraph(int nodeCount, int edgeCount) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); // Alokasi memori untuk graph
    graph->nodeCount = nodeCount;  // Mengatur jumlah node
    graph->edgeCount = edgeCount;  // Mengatur jumlah edge
    graph->edge = (struct Edge*) malloc(graph->edgeCount * sizeof(struct Edge)); // Alokasi memori untuk array edge
    return graph;  // Mengembalikan pointer ke graph yang telah dibuat
}

// Fungsi utilitas untuk menemukan set dari elemen i menggunakan teknik path compression
int find(struct subset subsets[], int i) {
    // Jika parent dari i bukan dirinya sendiri, lakukan pencarian rekursif untuk menemukan root
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);  // Path compression
    return subsets[i].parent;  // Mengembalikan root dari set
}

// Fungsi untuk melakukan union (penggabungan) dua set berdasarkan rank
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);  // Temukan root dari set x
    int yroot = find(subsets, y);  // Temukan root dari set y

    // Gabungkan dua set berdasarkan rank
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;  // Jika rank x lebih kecil, jadikan y sebagai parent
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;  // Jika rank y lebih kecil, jadikan x sebagai parent
    else {
        subsets[yroot].parent = xroot;  // Jika rank sama, jadikan x sebagai parent dan naikkan rank x
        subsets[xroot].rank++;
    }
}

// Fungsi untuk membandingkan dua edge berdasarkan weight (bobot)
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;  // Konversi pointer ke tipe Edge
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;  // Mengembalikan selisih bobot (untuk pengurutan ascending)
}

// Fungsi utama untuk membangun Minimum Spanning Tree (MST) menggunakan Kruskal's Algorithm
void KruskalMST(struct Graph* graph) {
    int nodeCount = graph->nodeCount;  // Ambil jumlah node dari graph
    struct Edge result[nodeCount];     // Array untuk menyimpan hasil MST
    int e = 0;  // Inisialisasi variabel indeks untuk result[]
    int i = 0;  // Inisialisasi variabel indeks untuk edge yang diurutkan

    // Mengurutkan semua edge dalam graph berdasarkan bobot menggunakan qsort
    qsort(graph->edge, graph->edgeCount, sizeof(graph->edge[0]), compareEdges);

    // Alokasi memori untuk subset, yang akan digunakan dalam union-find
    struct subset* subsets = (struct subset*) malloc(nodeCount * sizeof(struct subset));

    // Membuat subset untuk setiap node, dengan setiap node menjadi parent dari dirinya sendiri
    int v;
    for (v = 0; v < nodeCount; ++v) {
        subsets[v].parent = v;  // Setiap node menjadi parent dari dirinya sendiri
        subsets[v].rank = 0;    // Inisialisasi rank ke 0
    }

    // Loop melalui semua edge dan pilih edge yang tidak membentuk cycle (lingkaran)
    while (e < nodeCount - 1 && i < graph->edgeCount) {
        struct Edge next_edge = graph->edge[i++];  // Pilih edge berikutnya dari urutan

        int x = find(subsets, next_edge.src);  // Temukan root dari subset node src
        int y = find(subsets, next_edge.dest); // Temukan root dari subset node dest

        // Jika edge ini tidak membentuk cycle, tambahkan ke hasil dan lakukan union
        if (x != y) {
            result[e++] = next_edge;  // Tambahkan edge ke hasil MST
            Union(subsets, x, y);     // Gabungkan kedua subset
        }
    }
	
	// Menampilkan hasil MST (edges yang terpilih) dan total jarak minimum
	printf("Edges dalam MST dengan jarak minimum:\n");
	int minimumCost = 0;  // Inisialisasi variabel untuk total jarak
	for (i = 0; i < e; ++i) {
	    // Mendefinisikan label untuk setiap node agar lebih mudah dipahami
	    char* labels[] = {"D ", "K1", "K2", "P1", "P2"};
	    // Menampilkan setiap edge dalam format: "node1 -- node2 == weight km"
	    printf("%s -- %s == %d km\n", labels[result[i].src], labels[result[i].dest], result[i].weight);
	    minimumCost += result[i].weight;  // Menambahkan bobot ke total jarak
	}
	printf("Total jarak minimum: %d km\n", minimumCost);  // Menampilkan total jarak

    free(subsets);  // Dealokasi memori untuk subset
}

int main() {
    int edgeCount = 7;  // Mendefinisikan jumlah edge dalam graph
    
    struct Graph* graph = createGraph(NODE_COUNT, edgeCount);  // Membuat graph dengan jumlah node dan edge yang ditentukan

    // Mendefinisikan setiap edge dalam graph dengan format (src, dest, weight)
    graph->edge[0].src = 0;  // D-K1
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 30;

    graph->edge[1].src = 0;  // D-K2
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 20;

    graph->edge[2].src = 0;  // D-P1
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 10;

    graph->edge[3].src = 1;  // K1-P1
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 5;

    graph->edge[4].src = 1;  // K1-P2
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 25;

    graph->edge[5].src = 2;  // K2-P1
    graph->edge[5].dest = 3;
    graph->edge[5].weight = 13;

    graph->edge[6].src = 2;  // K2-P2
    graph->edge[6].dest = 4;
    graph->edge[6].weight = 40;

    KruskalMST(graph);  // Memanggil fungsi untuk membangun MST menggunakan Kruskal's Algorithm

    // Dealokasi memori untuk graph setelah digunakan
    free(graph->edge);
    free(graph);

    return 0;  // Mengakhiri program
}

