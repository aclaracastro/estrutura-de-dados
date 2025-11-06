#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100

// struct para representar um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// struct para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// vetor de itens
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// lista encadeada
No* inicioLista = NULL;

// contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

//
// funções para VETOR
//

void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("⚠️ Mochila (vetor) cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: "); scanf("%s", novo.nome);
    printf("Tipo: "); scanf("%s", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor++] = novo;
    printf("✅ Item inserido no vetor!\n");
}

void removerItemVetor() {
    char nome[30];
    printf("Nome do item a remover: "); scanf("%s", nome);

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalVetor--;
            printf("🗑️ Item removido do vetor!\n");
            return;
        }
    }
    printf("❌ Item não encontrado no vetor.\n");
}

void listarItensVetor() {
    printf("\n📦 Mochila (vetor):\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("🔹 %s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void buscarSequencialVetor() {
    char nome[30];
    printf("Nome do item a buscar: "); scanf("%s", nome);
    comparacoesSequencial = 0;

    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("🔍 Encontrado: %s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("❌ Item não encontrado. Comparações: %d\n", comparacoesSequencial);
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                Item temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
    printf("✅ Vetor ordenado por nome!\n");
}

void buscarBinariaVetor() {
    char nome[30];
    printf("Nome do item a buscar (binária): "); scanf("%s", nome);
    int inicio = 0, fim = totalVetor - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0) {
            printf("🔍 Encontrado: %s | %s | %d\n", mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    printf("❌ Item não encontrado. Comparações: %d\n", comparacoesBinaria);
}

//
// funções para LISTA ENCADEADA
//

void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    printf("Nome: "); scanf("%s", novo->dados.nome);
    printf("Tipo: "); scanf("%s", novo->dados.tipo);
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);
    novo->proximo = inicioLista;
    inicioLista = novo;
    printf("✅ Item inserido na lista!\n");
}

void removerItemLista() {
    char nome[30];
    printf("Nome do item a remover: "); scanf("%s", nome);

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                inicioLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("🗑️ Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado na lista.\n");
}

void listarItensLista() {
    printf("\n📦 Mochila (lista encadeada):\n");
    No* atual = inicioLista;
    while (atual != NULL) {
        printf("🔹 %s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    char nome[30];
    printf("Nome do item a buscar: "); scanf("%s", nome);
    comparacoesSequencial = 0;

    No* atual = inicioLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("🔍 Encontrado: %s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado. Comparações: %d\n", comparacoesSequencial);
}

//
// Menu principal
//

int main() {
    int estrutura, opcao;

    do {
        printf("\n🎮 Escolha a estrutura:\n1. Vetor\n2. Lista Encadeada\n0. Sair\n> ");
        scanf("%d", &estrutura);

        if (estrutura == 0) break;

        do {
            printf("\n📋 Menu de operações:\n");
            printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar sequencial\n");
            if (estrutura == 1) {
                printf("5. Ordenar vetor\n6. Buscar binária\n");
            }
            printf("0. Voltar\n> ");
            scanf("%d", &opcao);

            if (estrutura == 1) {
                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: ordenarVetor(); break;
                    case 6: buscarBinariaVetor(); break;
                }
            } else if (estrutura == 2) {
                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                }
            }

        } while (opcao != 0);

    } while (estrutura != 0);

    printf("👋 Saindo...\n");
    return 0;
}
