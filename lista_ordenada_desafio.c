#include <stdio.h>
#include <stdlib.h>

/* Nó da lista: guarda a chave de ordenação e o ponteiro para o sucessor. */
typedef struct No {
    int chave; //chave de ordenação
    struct No *proximo; //ponteiro para o próximo nó
} No;

/* Descritor da lista: ponto de entrada + metadado de tamanho. */
typedef struct {
    No *inicio; /*ponteiro de início (aponta para o menor elemento da lista)*/
    int tamanho; /*quantidade de elementos na lista*/
} Lista;

/* Deixa a lista em estado vazio e consistente. */
void inicializar(Lista *L) {
    L->inicio = NULL; /*lista vazia*/
    L->tamanho = 0; /*nenhum elemento*/
}

/* Insere 'valor' mantendo a ordem crescente e PROÍBE DUPLICATAS. Retorna 1 em sucesso e 0 se a chave já existir ou se falhar a alocação. */
int inserir_sem_duplicadas(Lista *L, int valor) {
    No *anterior = NULL;
    No *atual = L->inicio;

    /* Avança enquanto a chave do nó atual for MENOR que o valor. */
    while (atual != NULL && atual->chave < valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    /* DESAFIO B: Checa duplicata no ponto de parada (custo O(1) adicional) */
    if (atual != NULL && atual->chave == valor) {
        return 0; /* Falha por chave duplicada - não aloca memória */
    }

    /* Alocação só ocorre se a chave for inédita */
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return 0; /* Falha por falta de memória */

    novo->chave = valor;
    novo->proximo = atual;

    if (anterior == NULL)
        L->inicio = novo;
    else
        anterior->proximo = novo;

    L->tamanho++;
    return 1; /* Sucesso */
}

/* Libera todos os nós e devolve a lista ao estado vazio. */
void destruir(Lista *L) {
    No *p = L->inicio; 
    while (p != NULL) {
        No *proximo = p->proximo; 
        free(p);
        p = proximo;
    L->inicio = NULL; 
    L->tamanho = 0;
    }
}

/*Declaração da função. Ela recebe o ponteiro L para a lista e apenas exibe seu conteúdo na tela sem alterar nada.*/
void imprimir(Lista *L) {
    printf("[");
    for (No *p = L->inicio; p != NULL; p = p->proximo)
        printf("%d%s", p->chave, p->proximo ? " -> " : ""); 
    printf("] (n=%d)\n", L->tamanho);
}

int main(void) {
    Lista L;
    inicializar(&L);

    int valor;
    char opcao;

    printf("=== TESTE INTERATIVO DE INSERCAO (DESAFIO B) ===\n\n");

    do {
        printf("Digite um numero inteiro para inserir na lista: ");
        if (scanf("%d", &valor) != 1) {
            printf("Entrada invalida! Encerrando...\n");
            break;
        }

        /* Chama a funcao e analisa o retorno imediatamente */
        if (inserir_sem_duplicadas(&L, valor)) {
            printf("-> Sucesso: O numero %d foi inserido na lista!\n", valor);
        } else {
            printf("-> Rejeitado: O numero %d JA EXISTE na lista (duplicata barrada)!\n", valor);
        }

        /* Exibe o estado atualizado da lista */
        printf("Estado atual da lista: ");
        imprimir(&L);
        printf("\n");

        printf("Deseja inserir outro numero? (s/n): ");
        scanf(" %c", &opcao); // O espaco antes de %c eh importante para ignorar o 'Enter' anterior
        printf("\n");

    } while (opcao == 's' || opcao == 'S');

    printf("Encerrando o programa e liberando a memoria...\n");
    destruir(&L);

    return 0;
}
