#include <stdio.h>
#include <libprg/libprg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CAPACIDADE_CLASSE 7
#define CLASSE_MAIOR_PRIORIDADE 'A'
#define CLASSE_MENOR_PRIORIDADE 'F'

void gerar_senha_cliente(thash_t *hash, char *input, int *quantidade);
void atende_cliente(thash_t *hash, int *quantidade);
void clientes_quantidade_classes(char *str);
void converte_para_classe(char *str);

int main() {
    printf("** Fila clientes: **\n");

    int ativado = 1;
    char input[100];
    thash_t *hash = thash_cria();
    int quantidade[CAPACIDADE_CLASSE] = {};

    while(ativado){
        printf(">");
        scanf("%99s", input);

        if (strcmp(input, "sair") == 0) {
            ativado = 0;
        } else if (strcmp(input, "?") == 0) {
            atende_cliente(hash, quantidade);
        } else {
            gerar_senha_cliente(hash, input, quantidade);
        }
    }

    thash_destroi(hash);
}

void gerar_senha_cliente(thash_t *hash, char *input, int *quantidade){
    input[0] = toupper(input[0]);

    if (input[0] < CLASSE_MAIOR_PRIORIDADE || input[0] > CLASSE_MENOR_PRIORIDADE) {
        printf("Classe inválida. As classes permitidas são de A a F.\n");
        return; // Sai da função se a classe for inválida
    }

    char *input_qnt_str = strdup(input);
    clientes_quantidade_classes(input_qnt_str);

    int classe_idx = atoi(input_qnt_str);
    if (classe_idx < 0 || classe_idx >= CAPACIDADE_CLASSE) {
        printf("Erro: Classe inválida!\n");
        free(input_qnt_str);
        return;
    }

    quantidade[classe_idx]++;

    int quantidade_clientes = 0;
    for (int i = 0; i < CAPACIDADE_CLASSE; i++) {
        quantidade_clientes += quantidade[i];
    }

    char buffer[10];

    sprintf(buffer, "%c%03d", input[0], quantidade[classe_idx] - 1);
    printf("Senha: %s; Quantia clientes na frente: %d;\n", buffer, quantidade_clientes);
    thash_adiciona(hash, input, buffer);
    free(input_qnt_str);
}

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

void clientes_quantidade_classes(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] -= 17;
    }
}

void converte_para_classe(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] += 17;
    }
}