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

    int classe_idx = clientes_quantidade_classes(input); /* Pega o valor ASCII do input, e transforma em um número, que será o index da lista de quantidade de clientes por classe */

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

int atende_cliente(thash_t *hash, int *total_por_cliente) {
    for (int i = 0; i < CAPACIDADE_CLASSE; ++i) {
        if (total_por_cliente[i] > 0) {
            char *classe_num = converte_para_classe(i);
            printf("Atendendo cliente da senha: %s; ", thash_obtem(hash, classe_num));

            thash_remove(hash, classe_num);
            total_por_cliente[i]--;

            int total_restantes = 0;
            for (int j = 0; j < CAPACIDADE_CLASSE; ++j) {
                total_restantes += total_por_cliente[j]; /* Atualização do total de clientes */
            }

            if (total_restantes > 0) {
                printf("Clientes restantes na fila de espera: %d\n", total_restantes);
            } else {
                printf("Nenhum cliente na fila.\n");
            }
            free(classe_num);
            return 1;
        }
    }
    printf("Nenhum cliente na fila.\n");
    return 0;
}

int clientes_quantidade_classes(char *str) {
    char str_temp[10];
    strcpy(str_temp, str);

    for (int i = 0; str[i] != '\0'; i++) {
        str[i] -= 17; /* Transforma o caractere em um inteiro, para acessar o índice da lista da classe correspondente, exemplo: A => 0; B => 1; C => 2... */
    }
    return atoi(str);
}

char *converte_para_classe(int index) {
    char *classe_num = malloc(3);
    if (classe_num == NULL) return NULL;

    sprintf(classe_num, "%d", index);
    for (int i = 0; classe_num[i] != '\0'; i++) {
        classe_num[i] += 17; /* Transforma o inteiro em um caractere, para acessar a chave do hash que é a classe dos clientes, exemplo: 0 => A; 1 => B; 2 => C... */
    }

    return classe_num;
}