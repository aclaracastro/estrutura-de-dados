#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Struct que representa uma peça do Tetris
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // identificador único
} Peca;

// Fila circular
Peca fila[TAM_FILA];
int frente = 0, tras = 0, totalFila = 0;

// Pilha linear
Peca pilha[TAM_PILHA];
int topo = -1;

// Contador global de IDs
int contadorID = 0;

// Gera uma nova peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// Insere nova peça na fila (enqueue)
void inserirNaFila() {
    if (totalFila == TAM_FILA) return; // fila sempre cheia
    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAM_FILA;
    totalFila++;
}

// Remove peça da frente da fila (dequeue)
Peca removerDaFila() {
    Peca removida = {'-', -1};
    if (totalFila == 0) {
        printf("⚠️ Fila vazia!\n");
        return removida;
    }
    removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    totalFila--;
    return removida;
}

// Insere peça na pilha (push)
int inserirNaPilha(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("⚠️ Pilha cheia! Não é possível reservar mais peças.\n");
        return 0;
    }
    pilha[++topo] = p;
    return 1;
}

// Remove peça do topo da pilha (pop)
Peca removerDaPilha() {
    Peca removida = {'-', -1};
    if (topo == -1) {
        printf("⚠️ Pilha vazia! Nenhuma peça reservada.\n");
        return removida;
    }
    removida = pilha[topo--];
    return removida;
}

// Exibe o estado atual da fila e da pilha
void mostrarEstado() {
    printf("\n📦 Fila de peças:\n");
    int i = frente;
    for (int count = 0; count < totalFila; count++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\n🗃️ Pilha de reserva (Topo -> Base):\n");
    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// Menu principal
int main() {
    srand(time(NULL));

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        inserirNaFila();
    }

    int opcao;
    do {
        mostrarEstado();
        printf("\n🎮 Ações disponíveis:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = removerDaFila();
                if (jogada.id != -1)
                    printf("🕹️ Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                inserirNaFila();
                break;
            }
            case 2: {
                Peca reservada = removerDaFila();
                if (reservada.id != -1 && inserirNaPilha(reservada))
                    printf("📥 Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
                inserirNaFila();
                break;
            }
            case 3: {
                Peca usada = removerDaPilha();
                if (usada.id != -1)
                    printf("🧩 Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                break;
            }
            case 0:
                printf("👋 Encerrando o jogo...\n");
                break;
            default:
                printf("⚠️ Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
