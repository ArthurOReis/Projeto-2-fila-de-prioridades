//
// Created by aluno on 14/02/25.
//
#include <stdio.h>
#include <libprg/Apb.h>
#include <stdlib.h>
#include <string.h>

#include "libprg/Fila.h"

apb_t * apb_cria(char * dado) {
    apb_t * raiz = malloc(sizeof(apb_t));
    if (raiz != NULL) {
        raiz->valor = strdup(dado);
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    return raiz;
}

void apb_destroi(apb_t * arv) {

}

int apb_adiciona(apb_t * arv, char * dado) {
    apb_t * atual = arv;
    while (atual != NULL) {
        int cmp = strcmp(dado, atual->valor);
        if (cmp == 0) {
            return 1;
        }
        else if (cmp < 0) {
            if (atual->esq == NULL) {
                atual->esq = apb_cria(dado);
                return atual->esq != NULL;
            }
            atual = atual->esq;
        }
        else {
            if (atual->dir == NULL) {
                atual->dir = apb_cria(dado);
                return atual->dir != NULL;
            }
            atual = atual->dir;
        }
    }
    return 0;
}
int apb_procura(apb_t * arv, char * dado) {
    apb_t * atual = arv;
    while (atual != NULL) {
        int cmp = strcmp(dado, atual->valor);
        if (cmp == 0) {
            return 1;
        }
        else if (cmp < 0) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }
    return 0;
}
void _em_ordem(apb_t * raiz,lista_linear_t * l) {
    if (raiz != NULL) {
        _em_ordem(raiz->esq, l);
        lista_linear_adiciona(l,raiz->valor);
        _em_ordem(raiz->dir, l);
    }
}
lista_linear_t * apb_em_ordem(apb_t * arv) {
    lista_linear_t * l = lista_linear_cria();
    _em_ordem(arv,l);
    return l;
}

void _pre_ordem(apb_t * raiz,lista_linear_t * l) {
    if (raiz != NULL) {
        lista_linear_adiciona(l,raiz->valor);
        _pre_ordem(raiz->esq, l);
        _pre_ordem(raiz->dir, l);
    }
}
lista_linear_t * apb_pre_ordem(apb_t * arv) {
    lista_linear_t * l = lista_linear_cria();
    _pre_ordem(arv,l);
    return l;
}

void _pos_ordem(apb_t * raiz,lista_linear_t * l) {
    if (raiz != NULL) {
        _pos_ordem(raiz->esq, l);
        _pos_ordem(raiz->dir, l);
        lista_linear_adiciona(l,raiz->valor);
    }
}
lista_linear_t * apb_pos_ordem(apb_t * arv) {
    lista_linear_t * l = lista_linear_cria();
    _pos_ordem(arv,l);
    return l;
}
/*lista_linear_t * apb_em_largura(apb_t * arv) {
    lista_linear_t * l = lista_linear_cria();
    if (arv != NULL) {
        fila_t * q = fila_cria();

        fila_adiciona(q,arv);
        while (!fila_vazia(q)) {
            apb_t * nodo = fila_remove(q);
            if (nodo->esq) fila_adiciona(q,nodo->esq);
            if (nodo->dir) fila_adiciona(q,nodo->dir);
            lista_linear_adiciona(l,nodo->valor);
        }
    }
}*/

    int apb_adiciona_r(apb_t * arv, char * dado){
        apb_t * atual = arv;

        int cmp = strcmp(dado, atual->valor);
        if (cmp == 0){
            return 1; // valor ja existe, esta arvore nao possui valores repetidos
        }
        if (cmp < 0){
            if(atual->esq != NULL){
                return apb_adiciona_r(arv->esq, dado);
            } else {
                atual->esq = apb_cria(dado);
                return 1;
            }
        } else {
            if (atual->dir != NULL) {
                return apb_adiciona_r(arv->dir, dado);
            } else {
                atual->dir = apb_cria(dado);
                return 1;
            }
        }
        return 0;

    }

    int apb_remove(apb_t * arv, char * dado){
        apb_t * atual = arv;

        while (atual != NULL) {
            int cmp = strcmp(dado, atual->valor);

            if (cmp == 0) {
                if (atual->esq == NULL && atual->dir == NULL) {
                    free(atual->valor);
                    free(atual);
                    return 1;
                }
                if (atual->esq == NULL) {
                    apb_t *temp = atual->dir;
                    free(atual->valor);
                    free(atual);
                    apb_adiciona(arv , temp->valor);
                    return 1;
                }
                if (atual->dir == NULL) {
                    apb_t *temp = atual->dir;
                    free(atual->valor);
                    free(atual);
                    apb_adiciona(arv , temp->valor);
                    return 1;
                }
                apb_t *temp = atual->dir;
                while (temp->esq != NULL) {
                    temp = temp->esq;
                }
                free(atual->valor);
                atual->valor = strdup(temp->valor);
                apb_remove(atual->dir, temp->valor);
                return 1;
            }

            if (cmp < 0) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }

        return 0;
    }

    char * apb_obtem_menor(apb_t * arv) {
        apb_t * atual = arv;

        if (atual == NULL){ return NULL; }
        while (atual != NULL)
        {
            if (atual->esq == NULL) {
                char *temp = atual->valor;
                printf(temp);
                apb_remove(arv, atual->valor);

                return temp;
            }else
            atual = atual->esq;
        }
    }