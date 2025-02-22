#include <libprg/libprg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// função hash
uint32_t hash_simples(char* chave, int N) {
    uint32_t soma = 0;
    uint8_t* c = (uint8_t*)chave;
    for (; *c != 0; c++) {
        soma = ((soma << 8) + *c) % N;
    }
    return soma % N;
}

// cria uma tabela hash
// retorna: um ponteiro para a tabela criada
thash_t * thash_cria() {
    thash_t *tab = malloc(sizeof(thash_t));
    if (tab) {
        tab->linhas = CAPACIDADE_THASH;
        tab->quantidade = 0;
        tab->tab = calloc(CAPACIDADE_THASH, sizeof(lista_linear_t*));
    }
    return tab;
}

// destroi uma tabela hash
void thash_destroi(thash_t * tab) {
    for (int i = 0; i < tab->linhas; i++) {
        if (tab->tab[i]) {
            lista_linear_destroi(tab->tab[i]);
        }
    }
    free(tab->tab);
    free(tab);
}


// adiciona um par (chave, valor) à tabela hash
// retorna: 1=sucesso, 0=falha
int thash_adiciona(thash_t * tab, char * chave, char* valor) {
    uint32_t linha = hash_simples(chave, tab->linhas);
    if (!tab->tab[linha]) {
        tab->tab[linha] = lista_linear_cria();
    }
    char *novo_par = malloc(strlen(chave) + strlen(valor) + 2);
    sprintf(novo_par, "%s\xFF%s", chave, valor); // Usa \xFF para separar
    lista_linear_adiciona(tab->tab[linha], novo_par);
    return 1;
}

// procura um par com determinada chave na tabela, e retorna o valor nele contido
// retorna: o valor, ou NULL em caso de falha
char* thash_obtem(thash_t * tab, char* chave) {
    uint32_t linha = hash_simples(chave, tab->linhas);
    if (!tab->tab[linha]) return NULL;
    for (int i = 0; i < lista_linear_comprimento(tab->tab[linha]); i++) {
        char *item = lista_linear_obtem(tab->tab[linha], i);
        if (strncmp(item, chave, strlen(chave)) == 0 && item[strlen(chave)] == '\xFF') {
            return item + strlen(chave) + 1;
        }
    }
    return NULL;
}

// remove o par da tabela que contém chave
int thash_remove(thash_t * tab, char* chave) {
    uint32_t linha = hash_simples(chave, tab->linhas);
    if (!tab->tab[linha]) return 0;

    lista_linear_t *lista = tab->tab[linha];

    for (int i = 0; i < lista_linear_comprimento(lista); i++) {
        char *item = lista_linear_obtem(lista, i);
        // Verifica se o item possui a chave seguida pelo separador \xFF
        if (strncmp(item, chave, strlen(chave)) == 0 && item[strlen(chave)] == '\xFF') {
            // lista_linear_remove já realiza a compactação e libera o espaço do item
            lista_linear_remove(lista, item);

            // Se a lista ficou vazia, liberamos a memória da própria lista
            if (lista_linear_comprimento(lista) == 0) {
                lista_linear_destroi(lista);
                tab->tab[linha] = NULL;
            }
            return 1;
        }
    }
    return 0;
}

// testa se tabela está vazia
// retorna: 1 se vazia, 0 caso contrário
int thash_vazia(thash_t * tab) {
    return tab->quantidade == 0;
}

// Verifica se a chave existe na tabela.
// Retorna: 1=existe, 0=não existe
int thash_existe(thash_t * tab, char * chave) {

}

// retorna a quantidade de pares (chave, valor) contidos na tabela
inline int thash_tamanho(thash_t * tab) {
    return tab->quantidade;
}

// para iniciar uma iteração, deve-se chamar esta função
void thash_inicia_iteracao(thash_t * tab) {

}

// para acessar o próximo valor da iteração, chama-se esta outra função
// ela retorna: o valor da próxima iteração, ou NULL em caso de falha ou fim de iteração
//lista_linear_t * thash_proximo(thash_t * tab) {
//
//}