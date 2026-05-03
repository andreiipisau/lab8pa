#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 15
#define MAX_EDGES 100

typedef struct {
    int u, v, cost;
} Muchie;

Muchie muchii[MAX_EDGES];
int parinte[MAX_NODES];
int nr_muchii = 0;

int gaseste(int i) {
    while (parinte[i] != i)
        i = parinte[i];
    return i;
}

void uneste(int i, int j) {
    int a = gaseste(i);
    int b = gaseste(j);
    parinte[a] = b;
}

int compara(const void* a, const void* b) {
    return ((Muchie*)a)->cost - ((Muchie*)b)->cost;
}

int main() {
    FILE *f_in = fopen("graf.csv", "r");
    if (!f_in) return 1;

    while (fscanf(f_in, "%d,%d,%d", &muchii[nr_muchii].u, &muchii[nr_muchii].v, &muchii[nr_muchii].cost) == 3) {
        nr_muchii++;
    }
    fclose(f_in);

    for (int i = 0; i < MAX_NODES; i++) parinte[i] = i;
    qsort(muchii, nr_muchii, sizeof(Muchie), compara);

    FILE *f_out = fopen("kruskal.csv", "w");
    fprintf(f_out, "Sursa,Destinatie,Cost\n");

    int cost_total = 0, selectate = 0;
    printf("--- Rezultat Kruskal ---\n");
    for (int i = 0; i < nr_muchii; i++) {
        if (gaseste(muchii[i].u) != gaseste(muchii[i].v)) {
            printf("Muchie: %d-%d | Cost: %d\n", muchii[i].u, muchii[i].v, muchii[i].cost);
            fprintf(f_out, "%d,%d,%d\n", muchii[i].u, muchii[i].v, muchii[i].cost);
            cost_total += muchii[i].cost;
            uneste(muchii[i].u, muchii[i].v);
            selectate++;
        }
        if (selectate == MAX_NODES - 1) break;
    }
    fprintf(f_out, "Total,,%d\n", cost_total);
    fclose(f_out);
    return 0;
}