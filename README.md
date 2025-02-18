## Implementação de Bucket Sort em C  
**Autor:** Guilherme Ferreira da Silva  
**Disciplina:** Pesquisa e Ordenação de Dados  

O seguinte relatório apresenta a análise de desempenho de três algoritmos de ordenação híbridos baseados no **Bucket Sort** na linguagem C na matéria de Pesquisa e Ordenação de Dados. O objetivo foi avaliar a eficiência desses algoritmos para três conjuntos de dados de tamanhos diferentes:  

- **100 mil** números desordenados  
- **1 milhão** de números desordenados  
- **100 milhões** de números desordenados  

O **Bucket Sort** separa esses dados em baldes e aplica, posteriormente, uma técnica de ordenação interna diferente, considerando **buckets com tamanho fixo de 2000 elementos**.  

Cada algoritmo de ordenação escolhido para a fase de ordenação interna dos buckets possui características únicas, tornando-os adequados para diferentes cenários de ordenação. Assim, esses algoritmos foram selecionados com base em suas capacidades para lidar com subgrupos de dados parcialmente ordenados.  

## Estrutura do Código  

Para a estrutura do código, foram utilizadas apenas as bibliotecas padrão do C (`stdio.h` e `stdlib.h`). Além disso, foi definido um tipo de dado chamado **`balde_t`**, que consiste em uma `struct` contendo:  

- Um inteiro chamado `qtd`, que armazena a quantidade de elementos do balde.  
- Um ponteiro para inteiros chamado `valores`, que armazena os valores numéricos efetivamente.  

O algoritmo **Bucket Sort** se mantém aproximadamente o mesmo para todos os testes, visto que a principal mudança é o **algoritmo de ordenação interna** utilizado dentro de cada bucket.  

