#include <stdio.h>
#include <string.h>
#include <libprg/libprg.h>
#include <stdlib.h>

void clientes_quantidade_classes(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] -= 17;
    }
}

void gerar_senha_cliente(thash_t *hash, char *input, int *quantidade){
    char *input_qnt_str = strdup(input);
    clientes_quantidade_classes(input_qnt_str);

    quantidade[atoi(input_qnt_str)]++;
    int quantidade_clientes = 0;

    for (int i = 0; quantidade[i] != '\0'; i++) {
        quantidade_clientes += quantidade[i];
    }

    char buffer[10];
    sprintf(buffer, "%c%03d", input[0], quantidade[atoi(input_qnt_str)] - 1);
    printf("Senha: %s; Quantia clientes na frente: %d\n", buffer, quantidade_clientes);
    thash_adiciona(hash, input, buffer);
    free(input_qnt_str);
}

void atende_cliente(thash_t *hash, int *quantidade) {

}

int main() {
    printf("** Fila clientes: **\n");

    int ativado = 1;
    char input[100];
    thash_t *hash = thash_cria();
    int quantidade[7] = {0};

    while(ativado){
        printf(">");
        scanf("%99s", input);

        if (strcmp(input, "sair") == 0) {
            ativado = 0;
        } if (strcmp(input, "?") == 0) {
            atende_cliente(hash, quantidade);
        } else {
            gerar_senha_cliente(hash, input, quantidade);
        }
    }
}