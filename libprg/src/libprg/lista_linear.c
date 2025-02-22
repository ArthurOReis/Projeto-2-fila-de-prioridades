#include <libprg/lista_linear.h>
#include <string.h>
#include <stdlib.h>

// a seguir, defina e implemente as funções da lista !

#define AREA_SIZE 8

static int lista_linear_expande(lista_linear_t * l){
    int cap2 = 2*l->cap * sizeof(char *);
    void * p = realloc(l->area,cap2);
    if(p == NULL){
        return 0;
    }
    l->area = p;
    l->cap *= 2;
    return 1;
}

lista_linear_t * lista_linear_cria() {
    lista_linear_t * lista = malloc(sizeof(lista_linear_t));

    lista->quantidade = 0;
    lista->cap = AREA_SIZE;
    lista->area = calloc(AREA_SIZE, sizeof(char*));
    // lista->area = malloc(AREA_SIZE * sizeof(char*)); => forma alternativa de calcular área

    return lista;
}

int lista_linear_adiciona(lista_linear_t * l, char* valor) {
    // se lista estiver cheia, retorna erro
    if (l->quantidade == l->cap) {
        return 0;
    }

    l->area[l->quantidade] = strdup(valor); // cria cópia da string na posição
    l->quantidade++;
    return 1;
}

// obtém valor da posição "pos"
/// se pos inválida, retorna NULL
char* lista_linear_obtem(lista_linear_t * l, uint32_t pos) {
    if(pos >= l->quantidade) {
        return NULL;
    }

    return l->area[pos];
}

char* lista_linear_ultimo(lista_linear_t * l){
    if (l->quantidade == 0){
        return NULL;
    }

    return l->area[l->quantidade-1];
}

// obtém valor no início da lista
/// se lista vazia, retorna NULL
char* lista_linear_primeiro(lista_linear_t * l){
    if (l->quantidade == 0){
        return NULL;
    }

    return l->area[0];
}

// retorna 1 se lista estiver vazia, e 0 caso contrário
int lista_linear_vazia(lista_linear_t * l){
    return (l->quantidade == 0);
}


// procura um valor na lista sequencial
// resultado: -1=falha, >=0: posição do valor
int lista_linear_procura(lista_linear_t * l, char* valor){
    if(l->quantidade == 0){
        return -1;
    }
    for (int pos = 0; pos < l->quantidade; pos++){
        if (strcmp(l->area[pos], valor)){ return pos; }
    }

}

// remove um valor da lista_linear
// resultado: 1=sucesso, 0=falha
int lista_linear_remove(lista_linear_t * l, void * valor){
    int pos = lista_linear_procura(l, valor);

    if (pos < 0) { return 0; } /*valor nao existe na lista*/

    free(l->area[pos]);

    l->quantidade--;
    l->area[pos] = l->area[l->quantidade];
    return 1;
}

//ordena a lista

void lista_linear_ordena(lista_linear_t *l){
    for (int j = l->cap; j > 0; j--){
        for (int i = 0; i < j-1; i++){
        if (atoi(l->area[i]) > atoi(l->area[i+1])){ l->area[i+1] = l->area[i]; }
    }
}
}

int lista_linear_comprimento(lista_linear_t * l){
    return l->quantidade;
}

int lista_linear_remove_ultimo(lista_linear_t * l) {
    free(l->area[l->quantidade]);

    l->quantidade--;
    return 1;
}

void lista_linear_limpa(lista_linear_t * l) {
    while (l->quantidade-- > 0){
        free(l->area[l->quantidade]);
    }
}