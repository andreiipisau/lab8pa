#include <stdio.h>

#define V 15
#define INF 9999

int adj[V][V];
int vizitat[V];

int main() {
    FILE *f_in = fopen("graf.csv", "r");
    if (!f_in) return 1;

    int u, v, c;
    while (fscanf(f_in, "%d,%d,%d", &u, &v, &c) == 3) {
        adj[u][v] = c;
        adj[v][u] = c;
    }
    fclose(f_in);

    FILE *f_out = fopen("prim.csv", "w");
    fprintf(f_out, "Sursa,Destinatie,Cost\n");

    vizitat[0] = 1;
    int cost_total = 0, nr_muchii = 0;

    printf("--- Rezultat Prim ---\n");
    while (nr_muchii < V - 1) {
        int min = INF, x = 0, y = 0;
        for (int i = 0; i < V; i++) {
            if (vizitat[i]) {
                for (int j = 0; j < V; j++) {
                    if (!vizitat[j] && adj[i][j] && adj[i][j] < min) {
                        min = adj[i][j];
                        x = i; y = j;
                    }
                }
            }
        }
        printf("Muchie: %d-%d | Cost: %d\n", x, y, adj[x][y]);
        fprintf(f_out, "%d,%d,%d\n", x, y, adj[x][y]);
        cost_total += adj[x][y];
        vizitat[y] = 1;
        nr_muchii++;
    }
    fprintf(f_out, "Total,,%d\n", cost_total);
    fclose(f_out);
    return 0;
}