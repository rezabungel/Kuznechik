#pragma once
#ifndef _KUZNECHIK_H_
#define _KUZNECHIK_H_

#include <cstdint>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif

#include "kuznechik_const.h"

#define BLOCK_SIZE 16     // Block size: 16 bytes (128 bits)
#define KEY_SIZE 32       // Key size: 32 bytes (256 bits)
#define COUNT_ITER_KEY 10 // Number of iteration (round) cipher keys

extern "C" void GOST_Kuz_Encrypt(const uint8_t *blk, const uint8_t *key, uint8_t *out_blk);
extern "C" void GOST_Kuz_Decrypt(const uint8_t *blk, const uint8_t *key, uint8_t *out_blk);

#endif // _KUZNECHIK_H_