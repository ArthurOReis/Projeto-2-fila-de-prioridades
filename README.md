# Projeto 2: fila de prioridades

* Código exemplo do `char *converte_para_classe()`:
```C
char *converte_para_classe(int index){
    char *classe_num = malloc(3);
    if (classe_num == NULL) return NULL;

    sprintf(classe_num, "%d", index);
    for (int i = 0; classe_num[i] != '\0'; i++) {
        classe_num[i] += 17; /* Transforma o inteiro em um caractere, para acessar a chave do hash que é a classe dos clientes, exemplo: 0 => A; 1 => B; 2 => C... */
    }

    return classe_num;
    }
```
Implementamos essa função para poder converter um valor inteiro de 0 até 5 para uma string de "A" até "f"

* Código exemplo do `int clientes_quantidade_classes(char *str)`:
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
Essa função é o inverso da "converte_para_classe", pois passamos uma string "a" até "f" e obtemos o seu correspondente de 0 até 5

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