//
// Created by msobral on 28/03/24.
//

#ifndef LIBPRG_THASH_H
#define LIBPRG_THASH_H

#include <libprg/conjunto.h>
#include <libprg/thash_tipos.h>

// cria uma tabela hash
// retorna: um ponteiro para a tabela criada
thash_t * thash_cria(gconf_t gconf);

// destroi uma tabela hash
void thash_destroi(thash_t * tab);

// clona uma tabela
thash_t * thash_clona(thash_t * tab);

// compara duas thash com respeito às chaves
// faz a comparação "lexicográfica" similar à de lista e lista_linear
int thash_compara(const thash_t * t1, const thash_t * t2);

// Esvazia totalmente a tabela
void thash_limpa(thash_t * tab);

// Altera a capacidade
void thash_define_capacidade(thash_t * tab, uint32_t cap);

// adiciona um par (chave, valor) à tabela hash
// retorna: 1=sucesso, 0=falha
int thash_adiciona(thash_t * tab, char * chave, void* valor);

// procura um par com determinada chave na tabela, e retorna o valor nele contido
// retorna: o valor, ou NULL em caso de falha
void* thash_obtem(thash_t * tab, char* chave);

// remove o par da tabela que contém chave
int thash_remove(thash_t * tab, char* chave);

// testa se tabela está vazia
// retorna: 1 se vazia, 0 caso contrário
int thash_vazia(thash_t * tab);

// Verifica se a chave existe na tabela.
// Retorna: 1=existe, 0=não existe
int thash_existe(thash_t * tab, char * chave);

// retorna a quantidade de pares (chave, valor) contidos na tabela
int thash_tamanho(thash_t * tab);

// para iniciar uma iteração, deve-se chamar esta função
void thash_inicia_iteracao(thash_t * tab);

// para acessar o próximo valor da iteração, chama-se esta outra função
// ela retorna: o valor da próxima iteração, ou NULL em caso de falha ou fim de iteração
par_t * thash_proximo(thash_t * tab);

// gera a lista de chaves contidas na tabela
lista_linear_t * thash_chaves(thash_t * tab);

// gera a lista de valores contidos na tabela
lista_linear_t * thash_valores(thash_t * tab);

// gera a lista de pares (chave, valor) contidos na tabela
lista_linear_t * thash_items(thash_t * tab);

// esta macro ajuda a iterar a tabela, cuidando da inicialização da iteraçao, e do laço de iteração
#define while_iter_thash(l, var) for (par_t * var = (thash_inicia_iteracao(l), thash_proximo(l)); var != NULL; var = thash_proximo(l))

// esta macro itera a tabela, chamando a função func para cada
// func deve ter esta assinatura:
// int func(par_t * dado)
//#define itera_thash(l, func) ({ while_iter_thash(l, _dado) { \
//    if (! func(_dado)) break;                                              \
//}                                                         \
//_dado;})

// Funções para usar a thash como tipo genérico em outras estruturas de dados
gconf_t gconf_thash();

#endif //LIBPRG_THASH_H
