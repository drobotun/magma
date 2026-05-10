===========================
GOST R 34.12 - 2015 "Magma"
===========================

.. image:: https://img.shields.io/github/license/drobotun/virustotalapi3?style=flat
    :target: http://doge.mit-license.org
.. image:: https://img.shields.io/badge/HACKMAG-blue?color=purple
    :target: https://hackmag.com/stuff/working-with-magma
.. image:: https://img.shields.io/badge/-%5D%5Bakep-blue?color=blue
    :target: https://xakep.ru/2018/05/10/working-with-magma/

Implementation of the Magma block cipher (GOST R 34.12-2015) in C.
This repository contains an implementation of the Russian national standard
for block cipher Magma (also known as `GOST R 34.12-2015`_).
The algorithm uses 64‑bit blocks and 256‑bit keys.

.. _GOST R 34.12-2015: https://tc26.ru/standard/gost/GOST_R_3412-2015.pdf

Features
--------

- Pure C (C99) implementation, no external crypto libraries.
- Supports encryption and decryption.
- Optional debug output when compiled with ``DEBUG_MODE``.
- Includes test vectors in a separate header.

Project Structure
-----------------

::

   ├── magma_calc.h    // public API declarations
   ├── magma_calc.c    // algorithm implementation
   ├── magma_const.h   // constants (pi, reverse_pi, l_vec)
   └── magma_test.h    // test vectors (key, plaintext, expected ciphertext)

Requirements
------------

- C99 compatible compiler (GCC, Clang, MSVC).
- Standard headers: ``stdint.h``, ``string.h``, ``stdio.h``, ``stdlib.h``.

Building
--------

To use in your project:

- Copy the files ``magma_calc.h``, ``magma_const.h``,
  ``magma_calc.c`` into your project directory.
- Include the header ``magma_calc.h``.
- Compile your project together with ``magma_calc.c``::

   gcc -o magma main.c magma_calc.c

To enable debug output (prints round keys, intermediate states)::

   gcc -DDEBUG_MODE -o magma main.c magma_calc.c

Usage
-----

Key Setup
~~~~~~~~~

Before encryption or decryption, you must initialise a ``magma_ctx``
structure with the 256‑bit key:

.. code-block:: c

   #include "magma_calc.h"

   uint8_t key[KEY_SIZE] = { ... };   // 32 bytes
   magma_ctx ctx;
   magma_init(&ctx, key);

Encryption
~~~~~~~~~~

``magma_encrypt()`` takes a plaintext block (64 bits) and writes the
ciphertext block to the output buffer:

.. code-block:: c

   uint8_t plaintext[BLOCK_SIZE] = { ... };
   uint8_t ciphertext[BLOCK_SIZE];
   magma_encrypt(&ctx, plaintext, ciphertext);

Decryption
~~~~~~~~~~

Use ``magma_decrypt()`` to reverse the process:

.. code-block:: c

   uint8_t decrypted[BLOCK_SIZE];
   magma_decrypt(&ctx, ciphertext, decrypted);

Full Example (with test vectors)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The header ``magma_test.h`` provides a known key, plaintext, and the
expected ciphertext (from the standard). You can use it to verify the
implementation:

.. code-block:: c

   #include <stdio.h>
   #include <string.h>
   #include "magma_calc.h"
   #include "magma_test.h"

   int main() {
       uint8_t ciphertext[BLOCK_SIZE];
       uint8_t decrypted[BLOCK_SIZE];

       magma_ctx ctx;
       magma_init(&ctx, test_key);
       magma_encrypt(&ctx, encrypt_test_string, ciphertext);
       magma_decrypt(&ctx, decrypt_test_string, decrypted);

       // Check against expected ciphertext (decrypt_test_string)
       int encrypt_ok = memcmp(ciphertext, decrypt_test_string, BLOCK_SIZE) == 0;
       int decrypt_ok = memcmp(decrypted, encrypt_test_string, BLOCK_SIZE) == 0;

       printf("Encryption %s\n", encrypt_ok ? "correct" : "failed");
       printf("Decryption %s\n", decrypt_ok ? "correct" : "failed");
       return 0;
   }

**Note:** The test vectors are:

- Key: ``test_key`` (32 bytes)
- Plaintext: ``encrypt_test_string`` (8 bytes)
- Expected ciphertext: ``decrypt_test_string`` (8 bytes)

API Reference
-------------

- ``vect`` - 64‑bit block (aligned to 16 bytes). Defined as ``uint8_t[BLOCK_SIZE]``.
- ``magma_ctx`` - context structure that stores iterative constants and round keys.
- ``void magma_init(magma_ctx* ctx, const uint8_t* key)`` - expands the 256‑bit key and fills the context.

    Parameters:

    - ``ctx`` - pointer to context structure.
    - ``key`` - pointer to 32‑byte key array.

- ``void magma_encrypt(magma_ctx* ctx, const uint8_t* plain_block, uint8_t* cipher_block)`` - encrypts a single 64‑bit block.

    Parameters:

    - ``ctx`` - initialised context.
    - ``plain_block`` - input plaintext block (8 bytes).
    - ``cipher_block`` - output ciphertext block (8 bytes).

- ``void magma_decrypt(magma_ctx* ctx, const uint8_t* cipher_block, uint8_t* plain_block)`` - decrypts a single 64‑bit block.

    Parameters:

    - ``ctx`` - initialised context.
    - ``cipher_block`` - input ciphertext block (8 bytes).
    - ``plain_block`` - output plaintext block (8 bytes).

Debug Mode
----------

When ``DEBUG_MODE`` is defined, the following data is printed during execution:

- Round keys after expansion.
- Plaintext before encryption.
- Ciphertext after encryption.
- Ciphertext before decryption.
- Decrypted plaintext after decryption.

To disable debug output, remove the ``-DDEBUG_MODE`` compiler flag.

Notes
-----

- The implementation does not use dynamic memory allocation (apart from
  constant global arrays).
- Block size (``BLOCK_SIZE``) and key size (``KEY_SIZE``) are fixed as per
  the standard.
- The test header ``magma_test.h`` is **not required** for the library to
  work; it is provided for verification purposes only.

License
-------

MIT
Copyright (c) 2019 Evgeny Drobotun

-------
