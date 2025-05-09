#include "kuznechik.h"

#ifdef DEBUG
// Debug function to print the state bytes in hexadecimal format
static void GOST_Kuz_PrintDebug(const uint8_t *state, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%02x", state[i]);
    }
}
#endif

// Bitwise addition of two binary vectors modulo 2 (XOR)
static void GOST_Kuz_X(const uint8_t *vect1, const uint8_t *vect2, uint8_t *out_vect)
{
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        out_vect[i] = vect1[i] ^ vect2[i];
    }
}

// Multiplication of numbers in a finite field (Galois field) over the irreducible polynomial x^8 + x^7 + x^6 + x + 1
static uint8_t GOST_Kuz_GF_mul(uint8_t a, uint8_t b)
{
    uint8_t c = 0;
    uint8_t hi_bit;
    for (int i = 0; i < 8; ++i)
    {
        if (b & 1)
        {
            c ^= a;
        }
        hi_bit = a & 0x80;
        a <<= 1;
        if (hi_bit)
        {
            a ^= 0xC3; // The polynomial x^8 + x^7 + x^6 + x + 1
        }
        b >>= 1;
    }
    return c;
}

// Non-linear bijective transformation (S-box) based on the predefined substitution table 'Pi'
static void GOST_Kuz_S(const uint8_t *in_data, uint8_t *out_data)
{
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        out_data[i] = Pi[in_data[i]];
    }
}

// Reverse non-linear bijective transformation (S-box) based on the predefined substitution table 'reverse_Pi'
static void GOST_Kuz_reverse_S(const uint8_t *in_data, uint8_t *out_data)
{
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        out_data[i] = reverse_Pi[in_data[i]];
    }
}

// R-transformation
static void GOST_Kuz_R(uint8_t *state)
{
    uint8_t a_15 = GOST_Kuz_GF_mul(state[0], l_vec[0]);
    uint8_t internal[BLOCK_SIZE];

    for (int i = 1; i < BLOCK_SIZE; ++i)
    {
        internal[i - 1] = state[i];
        a_15 ^= GOST_Kuz_GF_mul(state[i], l_vec[i]);
    }

    internal[BLOCK_SIZE - 1] = a_15;
    memcpy(state, internal, BLOCK_SIZE);
}

// Reverse R-transformation
static void GOST_Kuz_reverse_R(uint8_t *state)
{
    uint8_t a_0 = state[BLOCK_SIZE - 1];
    uint8_t internal[BLOCK_SIZE];

    for (int i = 1; i < BLOCK_SIZE; ++i)
    {
        internal[i] = state[i - 1];
        a_0 ^= GOST_Kuz_GF_mul(internal[i], l_vec[i]);
    }

    internal[0] = a_0;
    memcpy(state, internal, BLOCK_SIZE);
}

// L-transformation
static void GOST_Kuz_L(const uint8_t *in_data, uint8_t *out_data)
{
    uint8_t internal[BLOCK_SIZE];
    memcpy(internal, in_data, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        GOST_Kuz_R(internal);
    }
    memcpy(out_data, internal, BLOCK_SIZE);
}

// Reverse L-transformation
static void GOST_Kuz_reverse_L(const uint8_t *in_data, uint8_t *out_data)
{
    uint8_t internal[BLOCK_SIZE];
    memcpy(internal, in_data, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        GOST_Kuz_reverse_R(internal);
    }
    memcpy(out_data, internal, BLOCK_SIZE);
}

// The F-function implementing transformations in the Feistel network
static void GOST_Kuz_F(const uint8_t *in_key_1, const uint8_t *in_key_2,
                       uint8_t *out_key_1, uint8_t *out_key_2,
                       const uint8_t *iter_const)
{
    uint8_t internal[BLOCK_SIZE];
    memcpy(out_key_2, in_key_1, BLOCK_SIZE);

    GOST_Kuz_X(in_key_1, iter_const, internal);
    GOST_Kuz_S(internal, internal);
    GOST_Kuz_L(internal, internal);
    GOST_Kuz_X(internal, in_key_2, out_key_1);
}

