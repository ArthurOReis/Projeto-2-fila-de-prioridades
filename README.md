# Projeto 2: fila de prioridades

* Código exemplo do `main.c`:
```C
    int clientes_quantidade_classes(char *str) {
        char str_temp[10];
        strcpy(str_temp, str);

        for (int i = 0; str[i] != '\0'; i++) {
            str[i] -= 17; /* Transforma o caractere em um inteiro, para acessar o índice da lista da classe correspondente, exemplo: A => 0; B => 1; C => 2... */
        }
        return atoi(str);
}
```

* Função `Atende Cliente`:
```
void atende_cliente(thash_t *hash, int *quantidade) {
    int total_restante = 0;

    for (int j = 0; j < CAPACIDADE_CLASSE; j++) {
        total_restante += quantidade[j];
    }

    for (int i = 0; i < CAPACIDADE_CLASSE; ++i) {
        if (quantidade[i] > 0) {
            char classe_num[2];
            sprintf(classe_num, "%d", i);

            converte_para_classe(classe_num);
            printf("Atendendo cliente da senha: %s; ", thash_obtem(hash, classe_num));
            thash_remove(hash, classe_num);
            quantidade[i] -= 1;

            int total_restantes = 0;
            for (int j = 0; j < CAPACIDADE_CLASSE; ++j) {
                total_restantes += quantidade[j];
            }

            if (total_restantes > 0) {
                printf("Clientes restantes na fila de espera: %d\n", total_restantes);
            } else {
                printf("Nenhum cliente na fila.\n");
            }
            return; // Sai da função após atender um cliente
        }
    }
    printf("Nenhum cliente na fila.\n"); // Se não encontrou clientes
}
```

A função atende_cliente() remove e exibe a senha do próximo cliente a ser atendido com base na
prioridade da classe. A prioridade segue a ordem das classes (A é a mais prioritária e F a menos 
prioritária). Em caso de empate, o critério de desempate é a ordem de chegada. Onde a função:

1. Conta o número total de clientes na fila

* O programa percorre o vetor quantidade, que armazena a quantidade de clientes em cada classe (A a F), para calcular o total de clientes ainda na fila.

2. Busca a classe de maior prioridade com clientes na fila

* Percorre o vetor quantidade da classe A (índice 0) até a classe F (índice 5).
* Se encontrar uma classe com clientes (quantidade[i] > 0), identifica essa classe como a próxima a ser atendida.

3. Atende o cliente dessa classe

* Converte o índice numérico da classe (0 a 5) para o caractere correspondente (A a F).
* Obtém a senha do cliente armazenada na tabela hash (thash_obtem()).
* Remove essa senha da tabela hash (thash_remove()).
* Atualiza a quantidade de clientes na classe, decrementando quantidade[i].

4. Exibe informações sobre o atendimento

* Mostra a senha do cliente que está sendo atendido.
* Atualiza e exibe o total de clientes restantes na fila.

5. Se a fila estiver vazia

* Caso todas as classes estejam vazias, exibe a mensagem "Nenhum cliente na fila.".
Essa função é o inverso da "converte_para_classe", pois passamos uma string "a" até "f" e obtemos o seu correspondente de 0 até 5

---

* Código exemplo do `int gerar_senha_cliente(thash_t *hash, char *input, int *total_por_cliente, int *senha_ordem)`:
```C
int gerar_senha_cliente(thash_t *hash, char *input, int *total_por_cliente, int *senha_ordem){
    if (input[0] == '\0') {
        printf("Entrada inválida.\n");
        return 0;
    }
    input[0] = toupper(input[0]); /* Converte a primeira letra da entrada para maiúscula */

    if (input[0] < CLASSE_MAIOR_PRIORIDADE || input[0] > CLASSE_MENOR_PRIORIDADE) {
        printf("Classe inválida. As classes permitidas são de 'A' a 'F'.\n");
        return 0;
    }

    int classe_idx = clientes_quantidade_classes(strdup(input)); /* Pega o valor ASCII do input, e transforma em um número, que será o index da lista de quantidade de clientes por classe */

    if (classe_idx < 0 || classe_idx >= CAPACIDADE_CLASSE) {
        printf("Erro: Classe inválida!\n");
        return 0;
    }

    total_por_cliente[classe_idx]++; /* Atualiza a contagem de clientes da classe especificada */
    senha_ordem[classe_idx]++; /* Atualiza a ordem de clientes da classe especificada */

    int quantidade_total = 0;
    for (int i = 0; i < CAPACIDADE_CLASSE; ++i) {
        quantidade_total += total_por_cliente[i]; /* Somatória do total de clientes */
    }

    char buffer[10];
    sprintf(buffer, "%c%03d", input[0], senha_ordem[classe_idx] - 1); /* Organizando string para ficar no formato 'Xnnn' (X: letra correspondente à classe de cliente, nnn: contador de clientes) */

    printf("Senha: %s; Quantia clientes na frente: %d;\n", buffer, quantidade_total);
    thash_adiciona(hash, input, buffer);

    return 1;
}
```

A função gerar_senha_cliente() adicio a senha correspondente ao input do usuario mais a ordem de chegada a uma tabela hash. Onde a função

1. Verifica se a entrada do usuario é valida
* Verifica se o charactere é vazio.
* Converte o caractere para maiusculo.
* Verifica se o caractere está entre A e F.

2. converte o input do usuario em um numero interio que sera usado com indexador, usando a função já descrita antes
3. Atualiza a contagem de clientes da classe especificada e Atualiza a ordem de clientes em espera na classe
4. faz a contagem de clientes totais em espera
5. printa a senha do usuario e quantas pessoas estão na fila de atendimento