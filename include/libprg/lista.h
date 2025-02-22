//
// Created by msobral on 28/03/24.
//

#ifndef LIBPRG_lista_enc_t_H
#define LIBPRG_lista_enc_t_H

#include <libprg/genericos.h>

struct NODO {
    void* valor;
    struct NODO * prox, * prev;
};

typedef struct NODO nodo_t;

// uma lista circular duplamente encadeada
typedef struct {
    nodo_t head;
    nodo_t * atual; // para iteração
    gconf_t gconf;
    int quantidade;
} lista_t;

// operações da lista

// esta macro ajuda a iterar a lista, cuidando da inicialização da iteraçao, e do laço de iteração
#define while_iter_dir(l, var, dir) for (void * var = (lista_inicia_iteracao(l), lista_ ## dir(l)); var != NULL; var = lista_ ## dir(l))

#define while_iter(l, var) while_iter_dir(l, var, proximo)
#define while_iter_reverso(l, var) while_iter_dir(l, var, anterior)

// estas macros iteram a lista, chamando a função func para cada
// dado
//#define itera(l, func) ({ while_iter(l, _dado) { \
//    if (! func(_dado)) break;                                              \
//}                                                         \
//_dado;})
//
//#define itera_reverso(l, func) ({ while_iter_reverso(l, _dado) { \
//    if (! func(_dado)) break;                                              \
//}                                                         \
//_dado;})

// cria uma lista vazia
lista_t* lista_cria(gconf_t gconf);

// destroi uma lista
void lista_destroi(lista_t * lista);

// clona uma lista
lista_t * lista_clona(lista_t * l);

// Compara duas listas "lexicograficamente" (do primeiro até o último)
int lista_compara(const lista_t * l1, const lista_t * l2);

// adiciona um valor ao final da lista
// resultado: 1=sucesso, 0=falha
int lista_adiciona(lista_t * lista, void* valor);

// insere um valor em uma posição da lista
// resultado: 1=sucesso, 0=falha
int lista_insere(lista_t * lista, unsigned int pos, void* valor);

// remove um valor de uma posição da lista
// resultado: 1=sucesso, 0=falha
int lista_remove(lista_t * lista, unsigned int pos);

// remove um valor do final da lista
// resultado: 1=sucesso, 0=falha
int lista_remove_final(lista_t * lista);

// procura um valor dentro da lista
// retorna: a posição do valor encontrado (em caso de falha, retorna -1)
int lista_procura(lista_t * lista, void * valor);

// retorna o valor que está na posição da lista
// Retorna: o valor, ou NULL em caso de falha
void* lista_obtem(lista_t * lista, unsigned int pos);

// retorna o valor que está no início da lista
// Retorna: o valor, ou NULL em caso de falha
void* lista_obtem_primeiro(lista_t * lista);

// retorna o valor que está no final  da lista
// Retorna: o valor, ou NULL em caso de falha
void* lista_obtem_ultimo(lista_t * lista);

// substitui o valor que está nesta posição da lista
// Retorna: 1=sucesso, 0=falha
int lista_substitui(lista_t * lista, unsigned int pos, void * valor);

// esvazia uma lista
void lista_limpa(lista_t * lista);

// testa se lista está vazia
int lista_vazia(lista_t * lista);

// retorna o comprimento da lista (quantos valores estão armazenados)
int lista_comprimento(lista_t * lista);

// inverte a lista
void lista_inverte(lista_t * lista);

// Ordena a lista usando o algoritmo "merge sort"
void lista_ordena(lista_t * lista);

// Embaralha a lista usando um algoritmo parecido com merge sort
void lista_embaralha(lista_t * lista);

// iteração da lista: isto serve para percorrer a lista de forma eficiente, com custo linear
// a iteração possibilita acessar do primemiro ao último valor da lista sucessivamente
// IMPORTANTE: não modifique a lista durante uma iteração ! Caso o faça, reinicie a iteração !

// para iniciar uma iteração, deve-se chamar esta função
void lista_inicia_iteracao(lista_t * lista);

// para acessar o próximo valor da iteração, chama-se esta outra função
// ela retorna: o valor da próxima iteração, ou NULL em caso de falha ou fim de iteração
void * lista_proximo(lista_t * lista);

// para acessar o valor anterior da iteração, chama-se esta outra função
// ela retorna: o valor da próxima iteração, ou NULL em caso de falha ou fim de iteração
void * lista_anterior(lista_t * lista);

// para testar se a iteração chegou ao fim, usa-se esta função
// retorna: 1, se terminou a iteração, 0 caso contrário
//int lista_fim_iteracao(lista_t * lista);

// Funções para usar a lista como tipo genérico em outras estruturas de dados
gconf_t gconf_lista();

#endif //LIBPRG_lista_enc_t_H