// The function for calculating iteration (round) cipher keys
static void GOST_Kuz_Expand_Key(const uint8_t *key, uint8_t iter_key[COUNT_ITER_KEY][BLOCK_SIZE])
{
#ifdef DEBUG
    std::cout << "\t*****************************" << std::endl
              << "\tThe function \"GOST_Kuz_Expand_Key\" has begun." << std::endl
              << "\tCipher key passed:" << std::endl
              << "\t\t";
    GOST_Kuz_PrintDebug(key, KEY_SIZE);
    std::cout << std::endl
              << "\tGenerating iteration (round) cipher keys..." << std::endl;
#endif

    uint8_t iter_1[KEY_SIZE / 2];
    uint8_t iter_2[KEY_SIZE / 2];
    uint8_t iter_3[KEY_SIZE / 2];
    uint8_t iter_4[KEY_SIZE / 2];

    memcpy(iter_1, key + KEY_SIZE / 2, KEY_SIZE / 2);
    memcpy(iter_2, key, KEY_SIZE / 2);

    memcpy(iter_key[0], iter_1, KEY_SIZE / 2);
    memcpy(iter_key[1], iter_2, KEY_SIZE / 2);

    for (int i = 0; i < 4; ++i)
    {
        GOST_Kuz_F(iter_1, iter_2, iter_3, iter_4, iter_C[0 + 8 * i]);
        GOST_Kuz_F(iter_3, iter_4, iter_1, iter_2, iter_C[1 + 8 * i]);

        GOST_Kuz_F(iter_1, iter_2, iter_3, iter_4, iter_C[2 + 8 * i]);
        GOST_Kuz_F(iter_3, iter_4, iter_1, iter_2, iter_C[3 + 8 * i]);

        GOST_Kuz_F(iter_1, iter_2, iter_3, iter_4, iter_C[4 + 8 * i]);
        GOST_Kuz_F(iter_3, iter_4, iter_1, iter_2, iter_C[5 + 8 * i]);

        GOST_Kuz_F(iter_1, iter_2, iter_3, iter_4, iter_C[6 + 8 * i]);
        GOST_Kuz_F(iter_3, iter_4, iter_1, iter_2, iter_C[7 + 8 * i]);

        memcpy(iter_key[2 * i + 2], iter_1, KEY_SIZE / 2);
        memcpy(iter_key[2 * i + 3], iter_2, KEY_SIZE / 2);
    }

#ifdef DEBUG
    std::cout << "\tGenerated iteration (round) cipher keys:" << std::endl;
    for (int i = 0; i < COUNT_ITER_KEY; ++i)
    {
        std::cout << "\t\t";
        GOST_Kuz_PrintDebug(iter_key[i], BLOCK_SIZE);
        std::cout << std::endl;
    }
    std::cout << "\tThe function \"GOST_Kuz_Expand_Key\" has completed." << std::endl;
    std::cout << "\t*****************************" << std::endl;
#endif
}

// Block encryption function
extern "C" void GOST_Kuz_Encrypt(const uint8_t *blk, const uint8_t *key, uint8_t *out_blk)
{
#ifdef DEBUG
    std::cout << "*****************************" << std::endl
              << "The function \"GOST_Kuz_Encrypt\" has begun." << std::endl
              << "Block to encrypt:" << std::endl
              << '\t';
    GOST_Kuz_PrintDebug(blk, BLOCK_SIZE);
    std::cout << std::endl
              << "Cipher key passed:" << std::endl
              << '\t';
    GOST_Kuz_PrintDebug(key, KEY_SIZE);
    std::cout << std::endl
              << "Generating iteration (round) cipher keys (calling the function \"GOST_Kuz_Expand_Key\")..." << std::endl;
#endif

    uint8_t iter_key[COUNT_ITER_KEY][BLOCK_SIZE]; // Iteration (round) cipher keys
    GOST_Kuz_Expand_Key(key, iter_key);

#ifdef DEBUG
    std::cout << "Iteration (round) cipher keys generated." << std::endl
              << "Encrypting the block..." << std::endl;
#endif

    memcpy(out_blk, blk, BLOCK_SIZE);

    for (int i = 0; i < 9; ++i)
    {
        GOST_Kuz_X(iter_key[i], out_blk, out_blk);
        GOST_Kuz_S(out_blk, out_blk);
        GOST_Kuz_L(out_blk, out_blk);
    }
    GOST_Kuz_X(out_blk, iter_key[9], out_blk);

#ifdef DEBUG
    std::cout << "Encryption complete. The encrypted block:" << std::endl
              << '\t';
    GOST_Kuz_PrintDebug(out_blk, BLOCK_SIZE);
    std::cout << std::endl
              << "The function \"GOST_Kuz_Encrypt\" has completed." << std::endl
              << "*****************************" << std::endl;
#endif
}

// Block decryption function
extern "C" void GOST_Kuz_Decrypt(const uint8_t *blk, const uint8_t *key, uint8_t *out_blk)
{
#ifdef DEBUG
    std::cout << "*****************************" << std::endl
              << "The function \"GOST_Kuz_Decrypt\" has begun." << std::endl
              << "Block to decrypt:" << std::endl
              << '\t';
    GOST_Kuz_PrintDebug(blk, BLOCK_SIZE);
    std::cout << std::endl
              << "Cipher key passed:" << std::endl
              << '\t';
    GOST_Kuz_PrintDebug(key, KEY_SIZE);
    std::cout << std::endl
              << "Generating iteration (round) cipher keys (calling the function \"GOST_Kuz_Expand_Key\")..." << std::endl;
#endif

    uint8_t iter_key[COUNT_ITER_KEY][BLOCK_SIZE]; // Iteration (round) cipher keys
    GOST_Kuz_Expand_Key(key, iter_key);

#ifdef DEBUG
    std::cout << "Iteration (round) cipher keys generated." << std::endl
              << "Decrypting the block..." << std::endl;
#endif

    memcpy(out_blk, blk, BLOCK_SIZE);

    for (int i = 9; i > 0; --i)
    {
        GOST_Kuz_X(iter_key[i], out_blk, out_blk);
        GOST_Kuz_reverse_L(out_blk, out_blk);
        GOST_Kuz_reverse_S(out_blk, out_blk);
    }
    GOST_Kuz_X(iter_key[0], out_blk, out_blk);

#ifdef DEBUG
    std::cout << "Decryption complete. The decrypted block:" << std::endl
              << '\t';
    GOST_Kuz_PrintDebug(out_blk, BLOCK_SIZE);
    std::cout << std::endl
              << "The function \"GOST_Kuz_Decrypt\" has completed." << std::endl
              << "*****************************" << std::endl;
#endif
}