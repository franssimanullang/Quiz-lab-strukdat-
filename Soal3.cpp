#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>

using namespace std;

const int V = 6; //Jumlah vertex: A,B,C,D,E,F
const int INF = 99999; //Representasi bobot tak terhingga (tidak ada jalur langsung)

// Konversi karakter vertex ('A'-'F') ke indeks (0-5)
int charToIndex(char c) {
    return c - 'A';
}

// Konversi indeks (0-5) ke karakter vertex ('A'-'F')
char indexToChar(int i) {
    return 'A' + i;
}

// Fungsi untuk menampilkan Adjacency Matrix
void tampilkanGraph(int graph[V][V]) {
    cout << "\n=========================================\n";
    cout << "        ADJACENCY MATRIX KAMPUS          \n";
    cout << "=========================================\n\t";
    for (int i = 0; i < V; i++) cout << indexToChar(i) << "\t";
    cout << "\n-----------------------------------------\n";
    for (int i = 0; i < V; i++) {
        cout << indexToChar(i) << " |\t";
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == INF) cout << "-";
            else cout << graph[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
    cout << "=========================================\n\n";
}

// 1. Algoritma BFS (Breadth-First Search)
void bfs(int graph[V][V], char startChar) {
    int start = charToIndex(startChar);
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Penelusuran BFS (Mulai dari " << startChar << "): ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << indexToChar(curr) << " ";

        for (int i = 0; i < V; i++) {
            if (graph[curr][i] != INF && graph[curr][i] > 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << "\n";
}

// 2. Algoritma DFS (Depth-First Search) - Rekursif helper
void dfsUtil(int graph[V][V], int curr, vector<bool>& visited) {
    visited[curr] = true;
    cout << indexToChar(curr) << " ";

    for (int i = 0; i < V; i++) {
        if (graph[curr][i] != INF && graph[curr][i] > 0 && !visited[i]) {
            dfsUtil(graph, i, visited);
        }
    }
}

void dfs(int graph[V][V], char startChar) {
    int start = charToIndex(startChar);
    vector<bool> visited(V, false);
    cout << "Penelusuran DFS (Mulai dari " << startChar << "): ";
    dfsUtil(graph, start, visited);
    cout << "\n";
}

// 3. Algoritma Dijkstra untuk mencari rute terpendek
void dijkstra(int graph[V][V], char startChar, char endChar) {
    int start = charToIndex(startChar);
    int end = charToIndex(endChar);

    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    vector<bool> sptSet(V, false);

    dist[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int minVal = INF, u = -1;

        // Cari vertex dengan jarak minimum yang belum diproses
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] < minVal) {
                minVal = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Tampilkan hasil rute dan jarak
    cout << "\n-----------------------------------------\n";
    cout << "HASIL DIJKSTRA DARI " << startChar << " KE " << endChar << "\n";
    cout << "-----------------------------------------\n";
    if (dist[end] == INF) {
        cout << "Tidak ada rute yang tersedia dari " << startChar << " ke " << endChar << ".\n";
    } else {
        cout << "Total Jarak Terpendek : " << dist[end] << "\n";
        cout << "Rute yang Dilalui      : ";

        vector<char> path;
        int curr = end;
        while (curr != -1) {
            path.push_back(indexToChar(curr));
            curr = parent[curr];
        }

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << "\n";
    }
    cout << "-----------------------------------------\n";
}

int main() {
    // Inisialisasi Adjacency Matrix dengan bobot sesuai tabel soal
    int graph[V][V];

    // Set semua nilai awal ke INF (tidak terhubung) dan 0 untuk diagonal utama
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }

    // Mengisi bobot berdasarkan tabel soal
    // (A-B:4, A-C:2, B-C:1, B-D:5, B-E:3, C-D:8, C-E:6, D-E:2, D-F:4, E-F:3)
    int edges[][3] = {
        {'A', 'B', 4}, {'A', 'C', 2},
        {'B', 'C', 1}, {'B', 'D', 5}, {'B', 'E', 3},
        {'C', 'D', 8}, {'C', 'E', 6},
        {'D', 'E', 2}, {'D', 'F', 4},
        {'E', 'F', 3}
    };

    for (auto& edge : edges) {
        int u = charToIndex(edge[0]);
        int v = charToIndex(edge[1]);
        int weight = edge[2];
        graph[u][v] = weight;
        graph[v][u] = weight; // Graf tak berarah (undirected graph)
    }

    // Tampilkan representasi grafik
    tampilkanGraph(graph);

    // Pengujian Penelusuran Graf (BFS & DFS)
    cout << "=== UJI COBA PENELUSURAN GRAF ===\n";
    char startTraversal = 'A';
    bfs(graph, startTraversal);
    dfs(graph, startTraversal);

    // Fitur interaktif bagi pengguna untuk memilih vertex awal dan tujuan pencarian rute terpendek
    cout << "\n=== SISTEM PENCARIAN RUTE TERPENDEK (DIJKSTRA) ===\n";
    char awal, tujuan;
    cout << "Masukkan Vertex Awal (A-F): ";
    cin >> awal;
    cout << "Masukkan Vertex Tujuan (A-F): ";
    cin >> tujuan;

    awal = toupper(awal);
    tujuan = toupper(tujuan);

    if (awal >= 'A' && awal <= 'F' && tujuan >= 'A' && tujuan <= 'F') {
        dijkstra(graph, awal, tujuan);
    } else {
        cout << "[Error] Masukkan vertex dengan huruf antara A sampai F!\n";
    }

    return 0;
}
