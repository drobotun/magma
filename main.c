#include "magma_calc.h"
#include "magma_test.h"

int main(int argc, char *argv[])
{
    magma_ctx ctx;
    vect block;
    magma_init(&ctx, test_key);
    magma_encrypt(&ctx, encrypt_test_string, block);
    magma_decrypt(&ctx, decrypt_test_string, block);
    return 0;
}
