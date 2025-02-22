//
// Created by msobral on 28/03/24.
//

#ifndef LIBPRG_THASH_TIPOS_H
#define LIBPRG_THASH_TIPOS_H

//#include <libprg/lista_linear.h>
#include <libprg/genericos.h>
#include <libprg/conjunto.h>
#include <string.h>

typedef struct {
    conjunto_t * c;
    gconf_t * pconf;
} thash_t;

typedef struct {
    char * chave;
    void * valor;
    gconf_t * pconf; // funções genericas de "valor"
} par_t;

#define safe_free(p, f_free) if (p != NULL) { \
f_free(p); \
p = NULL;                             \
}

static inline int par_comp(const void * o1, const void * o2) {
    const par_t * p1=o1, *p2=o2;
    return strcmp(p1->chave, p2->chave);
}

static inline void* par_clone(void * obj) {
    par_t *p=obj;

    g_alloc(novo, par_t);
    novo->chave = strdup(p->chave);
    novo->valor = p->valor!=NULL?p->pconf->f_clone(p->valor):NULL;
    novo->pconf = p->pconf;
    return novo;
}

static inline void par_destroi(void * obj) {
    par_t *p=obj;

    safe_free(p->chave, free);
    safe_free(p->valor, p->pconf->f_destroi);
    free(p);
}

static inline void par_move(par_t * src, par_t * dest) {
    *dest = *src;

    src->chave = NULL;
    src->valor = NULL;
}

static inline uint32_t par_hash(void* val, uint32_t len) {
    par_t* par = (par_t*)val;

    return fletcher32(par->chave, strlen(par->chave));
}
#endif //LIBPRG_THASH_TIPOS_H
