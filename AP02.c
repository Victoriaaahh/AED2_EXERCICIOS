#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int V[MAX];
long long cont = 0;

void merge(int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int *E = (int*) malloc(n1 * sizeof(int));
    int *D = (int*) malloc(n2 * sizeof(int));

    for(int i = 0; i < n1; i++) E[i] = V[esq + i];
    for(int i = 0; i < n2; i++) D[i] = V[meio + 1 + i];

    //contagem dos pares
    int j = 0;
    for(int i = 0; i < n1; i++) {
        while(j < n2 && E[i] > 2 * D[j]) {
            j++;
        }
        cont += j;
    }

    int i = 0;
    j = 0;
    int k = esq;

    while(i < n1 && j < n2) {
        if(E[i] <= D[j]) {
            V[k++] = E[i++];
        } else {
            V[k++] = D[j++];
        }
    }

    while(i < n1) V[k++] = E[i++];
    while(j < n2) V[k++] = D[j++];

    free(E);
    free(D);
}

void mergeSort(int esq, int dir) {
    if(esq < dir) {
        int meio = esq + (dir - esq) / 2;
        mergeSort(esq, meio);
        mergeSort(meio + 1, dir);
        merge(esq, meio, dir);
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }

    cont = 0;
    mergeSort(0, N - 1);

    printf("%lld\n", cont);

    for(int i = 0; i < N; i++) {
        printf("%d", V[i]);
        if(i < N - 1) printf(" ");
    }
    printf("\n");

    return 0;
}