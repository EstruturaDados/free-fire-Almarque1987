#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// Struct Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Função para mostrar componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n==== Componentes ====\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s %-15s Prioridade: %d\n", v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n) {
    int comparacoes = 0;
    clock_t inicio = clock();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
    clock_t fim = clock();
    printf("Bubble Sort concluído! Comparações: %d | Tempo: %.6f s\n", comparacoes, (double)(fim - inicio)/CLOCKS_PER_SEC);
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n) {
    int comparacoes = 0;
    clock_t inicio = clock();
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(chave.tipo, v[j].tipo) < 0) {
            comparacoes++;
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
    clock_t fim = clock();
    printf("Insertion Sort concluído! Comparações: %d | Tempo: %.6f s\n", comparacoes, (double)(fim - inicio)/CLOCKS_PER_SEC);
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n) {
    int comparacoes = 0;
    clock_t inicio = clock();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
    clock_t fim = clock();
    printf("Selection Sort concluído! Comparações: %d | Tempo: %.6f s\n", comparacoes, (double)(fim - inicio)/CLOCKS_PER_SEC);
}

// Busca Binária por nome
void buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(chave, v[meio].nome);
        if (cmp == 0) {
            printf("Componente encontrado: %s | %s | Prioridade %d\n", v[meio].nome, v[meio].tipo, v[meio].prioridade);
            printf("Comparações: %d\n", comparacoes);
            return;
        } else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    printf("Componente não encontrado. Comparações: %d\n", comparacoes);
}

// Função para medir tempo de execução de um algoritmo
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();
    printf("Tempo total: %.6f s\n", (double)(fim - inicio)/CLOCKS_PER_SEC);
}

// =====================
// Programa Principal
// =====================
int main() {
    Componente componentes[MAX];
    int n = 0, opcao;
    char chave[30];

    do {
        printf("\n==== MENU ====\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por nome (Bubble Sort)\n");
        printf("4 - Ordenar por tipo (Insertion Sort)\n");
        printf("5 - Ordenar por prioridade (Selection Sort)\n");
        printf("6 - Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1:
                if (n < MAX) {
                    printf("Nome: ");
                    fgets(componentes[n].nome, 30, stdin);
                    componentes[n].nome[strcspn(componentes[n].nome, "\n")] = 0;

                    printf("Tipo: ");
                    fgets(componentes[n].tipo, 20, stdin);
                    componentes[n].tipo[strcspn(componentes[n].tipo, "\n")] = 0;

                    printf("Prioridade (1-10): ");
                    scanf("%d", &componentes[n].prioridade);
                    getchar();

                    n++;
                    printf("Componente cadastrado!\n");
                } else {
                    printf("Limite de 20 componentes atingido!\n");
                }
                break;
            case 2:
                mostrarComponentes(componentes, n);
                break;
            case 3:
                bubbleSortNome(componentes, n);
                mostrarComponentes(componentes, n);
                break;
            case 4:
                insertionSortTipo(componentes, n);
                mostrarComponentes(componentes, n);
                break;
            case 5:
                selectionSortPrioridade(componentes, n);
                mostrarComponentes(componentes, n);
                break;
            case 6:
                printf("Digite o nome para buscar: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                buscaBinariaPorNome(componentes, n, chave);
                break;
        }
    } while(opcao != 0);

    printf("Saindo...\n");
    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
