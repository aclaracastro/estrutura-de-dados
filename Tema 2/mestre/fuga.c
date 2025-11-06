#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct que representa um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Contadores globais
int comparacoesOrdenacao = 0;
int comparacoesBusca = 0;

// Função para exibir os componentes
void mostrarComponentes(Componente lista[], int n) {
    printf("\n🔧 Componentes da torre:\n");
    for (int i = 0; i < n; i++) {
        printf("🔹 Nome: %s | Tipo: %s | Prioridade: %d\n",
               lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente lista[], int n) {
    comparacoesOrdenacao = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesOrdenacao++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                Componente temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente lista[], int n) {
    comparacoesOrdenacao = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            lista[j + 1] = lista[j];
            j--;
            comparacoesOrdenacao++;
        }
        lista[j + 1] = chave;
        comparacoesOrdenacao++;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente lista[], int n) {
    comparacoesOrdenacao = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoesOrdenacao++;
            if (lista[j].prioridade < lista[min].prioridade) {
                min = j;
            }
        }
        Componente temp = lista[i];
        lista[i] = lista[min];
        lista[min] = temp;
    }
}

// Busca binária por nome (após ordenação por nome)
int buscaBinariaPorNome(Componente lista[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    comparacoesBusca = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBusca++;
        int cmp = strcmp(lista[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// Função para medir tempo de execução
void medirTempo(void (*algoritmo)(Componente[], int), Componente lista[], int n) {
    clock_t inicio = clock();
    algoritmo(lista, n);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("⏱️ Tempo de execução: %.6f segundos\n", tempo);
    printf("🔁 Comparações realizadas: %d\n", comparacoesOrdenacao);
}

// Função principal
int main() {
    Componente torre[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    char chaveBusca[30];

    // Cadastro dos componentes
    printf("🛠️ Cadastro dos componentes da torre:\n");
    while (total < MAX_COMPONENTES) {
        printf("\nComponente %d:\n", total + 1);
        printf("Nome: "); fgets(torre[total].nome, 30, stdin);
        torre[total].nome[strcspn(torre[total].nome, "\n")] = '\0';
        printf("Tipo: "); fgets(torre[total].tipo, 20, stdin);
        torre[total].tipo[strcspn(torre[total].tipo, "\n")] = '\0';
        printf("Prioridade (1 a 10): "); scanf("%d", &torre[total].prioridade);
        getchar(); // Limpa o buffer
        total++;

        char continuar;
        printf("Adicionar outro componente? (s/n): ");
        scanf("%c", &continuar);
        getchar();
        if (continuar != 's' && continuar != 'S') break;
    }

    // Menu de ordenação
    do {
        printf("\n📋 Escolha a estratégia de ordenação:\n");
        printf("1. Bubble Sort por nome\n");
        printf("2. Insertion Sort por tipo\n");
        printf("3. Selection Sort por prioridade\n");
        printf("0. Sair\n> ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                medirTempo(bubbleSortNome, torre, total);
                mostrarComponentes(torre, total);
                printf("\n🔑 Digite o nome do componente-chave para busca binária: ");
                fgets(chaveBusca, 30, stdin);
                chaveBusca[strcspn(chaveBusca, "\n")] = '\0';
                int pos = buscaBinariaPorNome(torre, total, chaveBusca);
                if (pos != -1) {
                    printf("✅ Componente encontrado: %s | %s | Prioridade: %d\n",
                           torre[pos].nome, torre[pos].tipo, torre[pos].prioridade);
                } else {
                    printf("❌ Componente não encontrado.\n");
                }
                printf("🔍 Comparações na busca binária: %d\n", comparacoesBusca);
                break;

            case 2:
                medirTempo(insertionSortTipo, torre, total);
                mostrarComponentes(torre, total);
                break;

            case 3:
                medirTempo(selectionSortPrioridade, torre, total);
                mostrarComponentes(torre, total);
                break;

            case 0:
                printf("🚀 Encerrando montagem da torre...\n");
                break;

            default:
                printf("⚠️ Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
