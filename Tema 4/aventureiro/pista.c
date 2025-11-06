#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];
    char pista[50]; // Pista opcional
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura que representa um nó da árvore de pistas (BST)
typedef struct PistaNode {
    char pista[50];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

/**
 * Função criarSala
 * Cria dinamicamente uma sala com nome e pista (pode ser vazia)
 */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        strcpy(novaSala->pista, pista);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

/**
 * Função inserirPista
 * Insere uma nova pista na árvore BST de forma ordenada
 */
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        if (novo != NULL) {
            strcpy(novo->pista, pista);
            novo->esquerda = NULL;
            novo->direita = NULL;
        }
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    return raiz;
}

/**
 * Função exibirPistas
 * Exibe todas as pistas em ordem alfabética (em ordem simétrica)
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

/**
 * Função explorarSalasComPistas
 * Permite navegação entre salas e coleta automática de pistas
 */
void explorarSalasComPistas(Sala* atual, PistaNode** arvorePistas) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Se houver pista, adiciona à árvore
        if (strlen(atual->pista) > 0) {
            printf("🔍 Pista encontrada: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("Escolha o caminho: (e) esquerda, (d) direita, (s) sair: ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há sala à esquerda. Tente novamente.\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há sala à direita. Tente novamente.\n");
            }
        } else if (escolha == 's') {
            printf("Exploração encerrada.\n");
            break;
        } else {
            printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
        }
    }
}

/**
 * Função main
 * Monta o mapa da mansão e inicia a exploração com coleta de pistas
 */
int main() {
    // Criação das salas com pistas
    Sala* hall = criarSala("Hall de Entrada", "");
    Sala* salaEstar = criarSala("Sala de Estar", "Pegada na cortina");
    Sala* cozinha = criarSala("Cozinha", "Faca suja na pia");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado no chão");
    Sala* jardim = criarSala("Jardim", "");

    // Montagem da árvore binária da mansão
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    // Inicialização da árvore de pistas
    PistaNode* arvorePistas = NULL;

    // Início da exploração
    printf("🕵️ Bem-vindo ao Detective Quest - Nível Aventureiro!\nExplore a mansão e colete pistas.\n");
    explorarSalasComPistas(hall, &arvorePistas);

    // Exibição das pistas coletadas
    printf("\n📜 Pistas coletadas (em ordem alfabética):\n");
    exibirPistas(arvorePistas);

    // Liberação da memória das salas
    free(jardim);
    free(biblioteca);
    free(cozinha);
    free(salaEstar);
    free(hall);

    // Liberação da memória da árvore de pistas (recursiva)
    // Função auxiliar para liberar BST
    void liberarPistas(PistaNode* raiz) {
        if (raiz != NULL) {
            liberarPistas(raiz->esquerda);
            liberarPistas(raiz->direita);
            free(raiz);
        }
    }
    liberarPistas(arvorePistas);

    return 0;
}
