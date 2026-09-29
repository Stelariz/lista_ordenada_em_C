printf("== INSERINDO ==\n"); /*Imprime o cabeçalho de inserção no terminal com quebra de linha (\n).*/
    /*Inicia um laço que percorrerá cada elemento do vetor dados, de i = 0 até i < 6.*/
    for (int i = 0; i < n; i++) {
        inserir_ordenado(&L, dados[i]); /*Insere o valor dados[i] na lista mantendo a ordem crescente. O endereço &L permite que a função modifique a estrutura original da lista.*/
        printf("insere %2d -> ", dados[i]); /*Imprime a mensagem de inclusão no terminal. O %2d formata o número inteiro para ocupar pelo menos 2 caracteres, alinhando a saída visualmente.*/
        imprimir(&L); /*Exibe o estado atualizado da lista entre colchetes logo após a inserção.*/
    }