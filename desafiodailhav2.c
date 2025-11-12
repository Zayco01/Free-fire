#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// ===================== ESTRUTURAS =====================

// Estrutura básica do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ===================== VARIÁVEIS GLOBAIS =====================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ===================== FUNÇÕES VETOR =====================

void inserirItemVetor(Item vetor[], int* n) {
    if (*n >= 10) {
        printf("Mochila (vetor) cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    vetor[*n] = novo;
    (*n)++;

    printf("Item adicionado no vetor com sucesso!\n");
}

void removerItemVetor(Item vetor[], int* n) {
    if (*n == 0) {
        printf("Mochila (vetor) vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *n; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *n - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*n)--;
            printf("Item removido do vetor.\n");
            return;
        }
    }

    printf("Item nao encontrado no vetor.\n");
}

void listarItensVetor(Item vetor[], int n) {
    if (n == 0) {
        printf("Mochila (vetor) vazia!\n");
        return;
    }

    printf("\n--- Itens no vetor ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
            i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

void buscarSequencialVetor(Item vetor[], int n) {
    if (n == 0) {
        printf("Mochila (vetor) vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    comparacoesSequencial = 0;

    for (int i = 0; i < n; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            printf("Item encontrado: %s (%s), qtd %d\n",
                vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
            printf("Comparacoes feitas: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("Item nao encontrado.\n");
    printf("Comparacoes feitas: %d\n", comparacoesSequencial);
}

// Bubble Sort por nome
void ordenarVetor(Item vetor[], int n) {
    Item temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome!\n");
}

// Busca binária (após ordenar)
void buscarBinariaVetor(Item vetor[], int n) {
    if (n == 0) {
        printf("Mochila (vetor) vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a buscar (busca binaria): ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int inicio = 0, fim = n - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0) {
            printf("Item encontrado: %s (%s), qtd %d\n",
                vetor[meio].nome, vetor[meio].tipo, vetor[meio].quantidade);
            printf("Comparacoes feitas: %d\n", comparacoesBinaria);
            return;
        }
        else if (cmp < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("Item nao encontrado (busca binaria).\n");
    printf("Comparacoes feitas: %d\n", comparacoesBinaria);
}

// ===================== FUNÇÕES LISTA ENCADEADA =====================

No* inserirItemLista(No* inicio) {
    No* novo = (No*)malloc(sizeof(No));

    printf("Nome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("Item adicionado na lista encadeada!\n");
    return novo;
}

No* removerItemLista(No* inicio) {
    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return inicio;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = inicio, * anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado na lista.\n");
        return inicio;
    }

    if (anterior == NULL)
        inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido da lista encadeada!\n");
    return inicio;
}

void listarItensLista(No* inicio) {
    if (inicio == NULL) {
        printf("Lista encadeada vazia!\n");
        return;
    }

    printf("\n--- Itens na lista encadeada ---\n");
    No* aux = inicio;
    int i = 1;
    while (aux != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
            i++, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

void buscarItemLista(No* inicio) {
    if (inicio == NULL) {
        printf("Lista encadeada vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    comparacoesSequencial = 0;

    No* aux = inicio;
    while (aux != NULL) {
        comparacoesSequencial++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("Item encontrado: %s (%s), qtd %d\n",
                aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            printf("Comparacoes feitas: %d\n", comparacoesSequencial);
            return;
        }
        aux = aux->proximo;
    }

    printf("Item nao encontrado.\n");
    printf("Comparacoes feitas: %d\n", comparacoesSequencial);
}

// ===================== MENU PRINCIPAL =====================

int main() {
	setlocale(LC_ALL, "Portuguese");
    Item vetor[10];
    int n = 0;
    No* lista = NULL;
    int opcao, estrutura;

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("1. Usar vetor (lista sequencial)\n");
        printf("2. Usar lista encadeada\n");
        printf("3. Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &estrutura);
        getchar();

        if (estrutura == 1) {
            do {
                printf("\n--- Mochila (VETOR) ---\n");
                printf("1. Inserir item\n2. Remover item\n3. Listar itens\n");
                printf("4. Buscar sequencial\n5. Ordenar vetor\n6. Buscar binaria\n7. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                switch (opcao) {
                case 1: inserirItemVetor(vetor, &n); break;
                case 2: removerItemVetor(vetor, &n); break;
                case 3: listarItensVetor(vetor, n); break;
                case 4: buscarSequencialVetor(vetor, n); break;
                case 5: ordenarVetor(vetor, n); break;
                case 6: buscarBinariaVetor(vetor, n); break;
                case 7: break;
                default: printf("Opcao invalida!\n");
                }
            } while (opcao != 7);
        }

        else if (estrutura == 2) {
            do {
                printf("\n--- Mochila (LISTA ENCADEADA) ---\n");
                printf("1. Inserir item\n2. Remover item\n3. Listar itens\n");
                printf("4. Buscar item\n5. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                switch (opcao) {
                case 1: lista = inserirItemLista(lista); break;
                case 2: lista = removerItemLista(lista); break;
                case 3: listarItensLista(lista); break;
                case 4: buscarItemLista(lista); break;
                case 5: break;
                default: printf("Opcao invalida!\n");
                }
            } while (opcao != 5);
        }

    } while (estrutura != 3);

    printf("Encerrando o sistema...\n");
    return 0;
}
