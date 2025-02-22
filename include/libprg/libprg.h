#ifndef LIBPRG_LIBPRG_H
#define LIBPRG_LIBPRG_H

#include <libprg/lista_linear.h>
#include <libprg/lista.h>
#include <libprg/fila.h>
#include <libprg/pilha.h>
#include <libprg/thash.h>
#include <libprg/apb.h>
#include <libprg/conjunto.h>

// macro para facilitar a criação de uma estrutura de dados
// ed: nome da estrutura de dados, que deve ser: lista_linear, lista, fila, pilha, thash, conjunto ou apb
// tipo: o tipo de dados a ser armazenado na estrutura de dados
#define libprg_cria(ed, tipo) ed ## _cria(gconf_ ## tipo ())

#endif