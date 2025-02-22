//
// Created by msobral on 19/06/24.
//

#ifndef LIBPRG_CONJUNTO_H
#define LIBPRG_CONJUNTO_H

#include <libprg/lista_linear.h>
#include <stdint.h>

#define CAPACIDADE_CJTO 31
#define FATOR_CARGA 7

typedef struct {
    lista_linear_t** tab;
    gconf_t gconf;
    int linhas;
    int quantidade;
    // campos usados para iteração
    int _linha;
    int _pos;
    float fator; // fator de carga máximo
} conjunto_t;

#define set_fhash(c, fun) c->gconf.f_hash = (Fhash)fun
#define get_fhash(c) c->gconf.f_hash
#define do_fhash(c, val) (c->gconf.f_hash(val, g_sizeof(c, val)) % c->linhas)

// cria um conjunto
// retorna: um ponteiro para o conjunto criado
conjunto_t * conjunto_cria(gconf_t conf);

// cria um conjunto a partir de uma lista linear
conjunto_t * conjunto_cria_de_lista(lista_linear_t * l);

// destroi um conjunto
void conjunto_destroi(conjunto_t * c);

// clona um conjunto
conjunto_t * conjunto_clona(conjunto_t * c);

// compara dois conjuntos "lexicograficamente" (ordena os valores e compata do primeiro pro último)
// um tanto pesado ... custo nlogn
int conjunto_compara(const conjunto_t * t1, const conjunto_t * t2);

// ESvazia totalmente o conjunto
void conjunto_limpa(conjunto_t * c);

// altera a capacidade
void conjunto_define_capacidade(conjunto_t * tab, uint32_t cap);

// obtém um valor do conjunto
// se valor não existir, retorna NULL
// se vcalor existir, retorna referência.
// OBS: valor retornado não pode ser modificado, se isso afetar seu hash !!
void* conjunto_obtem(conjunto_t * tab, void* valor);

// adiciona um valor ao conjunto
// se valor jpa existe no conjunto, a operação nada faz
int conjunto_adiciona(conjunto_t * c, void * valor);

// remove um valor do conjunto, caso exista
int conjunto_remove(conjunto_t * c, void * valor);

// testa se valor existe no conjunto
// retorna: 1=valor existe, 0=não existe
int conjunto_existe(conjunto_t * c, void * valor);

// retorna: 1=vazio, 0=não-vazio
int conjunto_vazio(conjunto_t * c);

// inicia a iteração do conjunto
void conjunto_inicia_iteracao(conjunto_t * c);

// obtém próximo valor da iteração
// se chegou ao fim da iteração, retorna NULL
void * conjunto_proximo(conjunto_t * c);

// lista os valores do conjunto
lista_linear_t * conjunto_lista(conjunto_t * c);

// Funções para usar o conjunto como tipo genérico em outras estruturas de dados
gconf_t gconf_conjunto();

// esta macro ajuda a iterar o conjunto, cuidando da inicialização da iteraçao, e do laço de iteração
#define while_iter_conjunto(c, var) for (void * var = (conjunto_inicia_iteracao(c), conjunto_proximo(c)); var != NULL; var = conjunto_proximo(c))

#endif //LIBPRG_CONJUNTO_H
