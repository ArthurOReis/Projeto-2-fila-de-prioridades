#include <stdint.h>
#include <libprg/THash.h>
#include <stdlib.h>
#include <string.h>


// retorna: um ponteiro para a tabela criada
// Obs: melhores resultados se N for primo !
unsigned int hash_simples(char* chave, int N) {
    unsigned int soma = 0;
    unsigned char* c=(unsigned char*)chave;

    for (; *c != 0; c++) {
        soma = ((soma << 8) + *c) % N;
    }
    return soma % N;
}

// cria uma tabela hash
thash_t * thash_cria() {
    thash_t * th = malloc(sizeof(thash_t));

    if (th != NULL) {
        th->tab = calloc(CAPACIDADE_THASH, sizeof(par_t*));
        th->linhas = CAPACIDADE_THASH;
        th->quantidade = 0;
        th->maxDeCarga = 2;

    } else {
        free(th);
        th = NULL;
    }
    return th;
}

// destroi uma tabela hash
void thash_destroi(thash_t * tab);

// adiciona um par (chave, valor) à tabela hash
// retorna: 1=sucesso, 0=falha
int thash_adiciona(thash_t * tab, char * chave, char* valor) {
    int posicao = hash_simples(chave, tab->linhas);
    par_t* par = tab->tab[posicao];
    if (par != NULL) {
        if (strcmp(par->chave, chave) == 0) {
            free(par);
            tab->quantidade++;
            tab->fatorDeCarga = tab->quantidade/tab->linhas;
            par->valor = strdup(valor);
            return 1;
        }
        else {
            //colisão
            return 0;
        }
    }
    else {
        par_t* p = malloc(sizeof(par_t));
        p->chave = strdup(chave);
        p->valor = strdup(valor);
        tab->quantidade++;
        tab->fatorDeCarga = tab->quantidade/tab->linhas;
    }
    if (tab->fatorDeCarga >= tab->maxDeCarga) {
        thash_expande(tab);
    }
}
void thash_expande(thash_t * tab) {
    thash_t * th = malloc(sizeof(thash_t));

    if (th != NULL) {
        th->tab = calloc(tab->linhas*2, sizeof(par_t*));
        th->linhas = tab->linhas*2;
        th->quantidade = tab->quantidade;
        th->maxDeCarga =2;

    } else {
        free(th);
        th = NULL;
    }
    for (int i = 0; i < tab->linhas; i++) {
        thash_adiciona(th, tab->tab[i]->chave, tab->tab[i]->valor);
    }
    tab = th;
}

// procura um par com determinada chave na tabela, e retorna o valor nele contido
// retorna: o valor, ou NULL em caso de falha
char* thash_obtem(thash_t * tab, char* chave);

// remove o par da tabela que contém chave
int thash_remove(thash_t * tab, char* chave);

// testa se tabela está vazia
// retorna: 1 se vazia, 0 caso contrário
int thash_vazia(thash_t * tab);

// Verifica se a chave existe na tabela.
// Retorna: 1=existe, 0=não existe
int thash_existe(thash_t * tab, char * chave);

// retorna a quantidade de pares (chave, valor) contidos na tabela
inline int thash_tamanho(thash_t * tab) {
    return tab->quantidade;
}

// para iniciar uma iteração, deve-se chamar esta função
void thash_inicia_iteracao(thash_t * tab);

// para acessar o próximo valor da iteração, chama-se esta outra função
// ela retorna: o valor da próxima iteração, ou NULL em caso de falha ou fim de iteração
par_t * thash_proximo(thash_t * tab);
