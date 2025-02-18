#include <stdio.h>
#include <stdlib.h>


#define TAM 2000 /*tamanho dos baldes*/

typedef struct balde {
    int qtd;
    int *valores;
} balde_t;

/*funcao que troca dois numeros*/
void switchNumbers (int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*funcao particionadora*/
int part(int vet[], int low, int high) {
    int pivo = vet[high];
    int i = (low - 1);
    int j;

    for (j = low; j < high; j++) {
        if (vet[j] <= pivo) {
            i++;
            switchNumbers(&vet[i], &vet[j]);
        }
    }
    switchNumbers(&vet[i + 1], &vet[high]);
    return (i + 1); /*indice do pivo*/
}

/*funcao principal do QuickSort*/
void QuickSort (int vet[], int low, int high) {
    if (low < high) {
        int pi = part(vet, low, high);

        QuickSort(vet, low, pi - 1);
        QuickSort(vet, pi + 1, high);
    }
}

/*funcao principal do BucketSort*/
void bucketSort(int *v, int n) {
    int i, j, maior, menor, nBaldes, pos, tam;
    balde_t* bd;
    int TAM_META = 100;

    /*acha maior e menor valor*/
    maior = menor = v[0];
    for (i = 0; i < n; i++) {
        if (v[i] > maior) {
            maior = v[i];
        }
        if (v[i] < menor) {
            menor = v[i];
        }
    }

    /*define o numero de baldes e o tamanho ideal de cada balde*/ 
    nBaldes = n / TAM_META;
    tam = (maior - menor) /nBaldes + 1;

    /*inicializa baldes*/
    bd = (balde_t*)malloc(nBaldes * sizeof(balde_t));
    for (i = 0; i < nBaldes; i++) {
        bd[i].qtd = 0;
        bd[i].valores = (int*)malloc(tam * sizeof(int));
    }

    /*distribui os valores nos baldes*/ 
    for (i = 0; i < n; i++) {
        pos = (v[i] - menor) / tam;
        bd[pos].valores[bd[pos].qtd] = v[i];
        bd[pos].qtd++;
    }

    /*ordena baldes com insertion sort e coloca no array*/
    pos = 0;
    for (i = 0; i < nBaldes; i++) {
        QuickSort(bd[i].valores, 0, bd[i].qtd - 1); 
        for (j = 0; j < bd[i].qtd; j++) {
            v[pos] = bd[i].valores[j];
            pos++;
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