/*********************************************************************
Homework 5
CS 110: Computer Architecture, Spring 2021
ShanghaiTech University

* Last Modified: 03/28/2021
*********************************************************************/

#include "blockchain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void blockchain_node_init(blk_t *node, uint32_t index, uint32_t timestamp,
                          unsigned char prev_hash[32], unsigned char *data,
                          size_t data_size) {
  if (!node || !data || !prev_hash)
    return;

  node->header.index = index;
  node->header.timestamp = timestamp;
  node->header.nonce = -1;

  memset(node->header.data, 0, sizeof(unsigned char) * 256);
  memcpy(node->header.prev_hash, prev_hash, HASH_BLOCK_SIZE);
  memcpy(node->header.data, data,
         sizeof(unsigned char) * ((data_size < 256) ? data_size : 256));
}

void blockchain_node_hash(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE],
                          hash_func func) {
  if (node)
    func((unsigned char *)node, sizeof(blkh_t), (unsigned char *)hash_buf);
}

BOOL blockchain_node_verify(blk_t *node, blk_t *prev_node, hash_func func) {
  unsigned char hash_buf[HASH_BLOCK_SIZE];

  if (!node || !prev_node)
    return False;

  blockchain_node_hash(node, hash_buf, func);
  if (memcmp(node->hash, hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE))
    return False;

  blockchain_node_hash(prev_node, hash_buf, func);
  if (memcmp(node->header.prev_hash, hash_buf,
             sizeof(unsigned char) * HASH_BLOCK_SIZE))
    return False;

  return True;
}

/* The sequiental implementation of mining implemented for you. */
void blockchain_node_mine(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE],
                          size_t diff, hash_func func) {
  unsigned char one_diff[HASH_BLOCK_SIZE];
  size_t diff_q, diff_m;
  diff_q = diff / 8;
  diff_m = diff % 8;
  memset(one_diff, 0xFF, sizeof(unsigned char) * HASH_BLOCK_SIZE);
  memset(one_diff, 0, sizeof(unsigned char) * diff_q);
  one_diff[diff_q] = ((uint8_t)0xFF) >> diff_m;

  while (True) {
    printf("%s\n", hash_buf);
    blockchain_node_hash(node, hash_buf, func);
    if ((!memcmp(hash_buf, one_diff, sizeof(unsigned char) * diff_q)) &&
        memcmp(&hash_buf[diff_q], &one_diff[diff_q],
               sizeof(unsigned char) * (HASH_BLOCK_SIZE - diff_q)) <= 0) {

      memcpy(node->hash, hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE);
      break;
    }
    node->header.nonce++;
  }
}
