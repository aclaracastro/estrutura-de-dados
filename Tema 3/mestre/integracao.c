#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3
#define MAX_HISTORICO 10

// Struct que representa uma peça
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;
} Peca;

// Histórico de ações para desfazer
typedef struct {
    char acao[20];
    Peca peca;
} Historico;

// Fila circular
Peca fila[TAM_FILA];
int frente = 0, tras = 0, totalFila = 0;

// Pilha linear
Peca pilha[TAM_PILHA];
int topo = -1;

// Histórico
Historico historico[MAX_HISTORICO];
int totalHistorico = 0;

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

// Insere nova peça na fila
void inserirNaFila() {
    if (totalFila == TAM_FILA) return;
    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAM_FILA;
    totalFila++;
}

// Remove peça da fila
Peca removerDaFila() {
    Peca removida = {'-', -1};
    if (totalFila == 0) return removida;
    removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    totalFila--;
    return removida;
}

// Insere peça na pilha
int inserirNaPilha(Peca p) {
    if (topo == TAM_PILHA - 1) return 0;
    pilha[++topo] = p;
    return 1;
}

// Remove peça da pilha
Peca removerDaPilha() {
    Peca removida = {'-', -1};
    if (topo == -1) return removida;
    removida = pilha[topo--];
    return removida;
}

// Salva ação no histórico
void registrarAcao(char acao[], Peca p) {
    if (totalHistorico < MAX_HISTORICO) {
        strcpy(historico[totalHistorico].acao, acao);
        historico[totalHistorico].peca = p;
        totalHistorico++;
    }
}

// Desfaz última ação
void desfazerUltima() {
    if (totalHistorico == 0) {
        printf("⚠️ Nenhuma ação para desfazer.\n");
        return;
    }

    Historico ultima = historico[--totalHistorico];

    if (strcmp(ultima.acao, "jogar") == 0) {
        if (totalFila < TAM_FILA) {
            frente = (frente - 1 + TAM_FILA) % TAM_FILA;
            fila[frente] = ultima.peca;
            totalFila++;
            tras = (tras - 1 + TAM_FILA) % TAM_FILA;
        }
    } else if (strcmp(ultima.acao, "reservar") == 0) {
        if (topo >= 0 && pilha[topo].id == ultima.peca.id) {
            topo--;
            frente = (frente - 1 + TAM_FILA) % TAM_FILA;
            fila[frente] = ultima.peca;
            totalFila++;
            tras = (tras - 1 + TAM_FILA) % TAM_FILA;
        }
    } else if (strcmp(ultima.acao, "usar") == 0) {
        if (topo < TAM_PILHA - 1) {
            pilha[++topo] = ultima.peca;
        }
    }

    printf("↩️ Ação '%s' desfeita para peça [%c %d]\n", ultima.acao, ultima.peca.nome, ultima.peca.id);
}

// Troca frente da fila com topo da pilha
void trocarTopoFrente() {
    if (totalFila == 0 || topo == -1) {
        printf("⚠️ Troca impossível.\n");
        return;
    }
    Peca temp = fila[frente];
    fila[frente] = pilha[topo];
    pilha[topo] = temp;
    printf("🔁 Troca realizada entre frente da fila e topo da pilha.\n");
}

// Inverte fila com pilha
void inverterFilaPilha() {
    if (totalFila < TAM_PILHA || topo < TAM_PILHA - 1) {
        printf("⚠️ Inversão não permitida. Ambas devem ter pelo menos 3 peças.\n");
        return;
    }

    for (int i = 0; i < TAM_PILHA; i++) {
        int posFila = (frente + i) % TAM_FILA;
        Peca temp = fila[posFila];
        fila[posFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("🔄 Inversão realizada entre fila e pilha.\n");
}

// Exibe estado atual
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
    for (int i = 0; i < TAM_FILA; i++) inserirNaFila();

    int opcao;
    do {
        mostrarEstado();
        printf("\n🎮 Ações disponíveis:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Desfazer última jogada\n");
        printf("6 - Inverter fila com pilha\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = removerDaFila();
                if (jogada.id != -1) {
                    printf("🕹️ Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                    registrarAcao("jogar", jogada);
                    inserirNaFila();
                }
                break;
            }
            case 2: {
                Peca reservada = removerDaFila();
                if (reservada.id != -1 && inserirNaPilha(reservada)) {
                    printf("📥 Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
                    registrarAcao("reservar", reservada);
                    inserirNaFila();
                }
                break;
            }
            case 3: {
                Peca usada = removerDaPilha();
                if (usada.id != -1) {
                    printf("🧩 Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                    registrarAcao("usar", usada);
                }
                break;
            }
            case 4:
                trocarTopoFrente();
                break;
            case 5:
                desfazerUltima();
                break;
            case 6:
                inverterFilaPilha();
                break;
            case 0:
                printf("👋 Encerrando o jogo...\n");
                break;
            default:
                printf("⚠️ Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
