#include <stdio.h>
#include <stdlib.h>

//nó da lista duplamente encadeada
typedef struct No {
    int id;
    struct No *anterior;
    struct No *prox;
} No;

// ponteiros para início e fim da lista
No *inicio = NULL;
No *fim = NULL;

// contador de NEP
int nep_total = 0;

// cria um novo nó
No* novoNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->id = valor;
    novo->anterior = NULL;
    novo->prox = NULL;
    return novo;
}

// função de inserção
void inserir(int valor) {
    No *novo = novoNo(valor); 

    if (inicio == NULL) {
        inicio = fim = novo;
        return;
    }

    if (valor <= inicio->id) {
        novo->prox = inicio;
        inicio->anterior = novo;
        inicio = novo;
        return;
    }

    if (valor >= fim->id) {
        novo->anterior = fim;
        fim->prox = novo;
        fim = novo;
        return;
    }

    int d_cabeca = abs(valor - inicio->id);
    int d_final = abs(valor - fim->id);

    No *atual;
    int nep = 0;

    if (d_cabeca <= d_final) {
        atual = inicio;

        while (atual->prox != NULL) {
            nep++;

            if (atual->prox->id >= valor)
                break;

            atual = atual->prox;
        }

        novo->prox = atual->prox;
        novo->anterior = atual;

        atual->prox->anterior = novo;
        atual->prox = novo;
    } else {
        atual = fim;

        while (atual->anterior != NULL) {
            nep++;

            if (atual->anterior->id <= valor)
                break;

            atual = atual->anterior;
        }

        novo->prox = atual;
        novo->anterior = atual->anterior;

        if (atual->anterior != NULL)
            atual->anterior->prox = novo;
        else
            inicio = novo;

        atual->anterior = novo;
    }

    nep_total += nep;
}

// imprime a lista
void imprimir() {
    No *aux = inicio;
    while (aux != NULL) {
        printf("%d", aux->id);
        if (aux->prox != NULL) printf(" ");
        aux = aux->prox;
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int valor;
        scanf("%d", &valor);
        inserir(valor);
    }

    imprimir();
    printf("%d\n", nep_total);

    return 0;
}