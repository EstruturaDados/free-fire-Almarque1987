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

// =====================
// Estruturas
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =====================
// Variáveis globais
// =====================
Item mochilaVetor[10];
int numItensVetor = 0;
int comparacoes = 0;
int ordenadaPorNome = 0;

No* mochilaLista = NULL;

// =====================
// Funções Vetor
// =====================
void inserirItemVetor() {
    if (numItensVetor >= 10) {
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome: ");
    scanf("%s", mochilaVetor[numItensVetor].nome);
    printf("Tipo: ");
    scanf("%s", mochilaVetor[numItensVetor].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[numItensVetor].quantidade);

    numItensVetor++;
    ordenadaPorNome = 0;
    printf("Item inserido!\n");
}

void removerItemVetor() {
    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(nomeBusca, mochilaVetor[i].nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item não encontrado.\n");
        return;
    }

    for (int i = encontrado; i < numItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    numItensVetor--;
    printf("Item removido!\n");
}

void listarItensVetor() {
    printf("\n==== Mochila (Vetor) ====\n");
    if (numItensVetor == 0) {
        printf("Vazia.\n");
        return;
    }
    for (int i = 0; i < numItensVetor; i++) {
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void buscarSequencialVetor() {
    char nomeBusca[30];
    printf("Digite o nome: ");
    scanf("%s", nomeBusca);

    comparacoes = 0;
    for (int i = 0; i < numItensVetor; i++) {
        comparacoes++;
        if (strcmp(nomeBusca, mochilaVetor[i].nome) == 0) {
            printf("Encontrado: %s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoes);
            return;
        }
    }
    printf("Item não encontrado. Comparações: %d\n", comparacoes);
}

void ordenarVetor() {
    comparacoes = 0;
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    ordenadaPorNome = 1;
    printf("Ordenado por nome! Comparações: %d\n", comparacoes);
}

void buscarBinariaVetor() {
    if (!ordenadaPorNome) {
        printf("Mochila não está ordenada por nome!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome: ");
    scanf("%s", nomeBusca);

    int inicio = 0, fim = numItensVetor - 1;
    comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(nomeBusca, mochilaVetor[meio].nome);

        if (cmp == 0) {
            printf("Encontrado: %s | %s | %d\n", mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações: %d\n", comparacoes);
            return;
        } else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    printf("Item não encontrado. Comparações: %d\n", comparacoes);
}

// =====================
// Funções Lista Encadeada
// =====================
void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));
    printf("Nome: ");
    scanf("%s", novo->dados.nome);
    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;
    printf("Item inserido!\n");
}

void removerItemLista() {
    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeBusca);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL) mochilaLista = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
}

void listarItensLista() {
    printf("\n==== Mochila (Lista Encadeada) ====\n");
    No* atual = mochilaLista;
    if (atual == NULL) {
        printf("Vazia.\n");
        return;
    }
    while (atual != NULL) {
        printf("%s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    char nomeBusca[30];
    printf("Digite o nome: ");
    scanf("%s", nomeBusca);

    comparacoes = 0;
    No* atual = mochilaLista;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("Encontrado: %s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado. Comparações: %d\n", comparacoes);
}

// =====================
// Menu Principal
// =====================
int main() {
    int opcao, estrutura;
    do {
        printf("\n==== MENU ====\n");
        printf("1 - Usar Mochila (Vetor)\n");
        printf("2 - Usar Mochila (Lista Encadeada)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &estrutura);

        if (estrutura == 1) {
            do {
                printf("\n--- Mochila Vetor ---\n");
                printf("1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n5 - Ordenar por Nome\n6 - Buscar Binária\n0 - Voltar\n");
                scanf("%d", &opcao);
                switch(opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: ordenarVetor(); break;
                    case 6: buscarBinariaVetor(); break;
                }
            } while(opcao != 0);
        } else if (estrutura == 2) {
            do {
                printf("\n--- Mochila Lista ---\n");
                printf("1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar Sequencial\n0 - Voltar\n");
                scanf("%d", &opcao);
                switch(opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItens

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
