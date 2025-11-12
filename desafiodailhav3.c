#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ===================== ESTRUTURA =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ===================== VARIÁVEIS GLOBAIS =====================
int comparacoes = 0; // contador de comparações

// ===================== FUNÇÕES AUXILIARES =====================
void mostrarComponentes(Componente lista[], int n) {
    printf("\n--- COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
            i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
    printf("---------------------------\n");
}

// ===================== BUBBLE SORT (por nome) =====================
void bubbleSortNome(Componente lista[], int n) {
    comparacoes = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

// ===================== INSERTION SORT (por tipo) =====================
void insertionSortTipo(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;

        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            lista[j + 1] = lista[j];
            j--;
        }
        comparacoes++;
        lista[j + 1] = chave;
    }
}

// ===================== SELECTION SORT (por prioridade) =====================
void selectionSortPrioridade(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }
}

// ===================== BUSCA BINÁRIA (por nome) =====================
int buscaBinariaPorNome(Componente lista[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, meio;
    int comparacoesBusca = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBusca++;
        int cmp = strcmp(lista[meio].nome, chave);

        if (cmp == 0) {
            printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                lista[meio].nome, lista[meio].tipo, lista[meio].prioridade);
            printf("Comparações na busca binária: %d\n", comparacoesBusca);
            return meio;
        }
        else if (cmp < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("Componente não encontrado.\n");
    printf("Comparações na busca binária: %d\n", comparacoesBusca);
    return -1;
}

// ===================== MEDIR TEMPO DE EXECUÇÃO =====================
void medirTempo(void (*algoritmo)(Componente[], int), Componente lista[], int n, const char* nomeAlgoritmo) {
    clock_t inicio, fim;
    double tempoGasto;

    Componente copia[MAX];
    memcpy(copia, lista, n * sizeof(Componente));

    inicio = clock();
    algoritmo(copia, n);
    fim = clock();

    tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n=== %s ===\n", nomeAlgoritmo);
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempoGasto);
    mostrarComponentes(copia, n);
}

// ===================== MENU PRINCIPAL =====================
int main() {
	setlocale(LC_ALL, "Portuguese");
    Componente componentes[MAX];
    int n = 0;
    int opcao;
    char chave[30];

    do {
        printf("\n=== TORRE DE RESGATE - MÓDULO AVANÇADO ===\n");
        printf("1. Cadastrar componente\n");
        printf("2. Exibir componentes\n");
        printf("3. Ordenar (Bubble - Nome)\n");
        printf("4. Ordenar (Insertion - Tipo)\n");
        printf("5. Ordenar (Selection - Prioridade)\n");
        printf("6. Buscar componente (Binária - Nome)\n");
        printf("7. Ativar escape da torre(sair)\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1:
            if (n >= MAX) {
                printf("Limite máximo de componentes atingido!\n");
            }
            else {
                printf("Nome: ");
                fgets(componentes[n].nome, sizeof(componentes[n].nome), stdin);
                componentes[n].nome[strcspn(componentes[n].nome, "\n")] = '\0';

                printf("Tipo: ");
                fgets(componentes[n].tipo, sizeof(componentes[n].tipo), stdin);
                componentes[n].tipo[strcspn(componentes[n].tipo, "\n")] = '\0';

                printf("Prioridade (1-10): ");
                scanf("%d", &componentes[n].prioridade);
                getchar();

                n++;
                printf("Componente cadastrado com sucesso!\n");
            }
            break;

        case 2:
            mostrarComponentes(componentes, n);
            break;

        case 3:
            medirTempo(bubbleSortNome, componentes, n, "Bubble Sort (Nome)");
            break;

        case 4:
            medirTempo(insertionSortTipo, componentes, n, "Insertion Sort (Tipo)");
            break;

        case 5:
            medirTempo(selectionSortPrioridade, componentes, n, "Selection Sort (Prioridade)");
            break;

        case 6:
            if (n == 0) {
                printf("Nenhum componente cadastrado!\n");
                break;
            }
            printf("Digite o nome do componente a buscar: ");
            fgets(chave, sizeof(chave), stdin);
            chave[strcspn(chave, "\n")] = '\0';
            bubbleSortNome(componentes, n); // garantir ordenação
            buscaBinariaPorNome(componentes, n, chave);
            break;

        case 7:
            printf("Encerrando o sistema da torre de resgate...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 7);

    return 0;
}
