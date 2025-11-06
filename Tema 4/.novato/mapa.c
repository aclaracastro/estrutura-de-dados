#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/**
 * Função criarSala
 * Cria uma sala com nome e retorna o ponteiro para ela
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

/**
 * Função explorarSalas
 * Permite ao jogador navegar pela árvore binária da mansão
 */
void explorarSalas(Sala* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Verifica se chegou a um nó-folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho. Esta sala não possui saídas.\n");
            break;
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
 * Monta o mapa da mansão e inicia a exploração
 */
int main() {
    // Criação das salas
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");

    // Montagem da árvore binária
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    // Início da exploração
    printf("🎮 Bem-vindo ao Detective Quest!\nExplore a mansão e descubra seus mistérios.\n");
    explorarSalas(hall);

    // Liberação da memória
    free(jardim);
    free(biblioteca);
    free(cozinha);
    free(salaEstar);
    free(hall);

    return 0;
}
