#include <libprg/Fila.h>
#include <stdlib.h>
#include <string.h>

static int fila_expande(fila_t * q){
    int capTemp = 2 * q->cap;

    void *p = realloc(q->area, capTemp * sizeof(char *));
    if (p == NULL){
        return 0;
    }
    q->area = p;
    q->cap = capTemp;

    int i = 0;

    if (q->inicio < q->fim){
        return 1;
    }
    for (int j = q->inicio; j < q->cap / 2; j++) {
        q->area[i++] = q->area[j];
    }
    for (int j = 0; j < q->fim; j++) {
        q->area[i++] = q->area[j];
    }

    q->inicio = 0;
    q->fim = i;

    return 1;
}

fila_t * fila_cria(){
    fila_t * q = malloc(sizeof(fila_t));

    if (q != NULL) {
        q->area = calloc(FILA_CAPACIDADE, sizeof(char*));

        q->quantidade = 0;
        q->cap = FILA_CAPACIDADE;
        q->inicio = 0;
        q->fim = 0;
    } else {
        free(q);
        q = NULL;
    }
    return q;
}

int fila_adiciona(fila_t * q, char* valor) {
    if(q->quantidade == q->cap) {
        fila_expande(q);
    }
    q->area[q->fim] = strdup(valor);
    q->quantidade++;
    q->fim++;
    if(q->fim ==q->cap) q->fim =0;
    return 1;
}


char * fila_remove(fila_t * q){
    if (q->quantidade == 0){
        return NULL;
    }
    char * valor = q->area[q->inicio];
    q->inicio = (q->inicio+1) % q->cap;
    q->quantidade--;
    return valor;

}

int fila_comprimento(fila_t * q){
    return q->quantidade;
}

char * fila_frente(fila_t * q){
    if (q->quantidade == 0){
        return NULL;
    }
    return q->area[q->inicio];
}

char * fila_fim(fila_t * q){
    if (q->quantidade == 0){
        return NULL;
    }

    if (q->fim == 0) return q->area[q->cap-1];

    return q->area[q->fim-1];
}

void fila_limpa(fila_t * fila){
    while (fila->quantidade-- > 0){
        free(fila->area[fila->quantidade]);
    }
}


void fila_destroi(fila_t * fila){
    for (int i = fila->inicio; fila->quantidade > 0; fila->quantidade--) {
        free(fila->area[i]);
        i = (i + 1) % fila->cap;
    }

    free(fila->area);
    fila->area = NULL;
    fila->cap = 0;
    fila->inicio = 0;
    fila->fim = 0;
}

int fila_vazia(fila_t * q) {
    return (q->quantidade == 0);
}
