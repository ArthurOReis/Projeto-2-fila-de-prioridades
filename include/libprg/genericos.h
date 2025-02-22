//
// Created by msobral on 20/06/24.
//

#ifndef LIBPRG_GENERICOS_H
#define LIBPRG_GENERICOS_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef int(*Fcompare)(const void*, const void*);
typedef void(*Fdestroi)(void*);
typedef void*(*Fclone)(void*);
typedef size_t(*Fsize)(void*);
typedef uint32_t(*Fhash)(void*, uint32_t len);

// encapsula as funções para manipular tipos genéricos
typedef struct {
    Fcompare f_comp;
    Fclone f_clone;
    Fdestroi f_destroi;
    Fsize f_size;
    Fhash f_hash;
} gconf_t;

#define g_alloc(var, tipo) tipo* var = malloc(sizeof(tipo))
#define g_create(var, tipo, gconf) g_alloc(var, tipo); \
var->gconf = gconf

// facilitadores para referenciar ponteiros para tipos específicos
#define from_ref(x, tipo) *(tipo*)x
#define from_long_ref(x) from_ref(x, long)
#define from_int_ref(x) from_ref(x, int)
#define from_ulong_ref(x) from_ref(x, unsigned long)
#define from_uint_ref(x) from_ref(x, unsigned int)
#define from_char_ref(x) from_ref(x, char)
#define from_uchar_ref(x) from_ref(x, unsigned char)
#define from_float_ref(x) from_ref(x, float)
#define from_double_ref(x) from_ref(x, double)
#define from_string_ref(x) (char*)x

// macros para ajudar a obter as funções de um objeto que inclui um gconf_t (cujo campo deve se chamar gconf)
#define gconf(x) x->gconf
#define g_comp(obj) obj->gconf.f_comp
#define g_compare(obj, v1, v2) obj->gconf.f_comp(v1, v2)
#define g_clone(obj) obj->gconf.f_clone
#define g_copy(obj, val) obj->gconf.f_clone(val)
#define g_destroi(obj) obj->gconf.f_destroi
#define g_free(obj, val) obj->gconf.f_destroi(val)
#define g_sizeof(obj, val) obj->gconf.f_size(val)

// funções para tipos nativos
 int g_comp_int(const void * x, const void * y);

 int g_comp_uint(const void * x, const void * y);

 int g_comp_double(const void * x, const void * y);

 int g_comp_char(const void * x, const void * y);

 int g_comp_uchar(const void * x, const void * y);

 int g_comp_float(const void * x, const void * y);
 int g_comp_long(const void * x, const void * y);

 int g_comp_ulong(const void * x, const void * y);
// A função para destruir tipo genérico é simplesmente "free" da stdlib !

// clone
#define g_clone_nativo(x, tipo) tipo* ptr = malloc(sizeof(tipo)); \
*ptr = *(tipo*)x;                                                        \
return ptr;

 void* g_clone_int(void * x);

 void* g_clone_uint(void * x);
 void* g_clone_double(void * x);

 void* g_clone_char(void * x);

 void * g_clone_uchar(void * x);
 void* g_clone_float(void * x);

 void* g_clone_long(void * x);
 void * g_clone_ulong(void * x);

//
size_t g_size_int(void * x);

size_t g_size_uint(void * x);
size_t g_size_double(void * x);

size_t g_size_char(void * x);

size_t g_size_uchar(void * x);
size_t g_size_float(void * x);

size_t g_size_long(void *x);
size_t g_size_ulong(void * x);
size_t g_size_string(void * x);
//
//#define gconf_gen(tipo) gconf_t gconf = {.f_clone=g_clone_ ## tipo, .f_comp=g_comp_ ## tipo, .f_destroi=free}

 gconf_t gconf_int();

 gconf_t gconf_uint();

 gconf_t gconf_float();

 gconf_t gconf_double();

 gconf_t gconf_long();

 gconf_t gconf_ulong();

 gconf_t gconf_char();

 gconf_t gconf_uchar();

gconf_t gconf_string();


// a função hash geral, a ser usada por default
uint32_t fletcher32(void* val, uint32_t len);

#endif //LIBPRG_GENERICOS_H
