//
// Created by msobral on 28/03/24.
//

#ifndef LIBPRG_PILHA_H
#define LIBPRG_PILHA_H

#define PILHA_CAPACIDADE 16

#include <libprg/genericos.h>

typedef struct {
    // atributos da pilha
    void* * area;
    int cap;
    int quantidade;
    gconf_t gconf;
} pilha_t;

// operações da pilha

// cria uma pilha
// retorna: um ponteiro para a pilha criada
pilha_t* pilha_cria(gconf_t gconf);

// destroi uma pilha
void pilha_destroi(pilha_t * pilha);

// clona uma pilha
pilha_t * pilha_clona(pilha_t * pilha);

// Compara duas pilhas "lexicograficamente" (do topoa até a base)
int pilha_compara(const pilha_t * l1, const pilha_t * l2);

// adiciona um valor ao final da pilha
// resultado: 1=sucesso, 0=falha
int pilha_adiciona(pilha_t * pilha, void* valor);

// desnfileira o valor que está na frente da pilha
// resultado: o valor, ou NULL em caso de falha
void* pilha_remove(pilha_t * pilha);

// retorna o valor que está na frente da pilha
// resultado: o valor, ou NULL em caso de falha
void* pilha_topo(pilha_t * pilha);

// esvazia uma pilha
void pilha_limpa(pilha_t * pilha);

// testa se pilha está vazia
int pilha_vazia(pilha_t * pilha);

// retorna o comprimento da pilha (quantos valores estão armazenados)
int pilha_comprimento(pilha_t * pilha);

// Funções para usar a pilha como tipo genérico em outras estruturas de dados
gconf_t gconf_pilha();

#endif //LIBPRG_PILHA_H
