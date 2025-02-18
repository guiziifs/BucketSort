#include <stdio.h>
#include <stdlib.h>


#define TAM 2000 /*tamanho dos baldes*/

typedef struct balde {
    int qtd;
    int *valores;
} balde_t;

/*funcao principal do InsertioSort*/
void insertionSort (int vet[], int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = vet[i];
        j = i - 1;
        while (j >= 0 && vet[j] > chave) {
            vet[j + 1] = vet[j];
            j = j - 1;
        }
        vet[j + 1] = chave;
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
        insertionSort(bd[i].valores, bd[i].qtd); 
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