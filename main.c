#include "magma_calc.h"
#include "magma_test.h"

int main(int argc, char *argv[])
{
    uint8_t out_blk[4];
    GOST_Magma_Expand_Key(test_key);
    GOST_Magma_Encript(encrypt_test_string, out_blk);
    GOST_Magma_Decript(decrypt_test_string, out_blk);
    return 0;
}
