//
// Created by aluno on 14/02/25.
//

#ifndef LIBPRG_APB_H
#define LIBPRG_APB_H

#include <libprg/lista_linear.h>

// Cada nodo da árvore de pesquisa binária (apb)
struct APB_NODO {
    char * valor;
    struct APB_NODO * esq, *dir; // ramos esquerdo e direito
};

//
typedef struct APB_NODO apb_t;

// Cria a raiz de uma apb contendo este "dado"
// Retorna a raiz, ou NULL em caso de falha
apb_t * apb_cria(char * dado);

// Destroi uma apb enraizada em "arv"
void apb_destroi(apb_t * arv);

// Adiciona um "dado" à apb enraizada em "arv"
// Retorna: 1=sucesso, 0=falha
int apb_adiciona(apb_t * arv, char * dado);

// Procura "dado" na apb enraizada em "arv"
// Retorna: 1=dado existe, 0=não existe ou falha
int apb_procura(apb_t * arv, char * dado);

// Remove "dado" da apb enraizada em "arv"
// Retorna: 1=sucesso, 0=falha
int apb_remove(apb_t * arv, char * dado);

// Obtém o menor valor da apb enraizada em "arv"
// Retorna o valor encontrado
char * apb_obtem_menor(apb_t * arv);

// Obtém o maios valor da apb enraizada em "arv"
// Retorna o valor encontrado
char * apb_obtem_maior(apb_t * arv);

// Obtém o maior valor que seja menor que "dado", dentro da apb enraizada em "arv"
// Retorna o valor encontrado, ou NULL caso não exista
char * apb_obtem_maior_que(apb_t * arv, char * dado);

// Obtém o menor valor que seja maior que "dado", dentro da apb enraizada em "arv"
// Retorna o valor encontrado
char * apb_obtem_menor_que(apb_t * arv, char * dado);

// Obtém uma lista de valores menores ou iguais a "dado" , dentro da apb enraizada em "arv"
lista_linear_t * apb_obtem_maiores_que(apb_t * arv, char * dado);

// Obtém uma lista de valores maiores ou iguais a "dado" , dentro da apb enraizada em "arv"
lista_linear_t * apb_obtem_menores_que(apb_t * arv, char * dado);

// Obtém uma lista de valores menores ou iguais a "dado2" E maiores ou iguais a "dado1", dentro da apb enraizada em "arv"
lista_linear_t * apb_obtem_intervalo(apb_t * arv, char * dado1, char * dado2);

// Retorna uma lista contendo os dados da apb enumerados IN-ORDER
lista_linear_t * apb_em_ordem(apb_t * arv);

// Retorna uma lista contendo os dados da apb enumerados PRE-ORDER
lista_linear_t * apb_pre_ordem(apb_t * arv);

// Retorna uma lista contendo os dados da apb enumerados POS-ORDER
lista_linear_t * apb_pos_ordem(apb_t * arv);

// Retorna uma lista contendo os dados da apb enumerados BREADTH_FIRST
//lista_linear_t * apb_em_largura(apb_t * arv);

// Balanceia a apb usando o algoritmo AVL
// Retorna a nova raiz da árvore após o balanceamento
apb_t * apb_balanceia(apb_t * arv);

// Retorna a altura da árvore
int apb_altura(apb_t * arv);

// Retorna a quantidade de nodos da árvore
int apb_tamanho(apb_t * arv);
#endif //APB_H
