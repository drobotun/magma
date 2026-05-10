#include "magma_calc.h"
#include "magma_test.h"

int main(int argc, char *argv[])
{
    magma_ctx ctx;
    uint8_t out_blk[8];
    magma_init(&ctx, test_key);
    magma_encrypt(&ctx, encrypt_test_string, out_blk);
    magma_decrypt(&ctx, decrypt_test_string, out_blk);
    return 0;
}
