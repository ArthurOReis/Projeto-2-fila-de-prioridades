#include <libprg/lista_linear.h>
#include <string.h>
#include <stdlib.h>

//! cria uma lista_linear vazia
//! retorna: um ponteiro para a lista que foi criada, ou NULL se ocorrer um erro
lista_linear_t * lista_linear_cria() {
    lista_linear_t * lista = malloc(sizeof(lista_linear_t));
    if(!lista) {
        return NULL;
    }

    lista->quantidade = 0;
    lista->cap = CAPACIDADE_LISTA;
    lista->area = calloc(CAPACIDADE_LISTA, sizeof(char*));

    if(!lista->area) {
        free(lista);
        return NULL;
    }

    return lista;
}

//! expande a lista, dobrando sua capacidade de armazenamento
//! retorna: 1=sucesso, 0=falha
static int lista_linear_expande(lista_linear_t* l) {
    void* p = realloc(l->area, 2*l->cap*sizeof(char*));

    if(p != NULL) {
        l->area = p;
        l->cap *= 2;
        return 1;
    }

    return 0;
}

static int lista_linear_valido(lista_linear_t * l) {
    return l != NULL && l->cap >= 0 && l->area != NULL; // Função usada em todas/maioria das funções para verificar se a lista recebida é válida
}

//! destroi uma lista_linear
void lista_linear_destroi(lista_linear_t * l){
    if (!lista_linear_valido(l)) return;
    lista_linear_limpa(l);
    free(l->area);
    free(l);
}

//! esvazia uma lista
void lista_linear_limpa(lista_linear_t * l){
    if(lista_linear_valido(l)) {
        for(int i = 0; i < l->quantidade; i++) {
            if(l->area[i]) {
                free(l->area[i]); // Verificação para não limpar ponteiros nulos
            }
        }
        l->quantidade = 0;
    }
}

//! adiciona um valor ao final da lista_linear
//! expande a capacidade da lista se necessário, e aloca memória para uma cópia do valor fornecido
//! resultado: 1=sucesso, 0=falha
int lista_linear_adiciona(lista_linear_t * l, char* valor) {
    if(!lista_linear_valido(l) || !valor) {
        return 0;
    }

    // Se a quantidade for maior do que a capacidade disponível, a lista será expandida, no entanto, se falhar, para a operação
    if (l->quantidade == l->cap) {
        lista_linear_expande(l);
        if (l->area == NULL) {
            return 0; // Falha ao realocar
        }
    }
    l->area[l->quantidade] = strdup(valor); // Aloca memória para o novo valor
    l->quantidade++;
    return 1; // Sucesso
}

//! remove um valor da lista_linear
//! resultado: 1=sucesso, 0=falha
int lista_linear_remove(lista_linear_t * l, void* valor) {
    for (int i = 0; i < l->quantidade; i++) {
        if (strcmp(valor, l->area[i]) == 0) {
            free(l->area[i]);
            for (int j = i; j < l->quantidade - 1; j++) {
                l->area[j] = l->area[j + 1];  // Após remover o valor, a lista deve estar compactada, sem lacunas
            }
            l->quantidade--;
            return 1;
        }
    }
    return 0;
}

//! remove o último valor da lista_linear
//! resultado: 1=sucesso, 0=falha
int lista_linear_remove_ultimo(lista_linear_t * l) {
    if(!lista_linear_valido(l) || l->quantidade == 0) {
        return 0;
    }

    free(l->area[l->quantidade-1]);
    l->area[l->quantidade - 1] = NULL;
    l->quantidade--;
    return 1;
}

//! procura um valor na lista sequencial
//! resultado: -1=falha, >=0: posição do valor
int lista_linear_procura(lista_linear_t * l, char* valor) {
    for (int i = 0; i < l->quantidade; i++) {
        if(strcmp(valor, l->area[i]) == 0) {
            return i;
        }
    }
    return -1;
}

