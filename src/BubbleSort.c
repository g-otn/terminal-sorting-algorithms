#include <stdio.h>
#include <string.h> // strcmp()
#include <stdlib.h> // srand() e rand()
#include <time.h>   // Para ser usado no srand() para o rand() gerar números pseudo-aleatórios

void mostrar(int tamanhoVetor, int vetor[]);
void trocar(int vetor[], int indiceA, int indiceB);
void verificarArgumentos(int argc, char **argv, int *tamanhoVetor, int *mostrarIteracoes);

int bubbleSort(int tamanhoVetor, int vetor[], int mostrarIteracoes)
{
    int numComparacoes = 0;
    int numTrocas = 0;
    int i;
    for (i = 0; i < tamanhoVetor; i++)
    {
        int j;
        for (j = 0; j < tamanhoVetor - i; j++)
        {
            if (vetor[j] > vetor[j + 1]) {
                trocar(vetor, j, j+1);
                numTrocas++;
            }
            numComparacoes++;
        }

        // Mostra cada iteração se mostrarIteracoes for 1
        if (mostrarIteracoes)
        {
            printf("Iteracao %d:\t", i + 1);
            mostrar(tamanhoVetor, vetor);
        }
    }
    printf("Comparacoes:\t%d\n", numComparacoes);
    printf("Trocas:\t\t%d\n", numTrocas);
}

// Execute o programa com os argumentos "-t <tamanho>" para escolher o tamanho do vetor
// Execute o programa com o argumento "-i" para mostrar as iterações
int main(int argc, char **argv)
{
    int tamanhoVetor = 10;
    int mostrarIteracoes = 1; // Diz se as iterações do algoritmo serão mostradas

    // Altera as variáveis dependendo dos argumentos
    if (argc > 1) // Há argumentos
        verificarArgumentos(argc, argv, &tamanhoVetor, &mostrarIteracoes);
    
    // Cria e preenche o vetor com números pseudo-aleatórios
    int vetor[tamanhoVetor];
    srand(time(0)); // Gera uma seed (time(0)) para o rand()
    int i;
    for (i = 0; i < tamanhoVetor; i++)
        vetor[i] = rand() % 100;

    // printf()s e ordenação do array
    printf("\t-- Bubble Sort --\n");
    printf("Array (%d):\t", tamanhoVetor);
    mostrar(tamanhoVetor, vetor);
    bubbleSort(tamanhoVetor, vetor, mostrarIteracoes); // Ordena
    printf("Ordenado:\t");
    mostrar(tamanhoVetor, vetor);
    return 0;
}

// Itera o vetor e exibe seus valores
void mostrar(int tamanhoVetor, int vetor[])
{
    int i;
    printf("[");
    for (i = 0; i < tamanhoVetor - 1; i++)
        printf("%d ", vetor[i]);
    printf("%d]\n", vetor[tamanhoVetor - 1]);
}

// Troca os valores de vetor[indiceA] e vetor[indiceB] entre eles
void trocar(int vetor[], int indiceA, int indiceB)
{
    int aux = vetor[indiceA];
    vetor[indiceA] = vetor[indiceB];
    vetor[indiceB] = aux;
}

// (Não importante para a ordenação)
// Verifica os argumentos do programa e modifica mostrarIteracoes e tamanhoVetor
void verificarArgumentos(int argc, char **argv, int *tamanhoVetor, int *mostrarIteracoes) {    
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) { // Verifica se o argumento atual é "-t"
            if (i != argc - 1 && sscanf(argv[i+1],"%d", tamanhoVetor) == 1) // Verifica se há um argumento após "-t"
                if (*tamanhoVetor < 1) {
                    printf("Tamanho incorreto, utilize um tamanho de vetor >= 1");
                    abort();
                } else
                    i++; // pula o número indicando o tamanhoVetor
        } else if (strcmp(argv[i], "-i") == 0) 
            (*mostrarIteracoes) = 0;
        else {
            printf("Parametro incorreto (\"%s\"). Utilize \"-t <tamanho>\" para indicar o tamanho do vetor e \"-i\" para mostrar iteracoes", argv[i]);
            abort();
        }
    }
}