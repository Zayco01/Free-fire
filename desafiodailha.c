#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h> 
#include <stdlib.h>
#include <string.h>

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Declarações de funções
void inserirItem(Item mochila[], int* contador);
void removerItem(Item mochila[], int* contador);
void listarItens(Item mochila[], int contador);
void buscarItem(Item mochila[], int contador);

int main() { 
    setlocale(LC_ALL, "Portuguese");
    Item mochila[10]; // Vetor que armazena até 10 itens
    int contador = 0; // Quantidade atual de itens na mochila
    int opcao;

    do {
        printf("\n=== MOCHILA DE LOOT ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
        case 1:
            inserirItem(mochila, &contador);
            break;
        case 2:
            removerItem(mochila, &contador);
            break;
        case 3:
            listarItens(mochila, contador);
            break;
        case 4:
            buscarItem(mochila, contador);
            break;
        case 5:
            printf("Saindo do sistema de inventario...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

// Função para inserir um novo item na mochila
void inserirItem(Item mochila[], int* contador) {
    if (*contador >= 10) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o \n

    printf("Digite o tipo do item (arma, municao, cura, etc): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*contador] = novo;
    (*contador)++;

    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item da mochila
void removerItem(Item mochila[], int* contador) {
    if (*contador == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < *contador - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*contador)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
        printf("Item nao encontrado na mochila.\n");
}

// Função para listar todos os itens
void listarItens(Item mochila[], int contador) {
    if (contador == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    for (int i = 0; i < contador; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("--------------------------\n");
    }
}

// Função para buscar um item pelo nome
void buscarItem(Item mochila[], int contador) {
    if (contador == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("Item nao encontrado na mochila.\n");
}
