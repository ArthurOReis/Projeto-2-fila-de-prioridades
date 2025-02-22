//
// Created by Marcus on 15/12/2024.
//

#ifndef PILHA_H
#define PILHA_H
#define PILHA_CAPACIDADE 16

typedef struct {
    char* * area;
    int cap;
    int quantidade;
} pilha_t;

// operações da pilha

// cria uma pilha
// retorna: um ponteiro para a pilha criada

static int pilha_expande(pilha_t * q);

pilha_t* pilha_cria();

// destroi uma pilha
void pilha_destroi(pilha_t * pilha);

// adiciona um valor ao final da pilha
// resultado: 1=sucesso, 0=falha
int pilha_adiciona(pilha_t * pilha, char* valor);

// desempilha o valor que está na frente da pilha
// resultado: o valor, ou NULL em caso de falha
char* pilha_remove(pilha_t * pilha);

// retorna o valor que está no topo da pilha
// resultado: o valor, ou NULL em caso de falha
char* pilha_topo(pilha_t * pilha);

// esvazia uma pilha
void pilha_limpa(pilha_t * pilha);

// testa se pilha está vazia
int pilha_vazia(pilha_t * pilha);

// retorna o comprimento da pilha
int pilha_comprimento(pilha_t * pilha);
#endif //PILHA_H
