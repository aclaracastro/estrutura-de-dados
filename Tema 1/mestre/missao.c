#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== CONSTANTES E ESTRUTURAS ====================
#define MAX_TERRITORIOS 10
#define MAX_JOGADORES 2
#define MAX_MISSOES 5

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct {
    char nome[20];
    char cor[10];
    char* missao;
} Jogador;

// ==================== DECLARAÇÕES DE FUNÇÕES ====================
void inicializarJogo(Jogador jogadores[MAX_JOGADORES], Territorio territorios[MAX_TERRITORIOS], int* totalTerritorios);
void atribuirMissao(Jogador* jogador);
int verificarMissao(const Jogador* jogador, const Territorio territorios[], int totalTerritorios);
void exibirMissao(const Jogador* jogador);
void executarAtaque(Territorio territorios[], int totalTerritorios, const Jogador* jogadorAtual);
void exibirMapa(const Territorio territorios[], int totalTerritorios);
void mostrarMenu(const Jogador* jogadorAtual);
void liberarMemoria(Jogador jogadores[MAX_JOGADORES]);

// ==================== VARIÁVEIS GLOBAIS ====================
const char* MISSOES_DISPONIVEIS[MAX_MISSOES] = {
    "Destruir o exercito amarelo",
    "Conquistar 3 territorios",
    "Controlar a America do Sul",
    "Eliminar todas as tropas azuis", 
    "Ter 8 tropas em um territorio"
};

// ==================== IMPLEMENTAÇÃO DAS FUNÇÕES ====================

void atribuirMissao(Jogador* jogador) {
    int indiceMissao = rand() % MAX_MISSOES;
    jogador->missao = (char*)malloc(strlen(MISSOES_DISPONIVEIS[indiceMissao]) + 1);
    strcpy(jogador->missao, MISSOES_DISPONIVEIS[indiceMissao]);
}

int verificarMissao(const Jogador* jogador, const Territorio territorios[], int totalTerritorios) {
    // Missão 1: Destruir o exército amarelo
    if (strstr(jogador->missao, "exercito amarelo")) {
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(territorios[i].cor, "amarelo") == 0 && territorios[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    
    // Missão 2: Conquistar 3 territórios
    if (strstr(jogador->missao, "3 territorios")) {
        int territoriosControlados = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(territorios[i].cor, jogador->cor) == 0) {
                territoriosControlados++;
            }
        }
        return territoriosControlados >= 3;
    }
    
    // Missão 3: Controlar a América do Sul (territórios específicos)
    if (strstr(jogador->missao, "America do Sul")) {
        int territoriosSul = 0;
        const char* americaSul[] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia"};
        
        for (int i = 0; i < totalTerritorios; i++) {
            for (int j = 0; j < 5; j++) {
                if (strcmp(territorios[i].nome, americaSul[j]) == 0 && 
                    strcmp(territorios[i].cor, jogador->cor) == 0) {
                    territoriosSul++;
                }
            }
        }
        return territoriosSul >= 3;
    }
    
    // Missão 4: Eliminar todas as tropas azuis
    if (strstr(jogador->missao, "tropas azuis")) {
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(territorios[i].cor, "azul") == 0 && territorios[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    
    // Missão 5: Ter 8 tropas em um território
    if (strstr(jogador->missao, "8 tropas")) {
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(territorios[i].cor, jogador->cor) == 0 && territorios[i].tropas >= 8) {
                return 1;
            }
        }
        return 0;
    }
    
    return 0;
}

void exibirMissao(const Jogador* jogador) {
    printf("🎯 Missao de %s: %s\n", jogador->nome, jogador->missao);
}

