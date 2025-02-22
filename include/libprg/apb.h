//
// Created by msobral on 01/05/24.
//

#ifndef LIBPRG_APB_H
#define LIBPRG_APB_H

#include <libprg/lista_linear.h>
#include <libprg/genericos.h>

// Cada nodo da árvore de pesquisa binária (apb)
struct APB_NODO {
    void * valor;
    struct APB_NODO * esq, *dir; // ramos esquerdo e direito
    char * atual; // usado para iteração
};

typedef struct APB_NODO anodo_t;

//
typedef struct {
    anodo_t * raiz;
    gconf_t gconf;
    void * atual; // usado para iteração
    int quantidade;
} apb_t;

// Cria a raiz de uma apb contendo este "dado"
// Retorna a raiz, ou NULL em caso de falha
apb_t * apb_cria(gconf_t gconf);

// cria uma árvore a partir do conteúdo de uma lista
apb_t * apb_cria_de_lista(lista_linear_t * l);

// clona uma árvore
apb_t * apb_clona(apb_t * arv);

// compara duas árvores (comparação em ordem crescente)
int apb_compara(const apb_t * t1, const apb_t * t2);

// esvazia totalmente a árvore
void apb_limpa(apb_t * arv);

// Destroi uma apb enraizada em "arv"
void apb_destroi(apb_t * arv);

// Adiciona um "dado" à apb enraizada em "arv"
// Retorna: 1=sucesso, 0=falha
int apb_adiciona(apb_t * arv, void * dado);

// Procura "dado" na apb enraizada em "arv"
// Retorna: 1=dado existe, 0=não existe ou falha
int apb_procura(apb_t * arv, void * dado);

// retorna o dado contido na raiz
// retorna: NULL=sem raiz
void * apb_obtem_raiz(apb_t * arv);

// Remove "dado" da apb enraizada em "arv"
// Retorna: 1=sucesso, 0=falha
int apb_remove(apb_t * arv, void * dado);

// Obtém o menor valor da apb enraizada em "arv"
// Retorna o valor encontrado
void * apb_obtem_menor(apb_t * arv);

// Obtém o maios valor da apb enraizada em "arv"
// Retorna o valor encontrado
void * apb_obtem_maior(apb_t * arv);

// Obtém o maior valor que seja menor que "dado", dentro da apb enraizada em "arv"
// Retorna o valor encontrado, ou NULL caso não exista
void * apb_obtem_maior_que(apb_t * arv, void * dado);

// Obtém o menor valor que seja maior que "dado", dentro da apb enraizada em "arv"
// Retorna o valor encontrado
void * apb_obtem_menor_que(apb_t * arv, void * dado);

// Obtém uma lista de valores menores ou iguais a "dado" , dentro da apb enraizada em "arv"
lista_linear_t * apb_obtem_maiores_que(apb_t * arv, void * dado);

// Obtém uma lista de valores maiores ou iguais a "dado" , dentro da apb enraizada em "arv"
lista_linear_t * apb_obtem_menores_que(apb_t * arv, void * dado);

// Obtém uma lista de valores menores ou iguais a "dado2" E maiores ou iguais a "dado1", dentro da apb enraizada em "arv"
lista_linear_t * apb_obtem_intervalo(apb_t * arv, void * dado1, void * dado2);

// Retorna uma lista contendo os dados da apb enumerados IN-ORDER
lista_linear_t * apb_em_ordem(apb_t * arv);

// Retorna uma lista contendo os dados da apb enumerados PRE-ORDER
lista_linear_t * apb_pre_ordem(apb_t * arv);

// Retorna uma lista contendo os dados da apb enumerados POS-ORDER
lista_linear_t * apb_pos_ordem(apb_t * arv);

// Retorna uma lista contendo os dados da apb enumerados BREADTH_FIRST
lista_linear_t * apb_em_largura(apb_t * arv);

// Inicia iteração direta da apb (do menor para o maior)
void apb_inicia_iteracao(apb_t * arv);

// Inicia iteração reversa da apb (do maior para o menor)
void apb_inicia_iteracao_reversa(apb_t * arv);

// Obtém o próximo valor da iteração direta da apb
// Retorna o próximo valor, ou NULL caso a iteração tenha terminado
void * apb_proximo(apb_t * arv);

// Obtém o próximo valor da iteração reversa da apb
// Retorna o próximo valor, ou NULL caso a iteração tenha terminado
void * apb_anterior(apb_t * arv);

// Balanceia a apb undo o algoritmo AVL
// Retorna a nova raiz da árvore após o balanceamento
void apb_balanceia(apb_t * arv);

// Balanceia repetidas vezes, até não conseguir mais reduzir a altura
void apb_balanceia_maximo(apb_t * arv);

// Retorna a altura da árvore
int apb_altura(apb_t * arv);

// Retorna a quantidade de nodos da árvore
int apb_tamanho(apb_t * arv);

// Funções para usar a apb como tipo genérico em outras estruturas de dados
gconf_t gconf_apb();

// estas macros ajudam a iterar a apb, cuidando da inicialização da iteraçao, e do laço de iteração
#define while_iter_apb(c, var) for (void * var = (apb_inicia_iteracao(c), apb_proximo(c)); var != NULL; var = apb_proximo(c))

#define while_iter_reversa_apb(c, var) for (void * var = (apb_inicia_iteracao_reversa(c), apb_anterior(c)); var != NULL; var = apb_anterior(c))

// estas macros iteram a apb, chamando a função func para cada
// dado
#define itera_apb(l, func) ({ while_iter_apb(l, _dado) { \
    if (! func(_dado)) break;                                              \
}                                                         \
_dado;})

#define itera_apb_reversa(l, func) ({ while_iter_reversa_apb(l, _dado) { \
    if (! func(_dado)) break;                                              \
}                                                         \
_dado;})
#endif //LIBPRG_APB_H
