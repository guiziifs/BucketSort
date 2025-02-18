#include <stdio.h>
#include <stdlib.h>

#define TAM 2000 /* Tamanho dos baldes */

typedef struct balde {
    int qtd;
    int *valores;
} balde_t;

/* Função que troca dois números */
void switchNumbers(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Função que cria um heap máximo */
void maxHeapify(int vet[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    /* Se o filho da esquerda é maior que a raiz */
    if (esq < n && vet[esq] > vet[maior]) {
        maior = esq;
    }

    /* Se o filho da direita é maior que a raiz */
    if (dir < n && vet[dir] > vet[maior]) {
        maior = dir;
    }

    /* Se maior não é a raiz */
    if (maior != i) {
        switchNumbers(&vet[i], &vet[maior]);

        /* Transforma a subárvore em um heap */
        maxHeapify(vet, n, maior);
    }
}

/* Função principal do Heap Sort */
void heapSort(int vet[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(vet, n, i);
    }

    /* Extrai um elemento de cada vez do heap */
    for (int i = n - 1; i > 0; i--) {
        /* Move a raiz para o final */
        switchNumbers(&vet[0], &vet[i]);

        /* Chama o maxHeapify */
        maxHeapify(vet, i, 0);
    }
}

/* Função principal do Bucket Sort */
void bucketSort(int *v, int n) {
    int i, j, maior, menor, nBaldes, pos, tam;
    balde_t* bd;
    int TAM_META = 100;

    /* Acha maior e menor valor */
    maior = menor = v[0];
    for (i = 0; i < n; i++) {
        if (v[i] > maior) {
            maior = v[i];
        }
        if (v[i] < menor) {
            menor = v[i];
        }
    }

    /* Define o número de baldes e o tamanho ideal de cada balde */
    nBaldes = n / TAM_META;
    tam = (maior - menor) / nBaldes + 1;

    /* Inicializa baldes */
    bd = (balde_t*)malloc(nBaldes * sizeof(balde_t));
    for (i = 0; i < nBaldes; i++) {
        bd[i].qtd = 0;
        bd[i].valores = (int*)malloc(tam * sizeof(int));
    }

    /* Distribui os valores nos baldes */
    for (i = 0; i < n; i++) {
        pos = (v[i] - menor) / tam;
        bd[pos].valores[bd[pos].qtd] = v[i];
        bd[pos].qtd++;
    }

    /* Ordena baldes com heap sort e coloca no array */
    pos = 0;
    for (i = 0; i < nBaldes; i++) {
        heapSort(bd[i].valores, bd[i].qtd);
        for (j = 0; j < bd[i].qtd; j++) {
            v[pos++] = bd[i].valores[j];
        }
        free(bd[i].valores);
    }
    free(bd);
}

/*le o arquivo*/
void readFromFile (const char* filename, int vet[], int *n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    int i = 0;
    while(fscanf(file, "%d", &vet[i]) != EOF) {
        i++;
    }
    *n = i;
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    int vet[1000000]; 
    int n;

    readFromFile(filename, vet, &n);

    bucketSort(vet, n);
}