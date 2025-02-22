#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libprg/libprg.h>

int main() {int quantidade[6];
    char resposta;
    apb_t * filaDeAtendimento = apb_cria("A001");
    char senha[10];
    while (true) {
        printf(">");

        scanf("%c",&resposta);
        switch (resposta) {
            case 'A':
                quantidade[0]++;
            if (quantidade[0]<10)
                sprintf(senha,"A00%d",quantidade[0]);
            else if (quantidade[0]<100)
                sprintf(senha,"A0%d",quantidade[0]);
            else
                sprintf(senha,"A%d",quantidade[0]);
            apb_adiciona(filaDeAtendimento,senha);
            break;
            case 'B':
                break;
            case 'C':
                break;
            case 'D':
                break;
            case 'E':
                break;
            case 'F':
                break;
            case '?':
                break;
            default:
                return 0;
        }
    }
    printf(apb_obtem_menor(filaDeAtendimento));
}
