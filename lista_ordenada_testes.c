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

/* Insere 'valor' mantendo a ordem crescente. Retorna 1 em sucesso, 0 em falha. */
int inserir_ordenado(Lista *L, int valor) {
    No *novo = (No *) malloc(sizeof(No)); /*cria um novo nó na memória RAM*/
    if (novo == NULL) return 0; /*verifica se a alocação falhou (por falta de memória). Se falhar, a função para e retorna 0 (erro).*/
    novo->chave = valor; /*define que a chave do nó será o valor passado por parâmetro*/ 
    novo->proximo = NULL; /*temporariamente, coloca o ponteiro proximo apontando para NULL.*/

    No *anterior = NULL; /*acompanha o nó anterior*/
    No *atual = L->inicio; /*o nó atual da varredura (começa no primeiro elemento da lista, L->inicio)*/

    /* Avança enquanto a chave do nó atual for MENOR que o valor. */
    while (atual != NULL && atual->chave < valor) { /*Quando o while encontra um número maior ou igual (ou chega ao fim da lista), ele para, deixando anterior e atual exatamente onde o novo nó deve ser "costurado".*/
        anterior = atual; /*copia o endereço de memória contido em atual para dentro da variável anterior*/                      
        atual = atual->proximo; /*comando padrão para caminhar/avançar um passo para a frente na lista encadeada. Move o seu cursor: faz você andar para o próximo nó da lista. A estrutura da lista não muda.*/
    }

    novo->proximo = atual; /*Faz o campo proximo do seu novo nó apontar o nó atual. Ela diz:"Guarde dentro do meu campo proximo o mesmo endereço de memória que está armazenado no ponteiro atual".*/

    if (anterior == NULL)
        L->inicio = novo; /*altera o ponteiro de início da lista para apontar para a caixinha inteira do novo nó*/
    else
        anterior->proximo = novo; /*altera a seta de saída do nó anterior. Altera a estrutura da lista: faz o nó anterior apontar para o novo nó. Você não sai do lugar.*/

    L->tamanho++; /*incrementa o tamanho da lista*/

    return 1; /*Retorna 1 indicando para a main que a ordenação foi realizada com sucesso.*/
}

/* Retorna o nó com a chave procurada, ou NULL. Escreve em *comparacoes quantos nós foram efetivamente examinados.*/
No *buscar_ordenado(Lista *L, int valor, int *comparacoes) {
    No *ptr = L->inicio; /*Cria o ponteiro cursor de varredura ptr e o posiciona no primeiro elemento da lista (L->inicio).*/
    int cont = 0; /*Cria a variável inteira cont inicializada com 0. Ela funcionará como um contador interno para registrar quantas comparações a nós foram realizadas durante a busca.*/

    /*Inicia o laço de repetição. Ele continuará executando enquanto o ponteiro ptr for diferente de NULL — ou seja, enquanto não tiver percorrido toda a lista ou saído dela.*/
    while (ptr != NULL) { 
        cont++; /*Incremente o contador de visitas (cont = cont + 1). Toda vez que entramos no laço para analisar um nó, somamos 1 na contagem.*/

        /*Testa se o valor guardado no campo chave do nó atual (ptr->chave) é igual ao valor procurado.*/
        if (ptr->chave == valor) { 
            /*Verifica se o parâmetro comparacoes não é NULL (uma trava de segurança caso a função seja chamada sem passar esse ponteiro). Se ele for válido, grava o total do contador cont na memória da variável apontada por comparacoes (usando o * para modificar o valor original).*/
            if (comparacoes) *comparacoes = cont; 
            return ptr; /*Retorna imediatamente o ponteiro ptr (o endereço do nó onde a chave foi encontrada), encerrando a execução da função aqui.*/
        }

        /*Testa a condição de parada antecipada: verifica se a chave do nó atual é maior do que o valor que estamos buscando.*/
        if (ptr->chave > valor) { 
            break; /*Se o nó atual possui uma chave maior que o valor, o laço while é interrompido imediatamente. Como a lista é mantida ordenada em ordem crescente, se já encontramos um número maior, é impossível que o valor buscado apareça nos nós seguintes.*/
        }

        ptr = ptr->proximo; /*Avança o cursor ptr para o próximo nó da lista, pegando o endereço guardado em proximo.*/
    }

    /*Executado apenas quando o valor não foi encontrado (seja por chegar ao fim da lista NULL ou por ter acionado o break). Ele garante que a contagem final de comparações feitas até a interrupção seja gravada na variável apontada por comparacoes.*/
    if (comparacoes) *comparacoes = cont; 
    return NULL; /*Retorna NULL para indicar a quem chamou a função que o elemento procurado não existe na lista.*/
}

