/*********************************************************************
Homework 5
CS 110: Computer Architecture, Spring 2021
ShanghaiTech University

* Last Modified: 03/28/2021
* Copyright Notice: This file is dervived from work of Brad Conte at
  https://github.com/B-Con/crypto-algorithms/
*********************************************************************/

/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the SHA-256 hashing algorithm.
              SHA-256 is one of the three algorithms in the SHA2
              specification. The others, SHA-384 and SHA-512, are not
              offered in this implementation.
              Algorithm specification can be found here:
               * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
              This implementation uses little endian byte order.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include "sha256.h"
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <emmintrin.h> /* header file for the SSE intrinsics */
/****************************** MACROS ******************************/
// #define ROTLEFT(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define ROTLEFT(a, b) (_mm_or_si128(_mm_slli_epi32(a, b), _mm_srli_epi32(a, 32 - b)))
// #define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
#define ROTRIGHT(a, b) (_mm_or_si128(_mm_srli_epi32(a, b), _mm_slli_epi32(a, 32 - b)))
#define _mm_not_si128(x) (_mm_xor_si128(_mm_set1_epi32(0xffffffff), x))
// #define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define CH(x, y, z) (_mm_xor_si128(_mm_and_si128(x, y), _mm_and_si128(_mm_not_si128(x), z)))
//#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define MAJ(x, y, z) (_mm_xor_si128(_mm_xor_si128(_mm_and_si128(x, y), _mm_and_si128(x, z)), _mm_and_si128(y, z)))
//.#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP0(x) (_mm_xor_si128(_mm_xor_si128(ROTRIGHT(x, 2), ROTRIGHT(x, 13)), ROTRIGHT(x, 22)))
//#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define EP1(x) (_mm_xor_si128(_mm_xor_si128(ROTRIGHT(x, 6), ROTRIGHT(x, 11)), ROTRIGHT(x, 25)))
// #define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG0(x) (_mm_xor_si128(_mm_xor_si128(ROTRIGHT(x, 7), ROTRIGHT(x, 18)), _mm_srli_epi32(x, 3)))
//#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))
#define SIG1(x) (_mm_xor_si128(_mm_xor_si128(ROTRIGHT(x, 17), ROTRIGHT(x, 19)), _mm_srli_epi32(x, 10)))
// TODO: check above

#define f_add(a, b) (_mm_add_epi32(a, b)) // guess what f means
#define fu_add(a, b) (a = _mm_add_epi32(a, b))
/**************************** VARIABLES *****************************/
static const WORD k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
static __m128i Km[64];
/*********************** FUNCTION DEFINITIONS ***********************/
__m128i c[8];
BYTE datacache[64];



#include <stdint.h>
#include <string.h>

void fuck(__m128i var)
{
    uint16_t val[8];
    memcpy(val, &var, sizeof(val));

    printf("Numerical: %i %i %i %i %i %i %i %i \n", 
           val[0], val[1], val[2], val[3], val[4], val[5], 
           val[6], val[7]);
}


