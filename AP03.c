#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int gravidade;
} Paciente;

//troca começa em 0
long long swap = 0;

//prioridade
int prioridade(Paciente a, Paciente b) {
    if (a.gravidade > b.gravidade) return 1;
    if (a.gravidade < b.gravidade) return 0;
    return a.id < b.id;
}

// swap
void trocar(Paciente *A, int i, int j) {
    if (i == j) return;

    if (A[i].id == A[j].id && A[i].gravidade == A[j].gravidade)
        return;

    Paciente temp = A[i];
    A[i] = A[j];
    A[j] = temp;

    swap++;
}

// mediana 
void mediana(Paciente *A, int p, int r) {
    int meio = p + (r - p) / 2;

    if (prioridade(A[meio], A[p]))
        trocar(A, meio, p);

    if (prioridade(A[r], A[p]))
        trocar(A, r, p);

    if (prioridade(A[r], A[meio]))
        trocar(A, r, meio);

    // essa função bota a mediana no final
    trocar(A, meio, r);
}

// partição 
int particao(Paciente *A, int p, int v) {
    mediana(A, p, v);

    Paciente pivo = A[v];
    int i = p - 1;

    for (int j = p; j < v; j++) {
        if (prioridade(A[j], pivo)) {
            i++;
            trocar(A, i, j);
        }
    }

    trocar(A, i + 1, v);
    return i + 1;
}

// quicksort
void quicksort(Paciente *A, int p, int v) {
    if (p < v) {
        int q = particao(A, p, v);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, v);
    }
}

int main() {
    int N;
    scanf("%d", &N);

    Paciente *A = (Paciente *) malloc(N * sizeof(Paciente));

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &A[i].id, &A[i].gravidade);
    }

    quicksort(A, 0, N - 1);

    // sai os ids com prioridade
    for (int i = 0; i < N; i++) {
        printf("%d\n", A[i].id);
    }

    printf("Swaps: %lld\n", swap);

    free(A);
    return 0;
}