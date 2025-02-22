//
// Created by msobral on 28/03/24.
//

#ifndef LIBPRG_FILA_H
#define LIBPRG_FILA_H

#define FILA_CAPACIDADE 16

#include <libprg/genericos.h>

typedef struct {
    // atributos da fila
    void* * area;
    int cap;
    int quantidade;
    int inicio, fim;
    gconf_t gconf;
} fila_t;

// operações da fila
// cria uma fila
// retorna: ponteiro para a fila criada
fila_t* fila_cria(gconf_t gconf);

// destroi uma fila
void fila_destroi(fila_t * fila);

// clona uma fila
fila_t * fila_clona(fila_t * l);

// Compara duas filas "lexicograficamente" (do primeiro ao último ítem)
int fila_compara(const fila_t * f1, const fila_t * f2);

// adiciona um valor ao final da fila
// resultado: 1=sucesso, 0=falha
int fila_adiciona(fila_t * fila, void* valor);

// desnfileira o valor que está na frente da fila
// resultado: o valor, ou NULL em caso de falha
void* fila_remove(fila_t * fila);

// retorna o valor que está na frente da fila
// resultado: o valor, ou NULL em caso de falha
void* fila_frente(fila_t * fila);

// retorna o valor que está no fim da fila
// resultado: o valor, ou NULL em caso de falha
void* fila_fim(fila_t * fila);

// esvazia uma fila
void fila_limpa(fila_t * fila);

// testa se fila está vazia
int fila_vazia(fila_t * fila);

// retorna o comprimento da fila (quantos valores estão armazenados)
int fila_comprimento(fila_t * fila);

// Funções para usar a fila como tipo genérico em outras estruturas de dados
gconf_t gconf_fila();

#endif //LIBPRG_FILA_H
