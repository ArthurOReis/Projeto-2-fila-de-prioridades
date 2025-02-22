//
// Created by msobral on 15/03/24.
//

#ifndef LIBPRG_MMSOBRAL_lista_linear_LINEAR_H
#define LIBPRG_MMSOBRAL_lista_linear_LINEAR_H

#define CAPACIDADE_LISTA 16

#include <libprg/genericos.h>

typedef struct {
    // atributos da lista_linear linear
    void* * area;
    gconf_t gconf;
    int cap;
    int quantidade;
    int pos; // para iteração
} lista_linear_t;

// operações da lista_linear

// cria uma lista_linear vazia
// lista_linear_t l1;
// lista_linear_cria(&l1);
lista_linear_t * lista_linear_cria(gconf_t gconf);

// destroi uma lista_linear
void lista_linear_destroi(lista_linear_t * lista_linear);

// gera uma cópia da lista
lista_linear_t * lista_linear_clona(lista_linear_t * l);

// copia uma lista
// retorna: a lista destino (parâmetro dest)
lista_linear_t * lista_linear_copia(lista_linear_t * dest, lista_linear_t * src);

// esvazia uma lista
void lista_linear_limpa(lista_linear_t * lista);

// adiciona um valor ao final da lista_linear
// resultado: 1=sucesso, 0=falha
int lista_linear_adiciona(lista_linear_t * lista_linear, void* valor);

// remove um valor da lista_linear
// resultado: 1=sucesso, 0=falha
int lista_linear_remove(lista_linear_t * lista_linear, void* valor);

// remove o último valor da lista_linear
// resultado: 1=sucesso, 0=falha
int lista_linear_remove_ultimo(lista_linear_t * lista_linear);

// procura um valor na lista_linear
// resultado: -1=falha, >=0: posição do valor
int lista_linear_procura(lista_linear_t * lista_linear, void* valor);

// Ordena a lista
void lista_linear_ordena(lista_linear_t * lista);

// Compara duas listas lineares "lexicograficamente" (do primeiro ao último ítem)
int lista_linear_compara(const lista_linear_t * l1, const lista_linear_t * l2);

// resultado: 1=sucesso, 0=falha
int lista_linear_adiciona_ordenada(lista_linear_t * lista_linear, void* valor);

// remove um valor da lista_linear
// resultado: 1=sucesso, 0=falha
int lista_linear_remove_ordenada(lista_linear_t * lista_linear, void* valor);

// procura um valor na lista_linear
// resultado: -1=falha, >=0: posição do valor
int lista_linear_procura_ordenada(lista_linear_t * lista_linear, void* valor);

// obtém valor da posição "pos"
/// se pos inválida, retorna NULL
void* lista_linear_obtem(lista_linear_t * l, uint32_t pos);

// obtém valor no fim da lista
/// se lista vazia, retorna NULL
void* lista_linear_ultimo(lista_linear_t * l);

// obtém valor no início da lista
/// se lista vazia, retorna NULL
void* lista_linear_primeiro(lista_linear_t * l);

// retorna 1 se lista estiver vazia, e 0 caso contrário
int lista_linear_vazia(lista_linear_t * l);

// retorna o comprimento da lista
int lista_linear_comprimento(lista_linear_t * l);

// inicia iteração da lista
void lista_linear_inicia_iteracao(lista_linear_t * l);

// obtém próximo valor da iteração, ou NULL se iteração tiver terminado
void * lista_linear_proximo(lista_linear_t * l);

#define while_iter_ll(l, var) for (void * var = (lista_linear_inicia_iteracao(l), lista_linear_proximo(l)); var != NULL; var = lista_linear_proximo(l))
#endif //LIBPRG_MMSOBRAL_lista_linear_LINEAR_H

// Funções para usar a lista linear como tipo genérico em outras estruturas de dados
gconf_t gconf_lista_linear();
