# Projeto 2: Fila de Prioridades - Com Hash Buckets

## 📌 Introdução

Este projeto foi desenvolvido para um sistema de atendimento a clientes baseado em uma fila de prioridades. O objetivo é gerenciar uma lista de clientes, onde o atendimento ocorre com base em suas classes de prioridade.

Cada cliente pertence a uma das categorias de prioridade, representadas pelas letras de 'A' (mais alta) até 'F' (mais baixa). O algoritmo garante que os clientes com maior prioridade sejam atendidos primeiro, respeitando a ordem de chegada dentro de cada nível de prioridade. 
### [Referência](https://moodle.ifsc.edu.br/mod/page/view.php?id=227839)

## 🛠 Ferramentas

Para implementar a fila de prioridades, utilizamos a biblioteca `libprg`, com a estrutura `THash`. Essa escolha foi feita porque os buckets armazenam listas de valores acessíveis por uma chave, facilitando a organização e recuperação dos elementos por prioridade.

* Código exemplo de teste de funcionalidade da biblioteca `THash.c`:
```C
int main(){
    thash_t *hash_exemplo = thash_cria();
    thash_adiciona(hash_exemplo, "A", "A000");
    thash_adiciona(hash_exemplo, "A", "A001");
    thash_adiciona(hash_exemplo, "A", "A002");
    thash_adiciona(hash_exemplo, "A", "A003");
    thash_adiciona(hash_exemplo, "B", "B000");
    thash_adiciona(hash_exemplo, "B", "B001");
    thash_adiciona(hash_exemplo, "B", "B002");
    thash_adiciona(hash_exemplo, "B", "B003");
    
    while(thash_tamanho(hash_exemplo) > 0){
        printf("%s\n", thash_obtem(hash_exemplo, "A"));
        thash_remove(hash_exemplo, "A");
        printf("%s\n", thash_obtem(hash_exemplo, "B"));
        thash_remove(hash_exemplo, "B");
    }
        
    return 0;
}
```

Executando o código, ele retorna:
```console
A000
B000
A001
B001
A002
B002
A003
B003
```

Isso ocorre porque, na estrutura desenvolvida, cada bucket armazena os pares chave-valor como uma única string, separando-os pelo caractere `\xFF`:

`THash.c`:
```C
// adiciona um par (chave, valor) à tabela hash
// retorna: 1=sucesso, 0=falha
int thash_adiciona(thash_t * tab, char * chave, char* valor) {
    uint32_t linha = hash_simples(chave, tab->linhas);
    if (!tab->tab[linha]) {
        tab->tab[linha] = lista_linear_cria();
    }

    char *novo_par = malloc(strlen(chave) + strlen(valor) + 2);
    sprintf(novo_par, "%s\xFF%s", chave, valor); // Usa \xFF para separar
    lista_linear_adiciona(tab->tab[linha], novo_par);
    tab->quantidade++;
    return 1;
}
```

A função 'thash_obtem' sempre retorna o primeiro elemento da lista. Analogamente, quando 'thash_remove' é usado, o primeiro valor é removido, e o bucket é organizado, tornado o próximo elemento o novo primeiro:

`THash.c`:
```C
// procura um par com determinada chave na tabela, e retorna o valor nele contido
// retorna: o valor, ou NULL em caso de falha
char* thash_obtem(thash_t * tab, char* chave) {
    uint32_t linha = hash_simples(chave, tab->linhas);
    if (!tab->tab[linha]) return NULL;
        for (int i = 0; i < lista_linear_comprimento(tab->tab[linha]); i++) {
            char *item = lista_linear_obtem(tab->tab[linha], i);
            if (strncmp(item, chave, strlen(chave)) == 0 && item[strlen(chave)] == '\xFF') {
                return item + strlen(chave) + 1;
            }
        }
    return NULL;
}

int thash_remove(thash_t * tab, char* chave) {
    uint32_t linha = hash_simples(chave, tab->linhas);
    if (!tab->tab[linha]) return 0;

    lista_linear_t *lista = tab->tab[linha];

    for (int i = 0; i < lista_linear_comprimento(lista); i++) {
        char *item = lista_linear_obtem(lista, i);
        // Verifica se o item possui a chave seguida pelo separador \xFF
        if (strncmp(item, chave, strlen(chave)) == 0 && item[strlen(chave)] == '\xFF') {
            // lista_linear_remove já realiza a compactação e libera o espaço do item
            lista_linear_remove(lista, item);
            tab->quantidade--;

            // Se a lista ficou vazia, liberamos a memória da própria lista
            if (lista_linear_comprimento(lista) == 0) {
                lista_linear_destroi(lista);
                tab->tab[linha] = NULL;
            }
            return 1;
        }
    }
    return 0;
}
```

## 🏗️ Desenvolvimento

O projeto final utiliza cinco bibliotecas, três constantes e quatro funções principais para gerenciar a fila de prioridades.

`main.c`:
```C
#include <stdio.h>
#include <libprg/libprg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CAPACIDADE_CLASSE 7
#define CLASSE_MAIOR_PRIORIDADE 'A'
#define CLASSE_MENOR_PRIORIDADE 'F'

int gerar_senha_cliente(thash_t *hash, char *input, int *total_por_cliente, int *senha_ordem);
int atende_cliente(thash_t *hash, int *total_por_cliente);
int clientes_quantidade_classes(char *str);
char *converte_para_classe(int index);
```

Na função de execução, ela aparenta ser pequena, porém é estruturada de forma que as principais ações fiquem na responsabilidade das funções criadas:

