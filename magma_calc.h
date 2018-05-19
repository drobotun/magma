#ifndef MAGMA_CALC_H
#define MAGMA_CALC_H

#include <stdfix.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>

#include "magma_const.h"

typedef uint8_t vect[4]; //блок размером 32 бита

vect iter_key[32]; //итерационные ключи шифрования

void
GOST_Magma_Expand_Key(const uint8_t *key);

void
GOST_Magma_Encript(const uint8_t *blk, uint8_t *out_blk);

void
GOST_Magma_Decript(const uint8_t *blk, uint8_t *out_blk);

#endif // MAGMA_CALC_H
