#pragma once
#ifndef _KUZNECHIK_CONST_H_
#define _KUZNECHIK_CONST_H_

// Substitution table (S-box) used for the non-linear bijective transformation
static const uint8_t Pi[256] = {
    0xFC, 0xEE, 0xDD, 0x11, 0xCF, 0x6E, 0x31, 0x16, 0xFB, 0xC4, 0xFA, 0xDA, 0x23, 0xC5, 0x04, 0x4D,
    0xE9, 0x77, 0xF0, 0xDB, 0x93, 0x2E, 0x99, 0xBA, 0x17, 0x36, 0xF1, 0xBB, 0x14, 0xCD, 0x5F, 0xC1,
    0xF9, 0x18, 0x65, 0x5A, 0xE2, 0x5C, 0xEF, 0x21, 0x81, 0x1C, 0x3C, 0x42, 0x8B, 0x01, 0x8E, 0x4F,
    0x05, 0x84, 0x02, 0xAE, 0xE3, 0x6A, 0x8F, 0xA0, 0x06, 0x0B, 0xED, 0x98, 0x7F, 0xD4, 0xD3, 0x1F,
    0xEB, 0x34, 0x2C, 0x51, 0xEA, 0xC8, 0x48, 0xAB, 0xF2, 0x2A, 0x68, 0xA2, 0xFD, 0x3A, 0xCE, 0xCC,
    0xB5, 0x70, 0x0E, 0x56, 0x08, 0x0C, 0x76, 0x12, 0xBF, 0x72, 0x13, 0x47, 0x9C, 0xB7, 0x5D, 0x87,
    0x15, 0xA1, 0x96, 0x29, 0x10, 0x7B, 0x9A, 0xC7, 0xF3, 0x91, 0x78, 0x6F, 0x9D, 0x9E, 0xB2, 0xB1,
    0x32, 0x75, 0x19, 0x3D, 0xFF, 0x35, 0x8A, 0x7E, 0x6D, 0x54, 0xC6, 0x80, 0xC3, 0xBD, 0x0D, 0x57,
    0xDF, 0xF5, 0x24, 0xA9, 0x3E, 0xA8, 0x43, 0xC9, 0xD7, 0x79, 0xD6, 0xF6, 0x7C, 0x22, 0xB9, 0x03,
    0xE0, 0x0F, 0xEC, 0xDE, 0x7A, 0x94, 0xB0, 0xBC, 0xDC, 0xE8, 0x28, 0x50, 0x4E, 0x33, 0x0A, 0x4A,
    0xA7, 0x97, 0x60, 0x73, 0x1E, 0x00, 0x62, 0x44, 0x1A, 0xB8, 0x38, 0x82, 0x64, 0x9F, 0x26, 0x41,
    0xAD, 0x45, 0x46, 0x92, 0x27, 0x5E, 0x55, 0x2F, 0x8C, 0xA3, 0xA5, 0x7D, 0x69, 0xD5, 0x95, 0x3B,
    0x07, 0x58, 0xB3, 0x40, 0x86, 0xAC, 0x1D, 0xF7, 0x30, 0x37, 0x6B, 0xE4, 0x88, 0xD9, 0xE7, 0x89,
    0xE1, 0x1B, 0x83, 0x49, 0x4C, 0x3F, 0xF8, 0xFE, 0x8D, 0x53, 0xAA, 0x90, 0xCA, 0xD8, 0x85, 0x61,
    0x20, 0x71, 0x67, 0xA4, 0x2D, 0x2B, 0x09, 0x5B, 0xCB, 0x9B, 0x25, 0xD0, 0xBE, 0xE5, 0x6C, 0x52,
    0x59, 0xA6, 0x74, 0xD2, 0xE6, 0xF4, 0xB4, 0xC0, 0xD1, 0x66, 0xAF, 0xC2, 0x39, 0x4B, 0x63, 0xB6};

// Reverse substitution table (S-box) used for the reverse non-linear bijective transformation
static const uint8_t reverse_Pi[256] = {
    0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91,
    0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18, 0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F,
    0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4, 0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,
    0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9, 0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5,
    0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B, 0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F,
    0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F, 0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,
    0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2, 0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B,
    0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11, 0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C,
    0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F, 0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,
    0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1, 0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD,
    0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0, 0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA,
    0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D, 0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,
    0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67, 0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04,
    0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88, 0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80,
    0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,
    0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7, 0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74};

