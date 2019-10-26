#include <stdio.h>
#include <string.h> // strcmp()
#include <stdlib.h> // srand() e rand()
#include <time.h>   // Para ser usado no srand() para o rand() gerar números pseudo-aleatórios

int mostrarIteracoes = 1; // Diz se as iterações do algoritmo serão mostradas
int numComparacoes = 0;
int numTrocas = 0;
void mostrar(int vetor[], int inicio, int fim, int pularLinha);
void inserir(int vetor[], int indice, int indiceDestino);
void verificarArgumentos(int argc, char **argv, int *tamanhoVetor);

// Organiza os valores do vetor
void merge(int vetor[], int inicio, int meio, int fim)
{
    int indiceEsquerdo = inicio;
    int indiceDireito = meio + 1;
    int aux[fim - inicio + 1];

    // if (mostrarIteracoes) {
    //     printf("\nMesclando (%d-%d) e (%d-%d)", inicio, meio, meio + 1, fim);
    //     printf(" -> ");
    //     mostrar(vetor, inicio, meio, 0);
    //     printf(" ");
    //     mostrar(vetor, meio + 1, fim, 0);
    //     printf(":\n");
    // }

    // Coloca os valores desordenados de vetor em vetorMesclador em ordem
    int i;
    for (i = 0; i < fim - inicio + 1; i++)
    {
        // if (mostrarIteracoes)
        //     if (indiceEsquerdo < meio + 1 && indiceDireito < fim + 1)
        //         printf("\tv[%d]=%d < v[%d]=%d: %s, inserindo %d em aux[%d] (v[%d])\n", indiceEsquerdo, vetor[indiceEsquerdo], indiceDireito, vetor[indiceDireito], (vetor[indiceEsquerdo] < vetor[indiceDireito]) ? "true" : "false", (vetor[indiceEsquerdo] < vetor[indiceDireito]) ? vetor[indiceEsquerdo] : vetor[indiceDireito], i, i + inicio);
        //     else if (indiceEsquerdo < meio + 1)
        //         printf("\tvetor direito ja inserido, inserindo %d em aux[%d] (v[%d])\n", vetor[indiceEsquerdo], i, inicio + i);
        //     else if (indiceDireito < fim + 1)
        //         printf("\tvetor esquerdo ja inserido, inserindo %d em aux[%d] (v[%d])\n", vetor[indiceDireito], i, inicio + i);

        if (indiceEsquerdo < meio + 1 && (indiceDireito > fim || vetor[indiceEsquerdo] < vetor[indiceDireito])) {
            if (indiceDireito <= fim && vetor[indiceEsquerdo] >= vetor[indiceDireito])
                numTrocas++;
            aux[i] = vetor[indiceEsquerdo++];
        } else {
            if (indiceEsquerdo <= meio)
                numTrocas++;
            aux[i] = vetor[indiceDireito++];
        }
        numComparacoes++;
    }

    // Substitui os valores de vetor por aux nos indices inicio até fim
    int j;
    for (j = inicio; j < fim + 1; j++)
        vetor[j] = aux[j - inicio];

    if (mostrarIteracoes)
    {
        printf("Mesclado (%d-%d): ", inicio, fim);
        if (inicio > 0)
            printf("%+*c", inicio * 4);
        printf("%.*s", 2 - (fim / 10 + inicio / 10), "  "); // Espacamento para alinhamento
        mostrar(vetor, inicio, fim, 1);
    }
}

void mergeSort(int vetor[], int inicio, int fim) // Os valores de inicio e fim são de índice 1
{
    // if (mostrarIteracoes) {
    //     printf("vetor (%d-%d) (%s):\t", inicio, fim, (fim - inicio > 0 ? "divisivel" : "indivisivel"));
    //     mostrar(vetor, inicio, fim, 1);
    // }

    if (fim - inicio < 1) // Se o tamanho do vetor for 1
        return;           // Não precisa dividir mais o vetor

    int meio = (fim + inicio) / 2;

    if (mostrarIteracoes)
    {
        printf("Dividido (%d-%d): ", inicio, fim);
        if (inicio > 0) {
            int i;
            for (i = 0; i < inicio * 4; i++)
                printf(" ");
        }
        printf("%.*s", 2 - (fim / 10 + inicio / 10), "  ");
        mostrar(vetor, inicio, meio, 0);
        mostrar(vetor, meio + 1, fim, 1);
    }

    mergeSort(vetor, inicio, meio);  // Vetor esquerdo: do inicio ao meio
    mergeSort(vetor, meio + 1, fim); // Vetor direito: do meio+1 ao fim
    merge(vetor, inicio, meio, fim); // Junta os dois vetores
}

// Execute o programa com os argumentos "-t <tamanho>" para escolher o tamanho do vetor
// Execute o programa com o argumento "-i" para mostrar as iterações
int main(int argc, char **argv)
{
    int tamanhoVetor = 10;

    // Altera as variáveis dependendo dos argumentos
    if (argc > 1) // Há argumentos
        verificarArgumentos(argc, argv, &tamanhoVetor);

    // Cria e preenche o vetor com números pseudo-aleatórios
    int vetor[tamanhoVetor];
    srand(time(0)); // Gera uma seed (time(0)) para o rand()
    int i;
    for (i = 0; i < tamanhoVetor; i++)
        vetor[i] = rand() % 100;

    // printf()s e ordenação do array
    printf("\t-- Merge Sort --\n");
    printf("Array (%d):     %.*s", tamanhoVetor, 3 - (tamanhoVetor / 10), "          "); // Espacamento para alinhamento
    mostrar(vetor, 0, tamanhoVetor - 1, 1);
    mergeSort(vetor, 0, tamanhoVetor - 1); // Ordena
    printf("Comparacoes:      %d\n", numComparacoes);
    printf("Trocas (ordem):   %d\n", numTrocas);
    printf("Ordenado:         "); // Espacamento para alinhamento
    mostrar(vetor, 0, tamanhoVetor - 1, 1);
    return 0;
}

// Itera o vetor do "inicio" ao "fim" e exibe, depois pula "pularLinha" linhas
void mostrar(int vetor[], int inicio, int fim, int pularLinha)
{
    printf("[");
    int i;
    for (i = inicio; i < fim; i++)
    {
        if (vetor[i] < 10)
            printf(" ");
        printf("%d  ", vetor[i]);
    }
    if (vetor[fim] < 10)
        printf(" ");
    printf("%d]", vetor[fim]);
    for (i = 0; i < pularLinha; i++)
        printf("\n");
}

// (Não importante para a ordenação)
// Verifica os argumentos do programa e modifica mostrarIteracoes e tamanhoVetor
void verificarArgumentos(int argc, char **argv, int *tamanhoVetor)
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        { // Verifica se há um argumento após "-t"
            if (i != argc - 1 && sscanf(argv[i + 1], "%d", tamanhoVetor) == 1)
                if (*tamanhoVetor < 1)
                {
                    printf("Tamanho incorreto, utilize um tamanho de vetor >= 1");
                    abort();
                }
                else
                    i++; // pula o número indicando o tamanhoVetor
        }
        else if (strcmp(argv[i], "-i") == 0)
            mostrarIteracoes = 0;
        else // Argumento não é nenhum dos válidos
        {
            printf("Parametro incorreto (\"%s\"). Utilize \"-t <tamanho>\" para indicar o tamanho do vetor e \"-i\" para mostrar iteracoes", argv[i]);
            abort();
        }
    }
}