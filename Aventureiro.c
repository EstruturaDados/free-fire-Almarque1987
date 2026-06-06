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
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                }
            } while(opcao != 0);
        }
    } while(estrutura != 0);

    printf("Saindo...\n");
    return 0;
}