// The vector of linear transformation
static const uint8_t l_vec[16] = {
    0x01, 0x94, 0x20, 0x85, 0x10, 0xC2, 0xC0, 0x01,
    0xFB, 0x01, 0xC0, 0xC2, 0x10, 0x85, 0x20, 0x94};

// Iteration constants C (Pre-calculated for performance improvement)
static const uint8_t iter_C[32][16] = {
    {0x01, 0x94, 0x84, 0xDD, 0x10, 0xBD, 0x27, 0x5D, 0xB8, 0x7A, 0x48, 0x6C, 0x72, 0x76, 0xA2, 0x6E}, // 1
    {0x02, 0xEB, 0xCB, 0x79, 0x20, 0xB9, 0x4E, 0xBA, 0xB3, 0xF4, 0x90, 0xD8, 0xE4, 0xEC, 0x87, 0xDC}, // 2
    {0x03, 0x7F, 0x4F, 0xA4, 0x30, 0x04, 0x69, 0xE7, 0x0B, 0x8E, 0xD8, 0xB4, 0x96, 0x9A, 0x25, 0xB2}, // 3
    {0x04, 0x15, 0x55, 0xF2, 0x40, 0xB1, 0x9C, 0xB7, 0xA5, 0x2B, 0xE3, 0x73, 0x0B, 0x1B, 0xCD, 0x7B}, // 4
    {0x05, 0x81, 0xD1, 0x2F, 0x50, 0x0C, 0xBB, 0xEA, 0x1D, 0x51, 0xAB, 0x1F, 0x79, 0x6D, 0x6F, 0x15}, // 5
    {0x06, 0xFE, 0x9E, 0x8B, 0x60, 0x08, 0xD2, 0x0D, 0x16, 0xDF, 0x73, 0xAB, 0xEF, 0xF7, 0x4A, 0xA7}, // 6
    {0x07, 0x6A, 0x1A, 0x56, 0x70, 0xB5, 0xF5, 0x50, 0xAE, 0xA5, 0x3B, 0xC7, 0x9D, 0x81, 0xE8, 0xC9}, // 7
    {0x08, 0x2A, 0xAA, 0x27, 0x80, 0xA1, 0xFB, 0xAD, 0x89, 0x56, 0x05, 0xE6, 0x16, 0x36, 0x59, 0xF6}, // 8
    {0x09, 0xBE, 0x2E, 0xFA, 0x90, 0x1C, 0xDC, 0xF0, 0x31, 0x2C, 0x4D, 0x8A, 0x64, 0x40, 0xFB, 0x98}, // 9
    {0x0A, 0xC1, 0x61, 0x5E, 0xA0, 0x18, 0xB5, 0x17, 0x3A, 0xA2, 0x95, 0x3E, 0xF2, 0xDA, 0xDE, 0x2A}, // 10
    {0x0B, 0x55, 0xE5, 0x83, 0xB0, 0xA5, 0x92, 0x4A, 0x82, 0xD8, 0xDD, 0x52, 0x80, 0xAC, 0x7C, 0x44}, // 11
    {0x0C, 0x3F, 0xFF, 0xD5, 0xC0, 0x10, 0x67, 0x1A, 0x2C, 0x7D, 0xE6, 0x95, 0x1D, 0x2D, 0x94, 0x8D}, // 12
    {0x0D, 0xAB, 0x7B, 0x08, 0xD0, 0xAD, 0x40, 0x47, 0x94, 0x07, 0xAE, 0xF9, 0x6F, 0x5B, 0x36, 0xE3}, // 13
    {0x0E, 0xD4, 0x34, 0xAC, 0xE0, 0xA9, 0x29, 0xA0, 0x9F, 0x89, 0x76, 0x4D, 0xF9, 0xC1, 0x13, 0x51}, // 14
    {0x0F, 0x40, 0xB0, 0x71, 0xF0, 0x14, 0x0E, 0xFD, 0x27, 0xF3, 0x3E, 0x21, 0x8B, 0xB7, 0xB1, 0x3F}, // 15
    {0x10, 0x54, 0x97, 0x4E, 0xC3, 0x81, 0x35, 0x99, 0xD1, 0xAC, 0x0A, 0x0F, 0x2C, 0x6C, 0xB2, 0x2F}, // 16
    {0x11, 0xC0, 0x13, 0x93, 0xD3, 0x3C, 0x12, 0xC4, 0x69, 0xD6, 0x42, 0x63, 0x5E, 0x1A, 0x10, 0x41}, // 17
    {0x12, 0xBF, 0x5C, 0x37, 0xE3, 0x38, 0x7B, 0x23, 0x62, 0x58, 0x9A, 0xD7, 0xC8, 0x80, 0x35, 0xF3}, // 18
    {0x13, 0x2B, 0xD8, 0xEA, 0xF3, 0x85, 0x5C, 0x7E, 0xDA, 0x22, 0xD2, 0xBB, 0xBA, 0xF6, 0x97, 0x9D}, // 19
    {0x14, 0x41, 0xC2, 0xBC, 0x83, 0x30, 0xA9, 0x2E, 0x74, 0x87, 0xE9, 0x7C, 0x27, 0x77, 0x7F, 0x54}, // 20
    {0x15, 0xD5, 0x46, 0x61, 0x93, 0x8D, 0x8E, 0x73, 0xCC, 0xFD, 0xA1, 0x10, 0x55, 0x01, 0xDD, 0x3A}, // 21
    {0x16, 0xAA, 0x09, 0xC5, 0xA3, 0x89, 0xE7, 0x94, 0xC7, 0x73, 0x79, 0xA4, 0xC3, 0x9B, 0xF8, 0x88}, // 22
    {0x17, 0x3E, 0x8D, 0x18, 0xB3, 0x34, 0xC0, 0xC9, 0x7F, 0x09, 0x31, 0xC8, 0xB1, 0xED, 0x5A, 0xE6}, // 23
    {0x18, 0x7E, 0x3D, 0x69, 0x43, 0x20, 0xCE, 0x34, 0x58, 0xFA, 0x0F, 0xE9, 0x3A, 0x5A, 0xEB, 0xD9}, // 24
    {0x19, 0xEA, 0xB9, 0xB4, 0x53, 0x9D, 0xE9, 0x69, 0xE0, 0x80, 0x47, 0x85, 0x48, 0x2C, 0x49, 0xB7}, // 25
    {0x1A, 0x95, 0xF6, 0x10, 0x63, 0x99, 0x80, 0x8E, 0xEB, 0x0E, 0x9F, 0x31, 0xDE, 0xB6, 0x6C, 0x05}, // 26
    {0x1B, 0x01, 0x72, 0xCD, 0x73, 0x24, 0xA7, 0xD3, 0x53, 0x74, 0xD7, 0x5D, 0xAC, 0xC0, 0xCE, 0x6B}, // 27
    {0x1C, 0x6B, 0x68, 0x9B, 0x03, 0x91, 0x52, 0x83, 0xFD, 0xD1, 0xEC, 0x9A, 0x31, 0x41, 0x26, 0xA2}, // 28
    {0x1D, 0xFF, 0xEC, 0x46, 0x13, 0x2C, 0x75, 0xDE, 0x45, 0xAB, 0xA4, 0xF6, 0x43, 0x37, 0x84, 0xCC}, // 29
    {0x1E, 0x80, 0xA3, 0xE2, 0x23, 0x28, 0x1C, 0x39, 0x4E, 0x25, 0x7C, 0x42, 0xD5, 0xAD, 0xA1, 0x7E}, // 30
    {0x1F, 0x14, 0x27, 0x3F, 0x33, 0x95, 0x3B, 0x64, 0xF6, 0x5F, 0x34, 0x2E, 0xA7, 0xDB, 0x03, 0x10}, // 31
    {0x20, 0xA8, 0xED, 0x9C, 0x45, 0xC1, 0x6A, 0xF1, 0x61, 0x9B, 0x14, 0x1E, 0x58, 0xD8, 0xA7, 0x5E}  // 32
};

#endif // _KUZNECHIK_CONST_H_