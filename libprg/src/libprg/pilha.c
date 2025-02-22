#include <libprg/Pilha.h>
#include <stdlib.h>
#include <string.h>

static int pilha_expande(pilha_t * q){
    int capTemp = 2 * q->cap;

    void *p = realloc(q->area, capTemp * sizeof(char *));
    if (p == NULL){
        return 0;
    }
    q->area = p;
    q->cap = capTemp;

    int i = 0;

    for (int j = 0; j < q->quantidade; j++) {
        q->area[i++] = q->area[j];
    }

    return 1;
}

pilha_t* pilha_cria() {
    pilha_t * q = malloc(sizeof(pilha_t));

    if (q != NULL) {
        q->area = calloc(PILHA_CAPACIDADE, sizeof(char*));

        q->quantidade = 0;
        q->cap = PILHA_CAPACIDADE;
    } else {
        free(q);
        q = NULL;
    }
    return q;
}

// destroi uma pilha
void pilha_destroi(pilha_t * q) {
    for (int i = q->quantidade; q->quantidade > 0; q->quantidade--) {
        free(q->area[i]);
        i = (i + 1) % q->cap;
    }

    free(q->area);
    q->area = NULL;
    q->cap = 0;
}

// adiciona um valor ao final da pilha
// resultado: 1=sucesso, 0=falha
int pilha_adiciona(pilha_t * q, char* valor) {
    if(q->quantidade == q->cap) {
        pilha_expande(q);
    }
    q->area[q->quantidade] = strdup(valor);
    q->quantidade++;
    return 1;
}

// desempilha o valor que está na frente da pilha
// resultado: o valor, ou NULL em caso de falha
char* pilha_remove(pilha_t * q) {
    if (q->quantidade == 0){
        return NULL;
    }
    char * valor = q->area[q->quantidade];
    q->quantidade--;
    return valor;
}

// retorna o valor que está no topo da pilha
// resultado: o valor, ou NULL em caso de falha
char* pilha_topo(pilha_t * q) {
    if (q->quantidade == 0){
        return NULL;
    }
    return q->area[q->quantidade];
}

// esvazia uma pilha
void pilha_limpa(pilha_t * q) {
    while (q->quantidade-- > 0){
        free(q->area[q->quantidade]);
    }
}

// testa se pilha está vazia
int pilha_vazia(pilha_t * q) {
    return (q->quantidade == 0);
}

// retorna o comprimento da pilha
int pilha_comprimento(pilha_t * q) {
    return q->quantidade;
}