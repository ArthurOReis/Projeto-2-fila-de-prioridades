#include <stdio.h>
#include <string.h>
#include <libprg/libprg.h>
#include <stdlib.h>

void transformar(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] -= 17;
    }
}

void cliente_decisao(thash_t *hash, char *input, int *quantidade){
    char *input_qnt_str = strdup(input);
    transformar(input_qnt_str);

    quantidade[atoi(input_qnt_str)]++;

    char buffer[10];
    sprintf(buffer, "%c%03d", input[0], quantidade[atoi(input_qnt_str)]);
    printf("%s\n", buffer);
    thash_adiciona(hash, input, buffer);
    free(input_qnt_str);
}

int main() {
    printf("** Fila clientes: **\n");

    int ativado = 1;
    char input[100];
    thash_t *hash = thash_cria();
    int quantidade[6] = {0};

    while(ativado){
        printf(">");
        scanf("%99s", input);  // Evita buffer overflow

        if (strcmp(input, "sair") == 0) {
            ativado = 0;
        } else {
            cliente_decisao(hash, input, quantidade);
        }
    }
}