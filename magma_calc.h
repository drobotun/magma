#ifndef MAGMA_CALC_H
#define MAGMA_CALC_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "magma_const.h"

typedef uint8_t vect[4]; // 32-bit block

typedef struct {
    vect iter_key[32]; // iteration cipher keys
} magma_ctx;


void magma_init(magma_ctx* ctx, const uint8_t* key);
void magma_encrypt(magma_ctx* ctx, const uint8_t* blk, uint8_t* out_blk);
void magma_decrypt(magma_ctx* ctx, const uint8_t* blk, uint8_t* out_blk);

#endif // MAGMA_CALC_H
