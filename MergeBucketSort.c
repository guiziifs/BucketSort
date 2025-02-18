#include <stdio.h>
#include <stdlib.h>


#define TAM 2000 /*tamanho dos baldes*/

typedef struct balde {
    int qtd;
    int *valores;
} balde_t;

/*funcao que mescla as metades ordenadas*/
void merge(int vet[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /*vetores temporarios*/
    int L[n1], R[n2];

    /*copia os dados para os vetores temporarios*/
    for (i = 0; i < n1; i++) {
        L[i] = vet[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = vet[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            j++;
        }
        k++;
    }

        /* Copia os elementos restantes de L[], se houver algum*/
    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }

    /*Copia os elementos restantes de R[], se houver algum*/
    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }
}

/*funcao principal do mergeSort*/
void mergeSort (int vet[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        /*ordena a primeira e a segunda metade*/
        mergeSort(vet, l, m);
        mergeSort(vet, m + 1, r);

        /*mescla as metades ordenadas*/
        merge(vet, l, m, r);
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
        mergeSort(bd[i].valores, 0, bd[i].qtd - 1); 
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