#ifndef MAGMA_CALC_H
#define MAGMA_CALC_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "magma_const.h"

#define BLOCK_SIZE 8
#define KEY_SIZE 32

typedef uint8_t vect[BLOCK_SIZE] __attribute__((aligned(16))); // 64-bit block

typedef struct {
    uint8_t iter_key[8][KEY_SIZE]; // iteration cipher keys
} magma_ctx;


void magma_init(magma_ctx* ctx, const uint8_t* key);
void magma_encrypt(magma_ctx* ctx, const uint8_t* blk, uint8_t* out_blk);
void magma_decrypt(magma_ctx* ctx, const uint8_t* blk, uint8_t* out_blk);

#endif // MAGMA_CALC_H