void executarAtaque(Territorio territorios[], int totalTerritorios, const Jogador* jogadorAtual) {
    int atacante, defensor;
    
    printf("\nEscolha territorio ATACANTE (1-%d): ", totalTerritorios);
    scanf("%d", &atacante);
    printf("Escolha territorio DEFENSOR (1-%d): ", totalTerritorios);
    scanf("%d", &defensor);
    
    if (atacante < 1 || atacante > totalTerritorios || 
        defensor < 1 || defensor > totalTerritorios ||
        atacante == defensor) {
        printf("❌ Escolha invalida!\n");
        return;
    }
    
    int idxAtacante = atacante - 1;
    int idxDefensor = defensor - 1;
    
    // Validar ataque
    if (strcmp(territorios[idxAtacante].cor, jogadorAtual->cor) != 0) {
        printf("❌ Territorio atacante nao e seu!\n");
        return;
    }
    
    if (strcmp(territorios[idxDefensor].cor, jogadorAtual->cor) == 0) {
        printf("❌ Nao pode atacar territorio aliado!\n");
        return;
    }
    
    if (territorios[idxAtacante].tropas <= 1) {
        printf("❌ Territorio atacante precisa ter mais de 1 tropa!\n");
        return;
    }
    
    // Executar batalha
    printf("\n⚔️  BATALHA: %s (%s) vs %s (%s)\n", 
           territorios[idxAtacante].nome, territorios[idxAtacante].cor,
           territorios[idxDefensor].nome, territorios[idxDefensor].cor);
    
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("🎲 Dados: Atacante %d x Defensor %d\n", dadoAtacante, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("✅ VITORIA! %s conquistou %s\n", jogadorAtual->nome, territorios[idxDefensor].nome);
        
        // Conquistar território
        strcpy(territorios[idxDefensor].cor, jogadorAtual->cor);
        territorios[idxDefensor].tropas = (territorios[idxDefensor].tropas / 2) + 1;
        
    } else {
        printf("❌ DERROTA! %s defendeu o territorio\n", territorios[idxDefensor].cor);
        // Penalidade para atacante
        if (territorios[idxAtacante].tropas > 1) {
            territorios[idxAtacante].tropas--;
        }
    }
}

