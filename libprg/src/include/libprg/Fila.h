#ifndef FILA_H
#define FILA_H

#define FILA_CAPACIDADE 16

typedef struct {
    char* * area;
    int cap;
    int quantidade;
    int inicio, fim;
} fila_t;

fila_t* fila_cria();

static int fila_expande(fila_t * q);

void fila_destroi(fila_t * fila);

int fila_adiciona(fila_t * fila, char* valor);

char* fila_remove(fila_t * fila);

char* fila_frente(fila_t * fila);

char* fila_fim(fila_t * fila);

void fila_limpa(fila_t * fila);

int fila_vazia(fila_t * fila);

int fila_comprimento(fila_t * fila);

#endif //FILA_H