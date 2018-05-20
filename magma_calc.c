#include "magma_calc.h"

#define DEBUG_MODE

#ifdef DEBUG_MODE
static void
GOST_Magma_Blk_4_PrintDebug(uint8_t *state)
{
    int i;
    for (i = 0; i < 4; i++)
        printf("%02x", state[i]);
    printf("\n");
}

static void
GOST_Magma_Blk_8_PrintDebug(uint8_t *state)
{
    int i;
    for (i = 0; i < 8; i++)
        printf("%02x", state[i]);
    printf("\n");
}
#endif

static void
GOST_Magma_T(const uint8_t *in_data, uint8_t *out_data)
{
    uint8_t first_part_byte, sec_part_byte;
    int i;
    for (i = 0; i < 4; i++)
    {
        first_part_byte = (in_data[i] & 0x0f);
        sec_part_byte = (in_data[i] & 0xf0) >> 4;
        first_part_byte = Pi[i * 2] [first_part_byte];
        sec_part_byte = Pi[i * 2 + 1] [sec_part_byte];
        out_data[i] =  (sec_part_byte << 4) | first_part_byte;
    }
}

static void
GOST_Magma_Add(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
    int i;
    for (i = 0; i < 4; i++)
        c[i] = a[i]^b[i];
}

static void
GOST_Magma_Add_32(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
    int i;
    unsigned int internal = 0;
    for (i = 0; i < 4; i++)
    {
        internal = a[i] + b[i] + (internal >> 8);
        c[i] = internal & 0xff;
    }
}

static void
GOST_Magma_g(const uint8_t *k, const uint8_t *a, uint8_t *out_data)
{
    uint8_t internal[4];
    uint32_t out_data_32;
    GOST_Magma_Add_32(a, k, internal);
    GOST_Magma_T(internal, internal);
    out_data_32 = internal[3];
    out_data_32 = (out_data_32  << 8) + internal[2];
    out_data_32 = (out_data_32  << 8) + internal[1];
    out_data_32 = (out_data_32  << 8) + internal[0];
    out_data_32 = (out_data_32 << 11)|(out_data_32 >> 21);
    out_data[0] = out_data_32;
    out_data[1] = out_data_32 >> 8;
    out_data[2] = out_data_32 >> 16;
    out_data[3] = out_data_32 >> 24;
}

static void
GOST_Magma_G(const uint8_t *k, const uint8_t *a, uint8_t *out_data)
{
    uint8_t a_0[4];
    uint8_t a_1[4];
    uint8_t G[4];
    int i;
    for(i = 0; i < 4; i++)
    {
       a_1[i] = a[4 + i];
       a_0[i] = a[i];
    }
    GOST_Magma_g(k, a_0, G);
    GOST_Magma_Add(a_1, G, G);
    for(i = 0; i < 4; i++)
    {
        a_1[i] = a_0[i];
        a_0[i] = G[i];
    }
    for(i = 0; i < 4; i++)
    {
        out_data[i] = a_0[i];
        out_data[4 + i] = a_1[i];
    }

}

static void
GOST_Magma_G_Fin(const uint8_t *k, const uint8_t *a, uint8_t *out_data)
{
    uint8_t a_0[4];
    uint8_t a_1[4];
    uint8_t G[4];
    int i;
    for(i = 0; i < 4; i++)
    {
       a_1[i] = a[4 + i];
       a_0[i] = a[i];
    }
    GOST_Magma_g(k, a_0, G);
    GOST_Magma_Add(a_1, G, G);
    for(i = 0; i < 4; i++)
        a_1[i] = G[i];
    for(i = 0; i < 4; i++)
    {
        out_data[i] = a_0[i];
        out_data[4 + i] = a_1[i];
    }
}

void
GOST_Magma_Expand_Key(const uint8_t *key)
{
    memcpy(iter_key[7], key, 4);
    memcpy(iter_key[6], key + 4, 4);
    memcpy(iter_key[5], key + 8, 4);
    memcpy(iter_key[4], key + 12, 4);
    memcpy(iter_key[3], key + 16, 4);
    memcpy(iter_key[2], key + 20, 4);
    memcpy(iter_key[1], key + 24, 4);
    memcpy(iter_key[0], key + 28, 4);
    memcpy(iter_key[15], key, 4);
    memcpy(iter_key[14], key + 4, 4);
    memcpy(iter_key[13], key + 8, 4);
    memcpy(iter_key[12], key + 12, 4);
    memcpy(iter_key[11], key + 16, 4);
    memcpy(iter_key[10], key + 20, 4);
    memcpy(iter_key[9], key + 24, 4);
    memcpy(iter_key[8], key + 28, 4);
    memcpy(iter_key[23], key, 4);
    memcpy(iter_key[22], key + 4, 4);
    memcpy(iter_key[21], key + 8, 4);
    memcpy(iter_key[20], key + 12, 4);
    memcpy(iter_key[19], key + 16, 4);
    memcpy(iter_key[18], key + 20, 4);
    memcpy(iter_key[17], key + 24, 4);
    memcpy(iter_key[16], key + 28, 4);
    memcpy(iter_key[31], key + 28, 4);
    memcpy(iter_key[30], key + 24, 4);
    memcpy(iter_key[29], key + 20, 4);
    memcpy(iter_key[28], key + 16, 4);
    memcpy(iter_key[27], key + 12, 4);
    memcpy(iter_key[26], key + 8, 4);
    memcpy(iter_key[25], key + 4, 4);
    memcpy(iter_key[24], key, 4);

#ifdef DEBUG_MODE
    printf("Iteration cipher keys:\n");
    int i;
    for (i = 0; i < 32; i++)
    {
        printf("K%d=", i+1);
        GOST_Magma_Blk_4_PrintDebug(iter_key[i]);
    }
#endif
}

void
GOST_Magma_Encrypt(const uint8_t *blk, uint8_t *out_blk)
{
#ifdef DEBUG_MODE
    printf("Text:\n");
    GOST_Magma_Blk_8_PrintDebug(blk);
#endif

    int i;
    GOST_Magma_G(iter_key[0], blk, out_blk);
    for(i = 1; i < 31; i++)
        GOST_Magma_G(iter_key[i], out_blk, out_blk);
    GOST_Magma_G_Fin(iter_key[31], out_blk, out_blk);

#ifdef DEBUG_MODE
    printf("Encrypted text:\n");
    GOST_Magma_Blk_8_PrintDebug(out_blk);
#endif
}

void
GOST_Magma_Decrypt(const uint8_t *blk, uint8_t *out_blk)
{
#ifdef DEBUG_MODE
    printf("Gipher text:\n");
    GOST_Magma_Blk_8_PrintDebug(blk);
#endif

    int i;
    GOST_Magma_G(iter_key[31], blk, out_blk);
    for(i = 30; i > 0; i--)
        GOST_Magma_G(iter_key[i], out_blk, out_blk);
    GOST_Magma_G_Fin(iter_key[0], out_blk, out_blk);

#ifdef DEBUG_MODE
    printf("Decrypted text:\n");
    GOST_Magma_Blk_8_PrintDebug(out_blk);
#endif
}