//! obtém valor da posição "pos"
//! se pos inválida, retorna NULL
char* lista_linear_obtem(lista_linear_t * l, uint32_t pos) {
    if(!lista_linear_valido(l) || pos > l->quantidade) {
        return NULL;
    }

    return l->area[pos];
}

//! obtém valor no fim da lista
//! se lista vazia, retorna NULL
char* lista_linear_ultimo(lista_linear_t * l) {
    return l->area[l->quantidade-1];
}

//! obtém valor no início da lista
//! se lista vazia, retorna NULL
char* lista_linear_primeiro(lista_linear_t * l) {
    return l->area[0];
}

//! retorna 1 se lista estiver vazia, e 0 caso contrário
int lista_linear_vazia(lista_linear_t * l) {
    return l->quantidade == 0;
}

//! retorna o comprimento da lista
int lista_linear_comprimento(lista_linear_t * l) {
    return l->quantidade;
}

//! gera uma cópia da lista
//! resultado: um ponteiro para a nova lista, ou NULL em caso de erro
lista_linear_t * lista_linear_clona(lista_linear_t * l) {
    if(!lista_linear_valido(l)) {
        return NULL;
    }

    lista_linear_t * nova_lista = lista_linear_cria();
    if (!nova_lista) {
        return NULL;
    }

    for (int i = 0; i < l->quantidade; i++) {
        if (!lista_linear_adiciona(nova_lista, l->area[i])) {
            lista_linear_destroi(nova_lista);
            return NULL;
        }
    }

    return nova_lista;
}

//! ordena a lista em ordem alfabética
void lista_linear_ordena(lista_linear_t * l) {
    if(!lista_linear_valido(l)) {
        return;
    }

    for (int i = 0; i < l->quantidade; i++) {
        for(int j = 0; j < l->quantidade - i - 1; j++) {
            if (strcmp(l->area[j], l->area[j + 1]) > 0) {
                char* tmp = l->area[j];
                l->area[j] = l->area[j + 1];
                l->area[j + 1] = tmp;
            }
        }
    }
}

// adiciona um valor em uma lista ordenada
// resultado: 1=sucesso, 0=falha
int lista_linear_adiciona_ordenada(lista_linear_t * l, void* valor) {
    if (!lista_linear_valido(l) || !valor) {
        return 0;
    }

    if (l->quantidade >= l->cap) {
        if (!lista_linear_expande(l)) {
            return 0;
        }
    }

    int i = l->quantidade - 1;
    while (i >= 0 && strcmp(l->area[i], valor) > 0) {
        l->area[i + 1] = l->area[i];
        i--;
    }

    // Evitar duplicação de valores
    if (i >= 0 && strcmp(l->area[i], valor) == 0) {
        return 0;
    }

    l->area[i + 1] = strdup(valor);
    l->quantidade++;

    if (!l->area[l->quantidade]) {
        return 0;
    }

    return 1;
}

// procura um valor na lista ordenada
// resultado: -1=falha, >=0: posição do valor
int lista_linear_procura_ordenada(lista_linear_t * l, void* valor){
    if (!lista_linear_valido(l) || !valor) {
        return -1;
    }

    int inicio = 0;
    int fim = l->quantidade - 1;

    while (inicio <= fim) { // A procura do valor na lista é realizada através da busca binária
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(l->area[meio], valor);

        if (cmp == 0) {
            return meio;
        }

        if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

// remove um valor de uma lista ordenada
// resultado: 1=sucesso, 0=falha
int lista_linear_remove_ordenada(lista_linear_t * l, void* valor){
    if (!lista_linear_valido(l) || !valor) {
        return 0;
    }

    int pos = lista_linear_procura_ordenada(l, valor);
    if (pos == -1) {
        return 0;
    }

    free(l->area[pos]);
    for (int i = pos; i < l->quantidade - 1; i++) {
        l->area[i] = l->area[i + 1];
    }

    l->quantidade--;
    return 1;
}