/* Remove a primeira ocorrência de 'valor'. Retorna 1 se removeu, 0 caso contrário. */
int remover(Lista *L, int valor) {
    No *anterior = NULL; /*Cria o ponteiro anterior e o inicializa com NULL. Ele servirá como uma "âncora" para guardar a referência do nó que fica atrás do cursor principal.*/
    No *atual = L->inicio; /*Cria o ponteiro cursor de varredura atual e o posiciona no primeiro nó da lista (L->inicio).*/

    /*Inicia o laço de busca aproveitando a ordenação. Ele continua avançando enquanto o nó existir (atual != NULL) E a chave armazenada nele for menor do que o valor que queremos remover (atual->chave < valor).*/
    while (atual != NULL && atual->chave < valor) { 
        anterior = atual; /*Atualiza a "âncora": faz o ponteiro anterior apontar para a mesma caixinha em que o cursor atual está parado antes de ele avançar.*/
        atual = atual->proximo; /*Avança o cursor atual para o próximo nó da lista.*/
    }

    /*Verifica se a busca falhou. A remoção não acontece se:   atual == NULL: Chegou ao final da lista sem encontrar o elemento.   atual->chave != valor: Encontrou um nó com valor maior que o procurado (já "passou do ponto" devido à ordenação).*/
    if (atual == NULL || atual->chave != valor) 
    return 0; /*Se entrou no if acima, retorna 0 encerrando a função, pois o elemento não existe na lista.*/

    /*Testa se o nó a ser removido é o primeiro nó da lista. Se anterior continuar valendo NULL, significa que o while nem rodou e o nó que queremos remover é o L->inicio.*/
    if (anterior == NULL)
        L->inicio = atual->proximo; /*Como o primeiro nó está sendo removido, o ponteiro de início da lista (L->inicio) passa a apontar diretamente para o segundo nó (atual->proximo).*/
    else
        anterior->proximo = atual->proximo; /*"Costura" a lista ao redor do nó a ser removido. A seta de saída do nó anterior (anterior->proximo) pula o nó atual e se conecta diretamente ao nó que vem depois dele (atual->proximo).*/

    free(atual); /*Devolve para o sistema operacional o bloco de memória RAM que estava alocado para o nó atual, evitando vazamento de memória (memory leak).*/
    L->tamanho--; /*Decrementa a contagem do tamanho da lista no descritor.*/
    return 1; /*Retorna 1 indicando para a main que a remoção foi realizada com sucesso.*/
}

/* Libera todos os nós e devolve a lista ao estado vazio. */
void destruir(Lista *L) {
    No *p = L->inicio; /*Cria o ponteiro cursor p e o posiciona no primeiro elemento da lista (L->inicio)*/
    /*Inicia o laço de repetição. Ele continuará executando enquanto houver nós para desalocar na memória (enquanto p for diferente de NULL).*/
    while (p != NULL) {
        No *proximo = p->proximo; /*Passo crítico de segurança. Salva o endereço do próximo nó na variável temporária proximo antes de apagar o nó atual. Se você não salvar essa referência primeiro, perderá o acesso ao restante da lista assim que liberar p.*/
        free(p); /*Libera a memória RAM do nó em que o ponteiro p está parado.*/
        p = proximo; /*Avança o cursor p para o nó guardado na variável proximo, preparando-o para a próxima iteração do laço.*/
    }
    L->inicio = NULL; /*Reseta o ponteiro de início da lista no descritor para NULL, garantindo que a lista fique vazia e sem ponteiros pendentes (dangling pointers).*/
    L->tamanho = 0; /*Zera o contador de elementos no descritor.*/
}

/*Declaração da função. Ela recebe o ponteiro L para a lista e apenas exibe seu conteúdo na tela sem alterar nada.*/
void imprimir(Lista *L) {
    printf("["); /*Imprime o caractere de abertura de colchete [ no terminal para iniciar a formatação da lista.*/
    /*No *p = L->inicio: Cria o cursor p apontando para o primeiro nó. p != NULL: Continua enquanto o cursor não chegar ao fim da lista. p = p->proximo: Avança para o próximo nó a cada iteração. */
    for (No *p = L->inicio; p != NULL; p = p->proximo)
        printf("%d%s", p->chave, p->proximo ? " -> " : ""); /*Imprime o número contido no nó atual (p->chave). Se o nó tiver um sucessor (p->proximo != NULL), imprime a seta " -> "; se for o último nó (p->proximo == NULL), imprime uma string vazia "" para não deixar uma seta sobrando no final.*/
    printf("] (n=%d)\n", L->tamanho); /*Imprime o fechamento do colchete ], exibe o tamanho total da lista guardado em L->tamanho.*/
}

