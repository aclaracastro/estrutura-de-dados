#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void cadastrarTerritorios(struct Territorio* territorios, int quantidade);
void exibirTerritorios(struct Territorio* territorios, int quantidade);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* territorios);

void cadastrarTerritorios(struct Territorio* territorios, int quantidade) {
    printf("=== CADASTRO DE TERRITORIOS ===\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("--- Territorio %d ---\n", i + 1);
        
        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
}

void exibirTerritorios(struct Territorio* territorios, int quantidade) {
    printf("\n=== TERRITORIOS CADASTRADOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
    }
    printf("------------------------\n");
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n=== INICIANDO ATAQUE ===\n");
    printf("%s (%s) ataca %s (%s)\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATACANTE!\n");
        
        int tropasPerdidas = defensor->tropas;
        defensor->tropas = 0;
        
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasPerdidas / 2;  
        
        printf("%s agora pertence a %s\n", defensor->nome, atacante->cor);
        printf("Tropas em %s: %d\n", defensor->nome, defensor->tropas);
        
    } else {
        printf("VITORIA DO DEFENSOR!\n");
        
        atacante->tropas--;
        printf("%s perdeu 1 tropa. Tropas restantes: %d\n", 
               atacante->nome, atacante->tropas);
    }
}

void liberarMemoria(struct Territorio* territorios) {
    free(territorios);
    printf("Memoria liberada com sucesso!\n");
}

int main() {
    srand(time(NULL)); 
    
    int quantidadeTerritorios;
    
    printf("=== WAR ESTRUTURADO ===\n");
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidadeTerritorios);
    
    struct Territorio* territorios = (struct Territorio*) 
        malloc(quantidadeTerritorios * sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    cadastrarTerritorios(territorios, quantidadeTerritorios);
    
    exibirTerritorios(territorios, quantidadeTerritorios);
    
    char continuar;
    do {
        int indiceAtacante, indiceDefensor;
        
        printf("\n=== SELECAO DE ATAQUE ===\n");
        
        printf("Escolha o territorio ATACANTE (1 a %d): ", quantidadeTerritorios);
        scanf("%d", &indiceAtacante);
        indiceAtacante--;  
      
        printf("Escolha o territorio DEFENSOR (1 a %d): ", quantidadeTerritorios);
        scanf("%d", &indiceDefensor);
        indiceDefensor--;  
   
        if (indiceAtacante < 0 || indiceAtacante >= quantidadeTerritorios ||
            indiceDefensor < 0 || indiceDefensor >= quantidadeTerritorios) {
            printf("Indices invalidos!\n");
            continue;
        }
        
        if (strcmp(territorios[indiceAtacante].cor, territorios[indiceDefensor].cor) == 0) {
            printf("Nao pode atacar territorio da mesma cor!\n");
            continue;
        }
        
        if (territorios[indiceAtacante].tropas <= 0) {
            printf("Territorio atacante nao tem tropas suficientes!\n");
            continue;
        }
        
        atacar(&territorios[indiceAtacante], &territorios[indiceDefensor]);

        exibirTerritorios(territorios, quantidadeTerritorios);
        
        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        
    } while (continuar == 's' || continuar == 'S');
    
    liberarMemoria(territorios);
    
    printf("\nJogo finalizado!\n");
    return 0;
}