void exibirMapa(const Territorio territorios[], int totalTerritorios) {
    printf("\n🗺️  MAPA ATUAL:\n");
    printf("====================\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("%d. %-15s - %-8s (%2d tropas)\n", 
               i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("====================\n");
}

void mostrarMenu(const Jogador* jogadorAtual) {
    printf("\n📋 VEZ DE: %s (%s)\n", jogadorAtual->nome, jogadorAtual->cor);
    printf("MENU PRINCIPAL:\n");
    printf("1. ⚔️  Atacar\n");
    printf("2. 🎯 Verificar Missao\n");
    printf("3. 🗺️  Ver Mapa\n");
    printf("0. 🚪 Finalizar Turno\n");
    printf("Escolha uma opcao: ");
}

void inicializarJogo(Jogador jogadores[MAX_JOGADORES], Territorio territorios[MAX_TERRITORIOS], int* totalTerritorios) {
    srand(time(NULL));
    
    printf("=== WAR ESTRUTURADO - NIVEL MESTRE ===\n\n");
    
    // Cadastrar jogadores
    printf("=== CADASTRO DE JOGADORES ===\n");
    for (int i = 0; i < MAX_JOGADORES; i++) {
        printf("\nJogador %d:\n", i+1);
        printf("Nome: ");
        scanf("%19s", jogadores[i].nome);
        printf("Cor do exercito: ");
        scanf("%9s", jogadores[i].cor);
        atribuirMissao(&jogadores[i]);
    }
    
    // Inicializar territórios automaticamente
    printf("\n=== INICIALIZANDO TERRITORIOS ===\n");
    *totalTerritorios = 6;

    const char* nomesTerritorios[] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia", "Mexico"};
    
    // Distribuir territórios entre os jogadores
    for (int i = 0; i < *totalTerritorios; i++) {
        strcpy(territorios[i].nome, nomesTerritorios[i]);
        
        // Alternar entre os jogadores para distribuição inicial
        if (i % 2 == 0) {
            strcpy(territorios[i].cor, jogadores[0].cor);
        } else {
            strcpy(territorios[i].cor, jogadores[1].cor);
        }
        
        territorios[i].tropas = 3 + (rand() % 3); // 3-5 tropas
        printf("✅ %s - %s (%d tropas)\n", territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    
    // Mostrar missões iniciais
    printf("\n=== MISSOES ATRIBUÍDAS ===\n");
    for (int i = 0; i < MAX_JOGADORES; i++) {
        exibirMissao(&jogadores[i]);
    }
}

void liberarMemoria(Jogador jogadores[MAX_JOGADORES]) {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        free(jogadores[i].missao);
    }
    printf("✅ Memoria liberada com sucesso!\n");
}

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    Jogador jogadores[MAX_JOGADORES];
    Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios;
    int jogadorAtual = 0;
    int vencedor = -1;
    int turno = 1;
    
    // inicialização do jogo
    inicializarJogo(jogadores, territorios, &totalTerritorios);
    
    printf("\n🎮 JOGO INICIADO! Pressione Enter para continuar...");
    getchar(); getchar();
    
    // loop principal do jogo
    while (vencedor == -1) {
        printf("\n🎪 === TURNO %d === 🎪\n", turno);
        printf("🎯 AGORA E A VEZ DO: %s (%s)\n", jogadores[jogadorAtual].nome, jogadores[jogadorAtual].cor);
        
        int opcao;
        int turnoAtivo = 1;
        
        while (turnoAtivo && vencedor == -1) {
            exibirMapa(territorios, totalTerritorios);
            mostrarMenu(&jogadores[jogadorAtual]);
            scanf("%d", &opcao);
            
            switch (opcao) {
                case 1: // atacar
                    executarAtaque(territorios, totalTerritorios, &jogadores[jogadorAtual]);
                    break;
                    
                case 2: // verificar Missão
                    exibirMissao(&jogadores[jogadorAtual]);
                    if (verificarMissao(&jogadores[jogadorAtual], territorios, totalTerritorios)) {
                        printf("🎉 PARABENS! %s cumpriu sua missao!\n", jogadores[jogadorAtual].nome);
                        vencedor = jogadorAtual;
                    } else {
                        printf("📝 Continue tentando para cumprir sua missao!\n");
                    }
                    break;
                    
                case 3: // ver Mapa
                    exibirMapa(territorios, totalTerritorios);
                    break;
                    
                case 0: // finalizar Turno
                    printf("⏭️  %s finalizou o turno.\n", jogadores[jogadorAtual].nome);
                    turnoAtivo = 0;
                    break;
                    
                default:
                    printf("❌ Opcao invalida! Tente novamente.\n");
            }
            
            // verifica vitória silenciosamente após cada ação
            if (vencedor == -1 && verificarMissao(&jogadores[jogadorAtual], territorios, totalTerritorios)) {
                vencedor = jogadorAtual;
                printf("🎉 PARABENS! %s cumpriu sua missao!\n", jogadores[jogadorAtual].nome);
            }
            
            if (turnoAtivo && vencedor == -1) {
                printf("\nPressione Enter para continuar seu turno...");
                getchar(); getchar();
            }
        }
        
        // alternar jogador apenas se ninguém venceu
        if (vencedor == -1) {
            jogadorAtual = (jogadorAtual + 1) % MAX_JOGADORES;
            
            // se voltou para o jogador 0, incrementa o turno
            if (jogadorAtual == 0) {
                turno++;
            }
            
            printf("\n🔄 Proximo jogador: %s\n", jogadores[jogadorAtual].nome);
            printf("Pressione Enter para comecar o turno...");
            getchar(); getchar();
        }
    }
    
    // fim do jogo
    printf("\n🎊 === FIM DO JOGO === 🎊\n");
    printf("🏆 VENCEDOR: %s (%s)\n", jogadores[vencedor].nome, jogadores[vencedor].cor);
    printf("🎯 Missao cumprida: %s\n", jogadores[vencedor].missao);
    
    printf("\n📊 SITUACAO FINAL:\n");
    exibirMapa(territorios, totalTerritorios);
    
    liberarMemoria(jogadores);
    return 0;
}