/*Cenário T1 - Lista vazia.*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    printf("T1 - Lista Vazia: ");
    imprimir(&L);

    destruir(&L);
    return 0;
}
#endif

/*Cenário T2 - Primeira inserção.*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("T2 - Primeira insercao: ");
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }
    
    destruir(&L);
    return 0;
}
#endif

/*Cenário T3 - Inserção no inicio.*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("T3 - Insercao no inicio: ");
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }

    destruir(&L);
    return 0;
}
#endif

/*Cenário T4 - Inserção no fim.*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {10, 40, 75};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("T4 - Insercao no fim: ");
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }

    destruir(&L);
    return 0;
}
#endif

/*Cenário T5 - Inserção no meio.*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {10, 75, 40};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("T5 - Insercao no meio: ");
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }

    destruir(&L);
    return 0;
}
#endif

/*Cenário T6 - Entrada já ordenada*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {1, 2, 3, 4, 5};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("T6 - Entrada ja ordenada: ");
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }

    destruir(&L);
    return 0;
}
#endif

/*Cenário T7 - Entrada invertida*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {5, 4, 3, 2, 1};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("T7 - Entrada invertida: ");
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }

    destruir(&L);
    return 0;
}
#endif

/*Cenário T8 - Chaves duplicadas*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {20, 20, 20};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("T8 - Chaves duplicadas: ");
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }

    destruir(&L);
    return 0;
}
#endif

/*Cenário T9 - Busca com sucesso no 1º*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10, 75, 30, 90, 25};
    int n = sizeof(dados) / sizeof(dados[0]);

    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]);
    }

    int comps = 0;
    int x = 10;
    No *r = buscar_ordenado(&L, x, &comps);
    printf("T9 - Busca no 1o elemento: busca %d: %s (%d comparacoes)\n", x, r ? "ENCONTRADO" : "AUSENTE", comps);

    destruir(&L);
    return 0;
}
#endif

/*Cenário T10 - Busca ausente no meio*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10, 75, 30, 90, 25};
    int n = sizeof(dados) / sizeof(dados[0]);

    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]);
    }

    int comps = 0;
    int x = 60;
    No *r = buscar_ordenado(&L, x, &comps);
    printf("T10 - Busca ausente no meio: busca %d: %s (%d comparacoes)\n", x, r ? "ENCONTRADO" : "AUSENTE", comps);

    destruir(&L);
    return 0;
}
#endif

/*Cenário T11 - Busca ausente acima do máximo*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10, 75, 30, 90, 25};
    int n = sizeof(dados) / sizeof(dados[0]);

    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]);
    }

    int comps = 0;
    int x = 999;
    No *r = buscar_ordenado(&L, x, &comps);
    printf("T11 - Busca ausente acima do maximo: busca %d: %s (%d comparacoes)\n", x, r ? "ENCONTRADO" : "AUSENTE", comps);

    destruir(&L);
    return 0;
}
#endif

/*Cenário T12 - Remove o primeiro*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10, 75, 30, 90, 25};
    int n = sizeof(dados) / sizeof(dados[0]);

    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]);
    }
    imprimir(&L);

    int alvo = 10;
    int ok = remover(&L, alvo);
    printf("T12 - Remove o primeiro: %3d [%s] -> ", alvo, ok ? "ok" : "--");
    imprimir(&L);

    destruir(&L);
    return 0;
}
#endif

/*Cenário T13 - Remove o último*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10, 75, 30, 90, 25};
    int n = sizeof(dados) / sizeof(dados[0]);

    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]);
    }
    imprimir(&L);

    int alvo = 90;
    int ok = remover(&L, alvo);
    printf("T13 - Remove o ultimo: %3d [%s] -> ", alvo, ok ? "ok" : "--");
    imprimir(&L);

    destruir(&L);
    return 0;
}
#endif

/*Cenário T14 - Remove inexistente*/
#if 0
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10, 75, 30, 90, 25};
    int n = sizeof(dados) / sizeof(dados[0]);

    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]);
    }
    imprimir(&L);

    int alvo = 999;
    int ok = remover(&L, alvo);
    printf("T14 - Remove inexistente: %3d [%s] -> ", alvo, ok ? "ok" : "--");
    imprimir(&L);

    destruir(&L);
    return 0;
}
#endif

/*Cenário T15 - Esvaziar e reinserir*/
#if 1
int main (void) {
    Lista L;
    inicializar(&L);

    int dados[] = {40, 10, 75, 30, 90, 25};
    int n = sizeof(dados) / sizeof(dados[0]);

    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); 
        imprimir(&L);
    }

    destruir(&L);
    printf("\nLista destruida. Tamanho final: %d\n", L.tamanho);

    printf("\nT15 - Esvaziar e reinserir: ");

    int dado = 7;

    inserir_ordenado(&L, dado); 
    imprimir(&L);

    destruir(&L);
    return 0;
}
#endif