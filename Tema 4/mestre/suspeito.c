#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// 🏠 Estrutura da sala da mansão
typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// 🌳 Estrutura da árvore BST de pistas
typedef struct PistaNode {
    char pista[50];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// 🔗 Estrutura da tabela hash (lista encadeada)
typedef struct HashNode {
    char pista[50];
    char suspeito[50];
    struct HashNode* prox;
} HashNode;

// Tabela hash global
HashNode* tabelaHash[TAM_HASH];

// 🔧 Função de espalhamento simples
int hash(const char* pista) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++) {
        soma += pista[i];
    }
    return soma % TAM_HASH;
}

// 🏗️ Cria uma sala com nome e pista
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (nova != NULL) {
        strcpy(nova->nome, nome);
        strcpy(nova->pista, pista);
        nova->esquerda = NULL;
        nova->direita = NULL;
    }
    return nova;
}

// 🧩 Insere uma pista na BST
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
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

// 🔗 Insere pista e suspeito na tabela hash
void inserirNaHash(const char* pista, const char* suspeito) {
    int indice = hash(pista);
    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    if (novo != NULL) {
        strcpy(novo->pista, pista);
        strcpy(novo->suspeito, suspeito);
        novo->prox = tabelaHash[indice];
        tabelaHash[indice] = novo;
    }
}

// 🔍 Consulta suspeito por pista
const char* encontrarSuspeito(const char* pista) {
    int indice = hash(pista);
    HashNode* atual = tabelaHash[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }
    return NULL;
}

// 📜 Exibe pistas em ordem alfabética
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s (Suspeito: %s)\n", raiz->pista, encontrarSuspeito(raiz->pista));
        exibirPistas(raiz->direita);
    }
}

// 👥 Lista suspeitos únicos associados às pistas
void listarSuspeitos(PistaNode* raiz, char suspeitos[][50], int* total) {
    if (raiz != NULL) {
        listarSuspeitos(raiz->esquerda, suspeitos, total);
        const char* suspeito = encontrarSuspeito(raiz->pista);
        int jaExiste = 0;
        for (int i = 0; i < *total; i++) {
            if (strcmp(suspeitos[i], suspeito) == 0) {
                jaExiste = 1;
                break;
            }
        }
        if (!jaExiste && suspeito != NULL) {
            strcpy(suspeitos[*total], suspeito);
            (*total)++;
        }
        listarSuspeitos(raiz->direita, suspeitos, total);
    }
}

// 🚪 Explora salas e coleta pistas
void explorarSalas(Sala* atual, PistaNode** arvorePistas) {
    char escolha;
    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("🔍 Pista encontrada: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }
        printf("Escolha o caminho: (e) esquerda, (d) direita, (s) sair, (1) listar suspeitos: ");
        scanf(" %c", &escolha);
        if (escolha == 'e') atual = atual->esquerda;
        else if (escolha == 'd') atual = atual->direita;
        else if (escolha == '1') {
            char suspeitos[10][50];
            int total = 0;
            listarSuspeitos(*arvorePistas, suspeitos, &total);
            printf("\n👥 Suspeitos associados às pistas:\n");
            for (int i = 0; i < total; i++) {
                printf("- %s\n", suspeitos[i]);
            }
        }
        else if (escolha == 's') break;
        else printf("Opção inválida.\n");
    }
}

// ⚖️ Verifica se o suspeito tem pelo menos 2 pistas
void verificarSuspeitoFinal(PistaNode* raiz, const char* acusado, int* cont) {
    if (raiz != NULL) {
        verificarSuspeitoFinal(raiz->esquerda, acusado, cont);
        const char* suspeito = encontrarSuspeito(raiz->pista);
        if (suspeito != NULL && strcmp(suspeito, acusado) == 0)
            (*cont)++;
        verificarSuspeitoFinal(raiz->direita, acusado, cont);
    }
}

// 🧹 Libera memória da BST
void liberarPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// 🧹 Libera memória da tabela hash
void liberarHash() {
    for (int i = 0; i < TAM_HASH; i++) {
        HashNode* atual = tabelaHash[i];
        while (atual != NULL) {
            HashNode* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

// 🚀 Função principal
int main() {
    // Criação das salas
    Sala* hall = criarSala("Hall de Entrada", "");
    Sala* salaEstar = criarSala("Sala de Estar", "Pegada na cortina");
    Sala* cozinha = criarSala("Cozinha", "Faca suja na pia");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala* jardim = criarSala("Jardim", "Luvas enterradas");

    // Montagem da árvore da mansão
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    // Associação pista → suspeito
    inserirNaHash("Pegada na cortina", "Carlos");
    inserirNaHash("Faca suja na pia", "Ana");
    inserirNaHash("Livro rasgado", "Carlos");
    inserirNaHash("Luvas enterradas", "Beatriz");

    // Exploração
    PistaNode* arvorePistas = NULL;
    printf("🕵️ Bem-vindo ao Detective Quest - Nível Mestre!\nExplore a mansão e colete pistas.\n");
    explorarSalas(hall, &arvorePistas);

    // Exibição
    printf("\n📜 Pistas coletadas:\n");
    exibirPistas(arvorePistas);

    // Julgamento
    char acusado[50];
    printf("\n⚖️ Quem você acusa como culpado? ");
    scanf(" %[^\n]", acusado);
    int cont = 0;
    verificarSuspeitoFinal(arvorePistas, acusado, &cont);
    if (cont >= 2)
        printf("✅ Acusação válida! %s está ligado a %d pistas.\n", acusado, cont);
    else
        printf("❌ Acusação fraca. Apenas %d pista(s) apontam para %s.\n", cont, acusado);

    // Liberação de memória
   liberarPistas(arvorePistas);
   liberarHash();
   free(jardim);
   free(biblioteca);
   free(cozinha);
   free(salaEstar);
   free(hall);
    
    return 0;
}

//Carlos - pegada na cortina, livro rasgado
//Ana - faca suja na pia
//Beatriz - luvas enterradas