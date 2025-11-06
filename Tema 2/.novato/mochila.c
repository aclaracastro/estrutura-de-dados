#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// estrutura p/ representar um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// vetor armazenando os itens da mochila
Item mochila[MAX_ITENS];
int totalItens = 0;

// declaração da função
void listarItens();  

// função para inserir um novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("Digite o nome do item: ");
    scanf("%s", novoItem.nome);
    printf("Digite o tipo do item (arma, municao, cura, etc): ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens++] = novoItem;
    printf("✅ Item adicionado com sucesso!\n");
    listarItens();
}

// função para remover um item da mochila pelo nome
void removerItem() {
    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", nomeRemover);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("🗑️ Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("❌ Item não encontrado na mochila.\n");
    }

    listarItens();
}

// função para listar todos os itens da mochila
void listarItens() {
    printf("\n📦 Itens na mochila:\n");
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("🔹 Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("\n");
}

// função para buscar um item pelo nome
void buscarItem() {
    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("🔍 Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("❌ Item não encontrado.\n");
}

// função principal com menu interativo
int main() {
    int opcao;

    do {
        printf("🎮 Sistema de Inventário - Mochila de Loot\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("👋 Saindo do sistema...\n"); break;
            default: printf("⚠️ Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