```C
int main() {
    printf("** Fila clientes: **\n");

    char input[100];
    thash_t *hash = thash_cria();
    int total_por_cliente[CAPACIDADE_CLASSE] = {}; /* Lista da quantidade total de clientes por classe (A-F) */
    int senha_ordem[CAPACIDADE_CLASSE] = {}; /* Lista da ordem das senhas */

    int ativado = 1;
    while(ativado){
        printf(">");
        scanf("%99s", input);

        if (strcmp(input, "sair") == 0) {
            ativado = 0;
        } else if (strcmp(input, "?") == 0) {
            atende_cliente(hash, total_por_cliente);
        } else {
            gerar_senha_cliente(hash, input, total_por_cliente, senha_ordem);
        }
    }

    thash_destroi(hash);
}
```

## 💻 Funções principais

### Função `gerar_senha_cliente`

A função `gerar_senha_cliente()` adiciona a senha correspondente ao input do usuário mais a ordem de chegada a uma tabela hash. Onde a função:

1. **Verifica se a entrada do usuário é válida**:
    * Verifica se o caractere é vazio.
    * Converte o caractere para maiúsculo.
    * Verifica se o caractere está entre A e F.

2. **Converte o input do usuário em um número inteiro** que será usado como indexador, usando a função já descrita anteriormente.

3. **Atualiza a contagem de clientes da classe especificada** e atualiza a ordem de clientes em espera na classe.

4. **Faz a contagem de clientes totais em espera**.

5. **Imprime a senha do usuário** e quantas pessoas estão na fila de atendimento.

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
---
### Função `clientes_quantidade_classes`

A função `clientes_quantidade_classes()` converte uma string que representa uma classe de cliente (por exemplo, "A", "B", "C") em um índice inteiro que será usado para acessar a lista de quantidade de clientes por classe. O funcionamento da função é descrito a seguir:

1. **Copia a string de entrada** para uma variável temporária para evitar modificar a entrada original.

2. **Percorre a string** até encontrar o caractere nulo (`\0`):
    * Para o caractere, em código ASCII, realiza-se uma operação aritmética subtraindo 17, o que converte o caractere em um número correspondente ao índice da classe:
        - 'A' se torna 0
        - 'B' se torna 1
        - 'C' se torna 2, e assim por diante.

3. **Converte a string resultante** em um número inteiro usando `atoi()` e retorna o índice.

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
---
### Função `converte_para_classe`

A função `converte_para_classe()` converte um índice inteiro (representando uma classe de cliente) de volta em um caractere correspondente à classe (por exemplo, 0 para "A", 1 para "B", etc.). O funcionamento da função é descrito a seguir:

1. **Aloca memória** para uma string que irá armazenar o número da classe em formato de string.

2. **Verifica se a alocação foi bem-sucedida**. Se não, retorna `NULL`.

3. **Converte o índice inteiro para string** usando `sprintf()`.

4. **Percorre a string resultante**:
    * Para cada caractere, realiza uma operação aritmética adicionando 17, o que converte o número de volta no caractere correspondente à classe:
        - 0 se torna 'A'
        - 1 se torna 'B'
        - 2 se torna 'C', e assim por diante.

5. **Retorna a string contendo a classe correspondente**.

```C
char *converte_para_classe(int index) {
    char *classe_num = malloc(3);
    if (classe_num == NULL) return NULL;

    sprintf(classe_num, "%d", index);
    for (int i = 0; classe_num[i] != '\0'; i++) {
        classe_num[i] += 17; /* Transforma o inteiro em um caractere, para acessar a chave do hash que é a classe dos clientes, exemplo: 0 => A; 1 => B; 2 => C... */
    }

    return classe_num;
}
```
---
### Função `atende_cliente`

A função `atende_cliente()` remove e exibe a senha do próximo cliente a ser atendido com base na prioridade da classe. A prioridade segue a ordem das classes (A é a mais prioritária e F a menos prioritária). Em caso de empate, o critério de desempate é a ordem de chegada. Onde a função:

1. **Conta o número total de clientes na fila**:
    * O programa percorre o vetor `quantidade`, que armazena a quantidade de clientes em cada classe (A a F), para calcular o total de clientes ainda na fila;


2. **Busca a classe de maior prioridade com clientes na fila**:
    * Percorre o vetor `quantidade` da classe A (índice 0) até a classe F (índice 5);
    * Se encontrar uma classe com clientes (quantidade[i] > 0), identifica essa classe como a próxima a ser atendida;


3. **Atende o cliente dessa classe**:
    * Converte o índice numérico da classe (0 a 5) para o caractere correspondente (A a F);
    * Obtém a senha do cliente armazenada na tabela hash (`thash_obtem()`);
    * Remove essa senha da tabela hash (`thash_remove()`);
    * Atualiza a quantidade de clientes na classe, decrementando `quantidade[i]`;


4. **Exibe informações sobre o atendimento**:
    * Mostra a senha do cliente que está sendo atendido;
    * Atualiza e exibe o total de clientes restantes na fila;


5. **Se a fila estiver vazia**:
    * Caso todas as classes estejam vazias, exibe a mensagem "Nenhum cliente na fila.";

```C
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

## 📊 Conclusão

A fila foi testada com diversas entradas e o sistema funcionou conforme esperado, atendendo clientes de acordo com sua prioridade. O código foi organizado para que as funções principais fossem de fácil compreensão e manutenção, garantindo que o sistema pudesse ser expandido ou modificado no futuro, se necessário.