void print128_num(__m128i var)
{
    // uint16_t val[8];
    // memcpy(val, &var, sizeof(val));
    // printf("Numerical: %i %i %i %i %i %i %i %i \n", 
    //        val[0], val[1], val[2], val[3], val[4], val[5], 
    //        val[6], val[7]);
    int32_t  *p = (int *) &var;
    //cout<<p[0]<<endl;

    printf("%u ", p[3]);

}
void sha256_transform(SHA256_CTX *ctx, const BYTE data[])
{
  __m128i a, b, c, d, e, f, g, h, t1, t2, m[64];
  short i, j;
  for (i = 0, j = 0; i < 16; ++i, j += 4)
    m[i] = _mm_set1_epi32((data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) |
           (data[j + 3]));
#ifdef DEBUG
  printf("Remove me: m[i] \n");
#endif

  for (; i < 64; ++i)
    m[i] = f_add(f_add(f_add(SIG1(m[i - 2]), m[i - 7]), SIG0(m[i - 15])), m[i - 16]);
#ifdef DEBUG
  for (int i=0; i<=63 ; ++i)
    print128_num(m[i]);
  printf("\n");
  #endif
  a = ctx->state[0];
  b = ctx->state[1];
  c = ctx->state[2];
  d = ctx->state[3];
  e = ctx->state[4];
  f = ctx->state[5];
  g = ctx->state[6];
  h = ctx->state[7];
  #ifdef DEBUG
printf("Remove me 1 \n");
#endif
  for (i = 0; i < 64; ++i)
  {
    t1 = f_add(f_add(f_add(f_add(h, EP1(e)), CH(e, f, g)), Km[i]), m[i]);
    
    t2 = f_add(EP0(a) , MAJ(a, b, c));
    //print128_num(t2);
    h = g;
    g = f;
    f = e;
    e = f_add(d, t1);

    d = c;
    c = b;
    b = a;
    a = f_add(t1, t2);
    
  }

  fu_add(ctx->state[0], a);
  fu_add(ctx->state[1], b);
  fu_add(ctx->state[2], c);
  fu_add(ctx->state[3], d);
  fu_add(ctx->state[4], e);
  fu_add(ctx->state[5], f);
  fu_add(ctx->state[6], g);
  fu_add(ctx->state[7], h);
 #ifdef DEBUG
  printf("Remove me: Line 119 \n");

  for (int i=0; i<=7 ; ++i)
    print128_num(ctx->state[i]);
  printf("\n");
    #endif
}

void sha256_init(SHA256_CTX *ctx)
{
  ctx->datalen = 0;
  ctx->bitlen = 0;
  ctx->state[0] = _mm_set1_epi32(0x6a09e667);
  ctx->state[1] = _mm_set1_epi32(0xbb67ae85);
  ctx->state[2] = _mm_set1_epi32(0x3c6ef372);
  ctx->state[3] = _mm_set1_epi32(0xa54ff53a);
  ctx->state[4] = _mm_set1_epi32(0x510e527f);
  ctx->state[5] = _mm_set1_epi32(0x9b05688c);
  ctx->state[6] = _mm_set1_epi32(0x1f83d9ab);
  ctx->state[7] = _mm_set1_epi32(0x5be0cd19);
  #ifdef DEBUG
   printf("Remove me: Line 138 \n");
  for (int i=0; i<=7 ; ++i)
    print128_num(ctx->state[i]);
  printf("\n");
  #endif
  for (int i = 0; i < 64; Km[i] = _mm_set1_epi32(k[i]), ++i)
    ;
}


void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len)
{
  WORD i, j,k;
  int flag = 0;
  for (k=0; k<64; k++){
    if (data[k] != datacache[k])
      {
        flag = 1;
        break;
      }
  }
  if (flag)
  {
    for (i = 0; i < len; ++i)
    {
      ctx->data[ctx->datalen] = data[i];
      ctx->datalen++;
      if (ctx->datalen == 64)
      {
        sha256_transform(ctx, ctx->data);
        // printf("\n Remove me: sha256_update , i= %u , bitlen: %lu, datalen: %u \n", i, ctx->bitlen, ctx->datalen);
        // for (int i = 0; i <= 7; ++i)
        //   printf("%u ", ctx->state[i]);
        // printf("\n");
        ctx->bitlen += 512;
        ctx->datalen = 0;
        if (i == 255)
        {
          for (j = 0; j < 8; ++j)
            c[j] = ctx->state[j];
          memcpy(datacache, data, sizeof(datacache));
        }
      }
    }
    // printf("\n Remove me: sha256_update end, i= %u , bitlen: %lu, datalen: %u \n", i, ctx->bitlen, ctx->datalen);
    // for (int i = 0; i <= 7; ++i)
    //   printf("%u ", ctx->state[i]);
    // printf("\n");
  }
  else
  {
    // printf("\nSecond\n");
      for (i = 0; i < 8; ++i)
      ctx->state[i] = c[i];
    for (i = 256; i < len; ++i)
    {
      ctx->data[ctx->datalen] = data[i];
      ctx->datalen++;
    }
    ctx -> bitlen = 2048;
    // printf("\n Remove me: sha256_update end, i= %u , bitlen: %lu, datalen: %u \n", i, ctx->bitlen, ctx->datalen);
    // for (int i = 0; i <= 7; ++i)
    //   printf("%u ", ctx->state[i]);
    // printf("\n");
  }
}

void sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
  WORD i;
  WORD res[8][4];
  // TODO: fix  error: ‘res’ is used uninitialized [-Werror=uninitialized]
  memset(res, 0, sizeof(res));
  i = ctx->datalen;

  /* Pad whatever data is left in the buffer. */
  if (ctx->datalen < 56)
  {
    ctx->data[i++] = 0x80;
    while (i < 56)
      ctx->data[i++] = 0x00;
  }
  else
  {
    ctx->data[i++] = 0x80;
    while (i < 64)
      ctx->data[i++] = 0x00;
    sha256_transform(ctx, ctx->data);
    memset(ctx->data, 0, 56);
  }

  /* Append to the padding the total message's length in bits and transform. */
  ctx->bitlen += ctx->datalen * 8;
  ctx->data[63] = ctx->bitlen;
  ctx->data[62] = ctx->bitlen >> 8;
  ctx->data[61] = ctx->bitlen >> 16;
  ctx->data[60] = ctx->bitlen >> 24;
  ctx->data[59] = ctx->bitlen >> 32;
  ctx->data[58] = ctx->bitlen >> 40;
  ctx->data[57] = ctx->bitlen >> 48;
  ctx->data[56] = ctx->bitlen >> 56;
  sha256_transform(ctx, ctx->data);

  /* Since this implementation uses little endian byte ordering and SHA uses big
     endian, reverse all the bytes when copying the final state to the output
     hash. */
  
  _mm_storeu_si128((__m128i *)res[0], ctx->state[0]);
  _mm_storeu_si128((__m128i *)res[1], ctx->state[1]);
  _mm_storeu_si128((__m128i *)res[2], ctx->state[2]);
  _mm_storeu_si128((__m128i *)res[3], ctx->state[3]);
  _mm_storeu_si128((__m128i *)res[4], ctx->state[4]);
  _mm_storeu_si128((__m128i *)res[5], ctx->state[5]);
  _mm_storeu_si128((__m128i *)res[6], ctx->state[6]);
  _mm_storeu_si128((__m128i *)res[7], ctx->state[7]);
  #ifdef DEBUG
  printf("Remove me: Line 238 \n");
  for (int i=0; i<=7 ; ++i)
    print128_num(ctx->state[i]);
  printf("\n");
    for (int i=0; i<=7 ; ++i)
      printf("%u ", res[i][0]);
  printf("\n");
  #endif
  for (i = 0; i < 4; ++i)
  {
    hash[i] = ((res[0][0])>> (24 - i * 8)) & 0x000000ff;
    hash[i + 4] =( (res[1][0]) >> (24 - i * 8)) & 0x000000ff;
    hash[i + 8] = ((res[2][0]) >> (24 - i * 8)) & 0x000000ff;
    hash[i + 12] = ((res[3][0])>> (24 - i * 8)) & 0x000000ff;
    hash[i + 16] = ((res[4][0]) >> (24 - i * 8)) & 0x000000ff;
    hash[i + 20] =( (res[5][0]) >> (24 - i * 8)) & 0x000000ff;
    hash[i + 24] =( (res[6][0]) >> (24 - i * 8)) & 0x000000ff;
    hash[i + 28] =( (res[7][0]) >> (24 - i * 8)) & 0x000000ff;
  }
#ifdef DEBUG
    printf("Remove me: hash \n");
  for(i = 0; i< 32; ++i)  
    printf(" %d", hash[i]);
  printf("\n");
  #endif
}
