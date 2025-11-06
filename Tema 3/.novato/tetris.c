#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

// Struct que representa uma peça do Tetris
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // identificador único
} Peca;

// Fila circular
Peca fila[TAMANHO_FILA];
int frente = 0;
int tras = 0;
int total = 0;
int contadorID = 0;

// Gera uma nova peça automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// Insere uma nova peça no final da fila
void enqueue() {
    if (total == TAMANHO_FILA) {
        printf("⚠️ Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAMANHO_FILA;
    total++;
    printf("✅ Nova peça inserida!\n");
}

// Remove a peça da frente da fila
void dequeue() {
    if (total == 0) {
        printf("⚠️ Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    printf("🕹️ Peça jogada: [%c %d]\n", fila[frente].nome, fila[frente].id);
    frente = (frente + 1) % TAMANHO_FILA;
    total--;
}

// Exibe o estado atual da fila
void mostrarFila() {
    printf("\n📦 Fila de peças:\n");
    if (total == 0) {
        printf("Fila vazia.\n");
        return;
    }
    int i = frente;
    for (int count = 0; count < total; count++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// Menu principal
int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue();
    }

    int opcao;
    do {
        mostrarFila();
        printf("\n🎮 Ações disponíveis:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: dequeue(); break;
            case 2: enqueue(); break;
            case 0: printf("👋 Encerrando o jogo...\n"); break;
            default: printf("⚠️ Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
