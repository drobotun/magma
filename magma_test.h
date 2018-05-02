#ifndef MAGMA_TEST_H
#define MAGMA_TEST_H

static const unsigned char test_key[32] = {
    0xff, 0xee, 0xdd, 0xcc,
    0xbb, 0xaa, 0x99, 0x88,
    0x77, 0x66, 0x55, 0x44,
    0x33, 0x22, 0x11, 0x00,
    0xf0, 0xf1, 0xf2, 0xf3,
    0xf4, 0xf5, 0xf6, 0xf7,
    0xf8, 0xf9, 0xfa, 0xfb,
    0xfc, 0xfd, 0xfe, 0xff
};

static const unsigned char encrypt_test_string[8] = {
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
};

static const unsigned char decrypt_test_string[8] = {
    0x4e, 0xe9, 0x01, 0xe5, 0xc2, 0xd8, 0xca, 0x3d,
};

#endif // MAGMA_TEST_H