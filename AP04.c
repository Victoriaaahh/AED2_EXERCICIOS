#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALAVRA 21
#define ALFA 26 //alfabeto

// calcula o peso da palavra
int cpeso(const char *palavra, const int freq[]) {
    int peso = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        peso += freq[palavra[i] - 'a'];
    }
    return peso;
}

// define qual palavra é "maior"
int Maior(const char *a, const char *b, const int freq[]) {
    int pa = cpeso(a, freq);
    int pb = cpeso(b, freq);

    if (pa != pb) return pa > pb;

    // desempate é na ordem alfabetica inversa
    return strcmp(a, b) > 0;
}

// troca duas palavras
void trocar(char vetor[][MAX_PALAVRA], int i, int j) {
    char temp[MAX_PALAVRA];
    strcpy(temp, vetor[i]);
    strcpy(vetor[i], vetor[j]);
    strcpy(vetor[j], temp);
}

// desce no heap
void descer(char vetor[][MAX_PALAVRA], int i, int n, const int freq[]) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && Maior(vetor[esq], vetor[maior], freq))
        maior = esq;

    if (dir < n && Maior(vetor[dir], vetor[maior], freq))
        maior = dir;

    if (maior != i) {
        trocar(vetor, i, maior);
        descer(vetor, maior, n, freq);
    }
}

// constroi heap
void heap(char vetor[][MAX_PALAVRA], int n, const int freq[]) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        descer(vetor, i, n, freq);
    }
}

// heapsort
void heapSort(char vetor[][MAX_PALAVRA], int n, const int freq[]) {
    heap(vetor, n, freq);

    // imprimir heap
    printf("build_heap:");
    for (int i = 0; i < n; i++) {
        printf(" %s", vetor[i]);
    }
    printf("\n");

    // ordena
    for (int i = n - 1; i > 0; i--) {
        trocar(vetor, 0, i);
        descer(vetor, 0, i, freq);
    }
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    char (*entrada)[MAX_PALAVRA] = malloc(N * sizeof(*entrada));
    if (!entrada) return 1;

    for (int i = 0; i < N; i++) {
        scanf("%20s", entrada[i]);
    }

    // frequencia global
    int freq[ALFA] = {0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; entrada[i][j] != '\0'; j++) {
            freq[entrada[i][j] - 'a']++;
        }
    }

    char (*validas)[MAX_PALAVRA] = malloc(N * sizeof(*validas));
    if (!validas) {
        free(entrada);
        return 1;
    }

    int M = 0;

    // filtragem
    for (int i = 0; i < N; i++) {
        int invalida = 0;

        for (int j = 0; entrada[i][j] != '\0'; j++) {
            if (freq[entrada[i][j] - 'a'] < K) {
                invalida = 1;
                break;
            }
        }

        if (invalida) {
            printf("A palavra %s eh invalida (K=%d)\n", entrada[i], K);
        } else {
            strcpy(validas[M], entrada[i]);
            M++;
        }
    }

    // ordenacao
    if (M == 0) {
        printf("Erro: Sem palavras validas para ordenacao.\n");
    } else {
        heapSort(validas, M, freq);

        printf("palavras:");
        for (int i = 0; i < M; i++) {
            printf(" %s", validas[i]);
        }
        printf("\n");
    }

    free(entrada);
    free(validas);

    return 0;
}