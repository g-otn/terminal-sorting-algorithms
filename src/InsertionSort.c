#include <stdio.h>
#include <string.h> // strcmp()
#include <stdlib.h> // srand() e rand()
#include <time.h>   // Para ser usado no srand() para o rand() gerar números pseudo-aleatórios

void mostrar(int tamanhoVetor, int vetor[]);
void verificarArgumentos(int argc, char **argv, int *tamanhoVetor, int *mostrarIteracoes);

int insertionSort(int tamanhoVetor, int vetor[], int mostrarIteracoes)
{
    int numComparacoes = 0;
    int numTrocas = 0;
    for (int i = 1; i < tamanhoVetor; i++)
    {
        //printf("\tseparando v[%d] (%d)\n", i, vetor[i]);
        int separado = vetor[i];
        int indiceVazio = i;
        while (indiceVazio > 0 && vetor[indiceVazio - 1] > separado) {
            numComparacoes++;
            //printf("\tmovendo v[%d] (%d) para v[%d]\n", indiceVazio - 1, vetor[indiceVazio - 1], indiceVazio);
            // Move o valor de vetor[indiceVazio - 1] uma posição para a direita
            vetor[indiceVazio] = vetor[indiceVazio - 1];
            numTrocas++;
            indiceVazio--;
        }
        numComparacoes++; // Guarda a última comparação (que faz sair do while)
        //printf("\tinserindo (%d) de volta em v[%d]\n", separado, indiceVazio);
        vetor[indiceVazio] = separado;

        // Mostra cada iteração se mostrarIteracoes for 1
        if (mostrarIteracoes)
        {
            printf("Iteracao %d:\t", i);
            mostrar(tamanhoVetor, vetor);
        }
    }
    printf("Comparacoes:\t%d\n", numComparacoes);
    printf("Trocas:\t\t%d\n", numTrocas);
}

// Execute o programa com os argumentos "-t <tamanho>" para escolher o tamanho do vetor
// Execute o programa com o argumento "-i" para não mostrar as iterações
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
    for (int i = 0; i < tamanhoVetor; i++)
        vetor[i] = rand() % 100;

    // printf()s e ordenação do array
    printf("\t-- Insertion Sort --\n");
    printf("Array (%d):\t", tamanhoVetor);
    mostrar(tamanhoVetor, vetor);
    insertionSort(tamanhoVetor, vetor, mostrarIteracoes); // Ordena
    printf("Ordenado:\t");
    mostrar(tamanhoVetor, vetor);
    return 0;
}

// Itera o vetor e exibe seus valores
void mostrar(int tamanhoVetor, int vetor[])
{
    printf("[");
    for (int i = 0; i < tamanhoVetor - 1; i++)
        printf("%d ", vetor[i]);
    printf("%d]\n", vetor[tamanhoVetor - 1]);
}

// (Não importante para a ordenação)
// Verifica os argumentos do programa e modifica mostrarIteracoes e tamanhoVetor
void verificarArgumentos(int argc, char **argv, int *tamanhoVetor, int *mostrarIteracoes)
{
    for (int i = 1; i < argc; i++)
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
            (*mostrarIteracoes) = 0;
        else // Argumento não é nenhum dos válidos
        {
            printf("Parametro incorreto (\"%s\"). Utilize \"-t <tamanho>\" para indicar o tamanho do vetor e \"-i\" para mostrar iteracoes", argv[i]);
            abort();
        }
    }
}