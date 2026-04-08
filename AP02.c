#include <stdio.h>
#include <stdlib.h>

#define MAX 100000 //10^5

double V[MAX];
long long cont = 0;

//conta quantos pares (i, j) existem (i < j e V[i] > 2 * V[j]) 
void merge(int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    double E[MAX], D[MAX];
    for(int i = 0; i < n1; i++) E[i] = V[esq + i];
    for(int i = 0; i < n2; i++) D[i] = V[meio + 1 + i];
    
    int t = 0;
    for(int i = 0; i < n2; i++) {
        while(t < n1 && E[t] <= 2 * D[i]) t++;
        cont += n1 - t;
    }
    
    int ii = 0, j = 0, k = esq;
    while(ii < n1 && j < n2) {
        if(E[ii] <= D[j]) {
            V[k++] = E[ii++];
        } else {
            V[k++] = D[j++];
        }
    }
    while(ii < n1) V[k++] = E[ii++];
    while(j < n2) V[k++] = D[j++];
}

//merge sort
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
    for(int i = 0; i < N; i++){ 
        scanf("%lf", &V[i]);
    }
    cont = 0;
    mergeSort(0, N - 1);
    printf("%lld\n", cont);
    for(int i = 0; i < N; i++) {
        printf("%.2f ", V[i]);
    }
    printf("\n");
    return 0;
}
