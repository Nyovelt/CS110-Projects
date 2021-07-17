/*********************************************************************
Homework 5
CS 110: Computer Architecture, Spring 2021
ShanghaiTech University

* Last Modified: 03/28/2021
*********************************************************************/


#define _GNU_SOURCE
#include "blockchain.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>
#include<sched.h>
#include<ctype.h>
#define THREAD 20
// #define vCPU 20
short success = 0;


struct _blk_nod_hash {
    unsigned char hash_buf[HASH_BLOCK_SIZE];
    blk_t *node; 
    hash_func *func;
    size_t diff_q;
    blk_t *real_node;  
    unsigned char one_diff[HASH_BLOCK_SIZE];  
    unsigned char * real_hash_buff;
};

typedef struct  _blk_nod_hash  blk_nod_hash; 

void blockchain_node_init(blk_t *node, uint32_t index, uint32_t timestamp, unsigned char prev_hash[32], unsigned char *data,
                          size_t data_size) {
    if (!node || !data || !prev_hash)
        return;

    node->header.index = index;
    node->header.timestamp = timestamp;
    node->header.nonce = -1;

    memset(node->header.data, 0, sizeof(unsigned char) * 256);
    memcpy(node->header.prev_hash, prev_hash, HASH_BLOCK_SIZE);
    memcpy(node->header.data, data, sizeof(unsigned char) * ((data_size < 256) ? data_size : 256));
}

void blockchain_node_hash(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE], hash_func func) {
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
    if (memcmp(node->header.prev_hash, hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE))
        return False;

    return True;
}



void *ith_hlk_nod_hash(void *arg) {

    blk_nod_hash *p_arg = (blk_nod_hash *)arg;
    #pragma GCC ivdep
    while (__builtin_expect((!success), 1)) {
        blockchain_node_hash(p_arg->node, p_arg->hash_buf, p_arg->func);
        if (__builtin_expect(((!memcmp(p_arg->hash_buf, p_arg->one_diff, sizeof(unsigned char) * p_arg->diff_q)) &&
            memcmp(&p_arg->hash_buf[p_arg->diff_q], &p_arg->one_diff[p_arg->diff_q],
                   sizeof(unsigned char) * (HASH_BLOCK_SIZE - p_arg->diff_q)) <= 0),0)) {
            //memcpy(p_arg->node->hash, p_arg->hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE);  
            p_arg->real_node->header.nonce = p_arg->node->header.nonce;
            //memcpy(p_arg->real_node->hash, p_arg->node->hash, sizeof(unsigned char) * HASH_BLOCK_SIZE);
            memcpy(p_arg->real_node->hash, p_arg->hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE);
            memcpy(p_arg->real_hash_buff, p_arg->hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE);
            success  = 1;
            break;
        }
        p_arg->node->header.nonce+=THREAD;
    }
    // p_arg->real_node->header.nonce = p_arg->node->header.nonce;
    // memcpy(p_arg->real_node->hash, p_arg->node->hash, sizeof(unsigned char) * HASH_BLOCK_SIZE);
    return NULL;
}

/* The sequiental implementation of mining implemented for you. */
void blockchain_node_mine(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE], size_t diff, hash_func func) {
    pthread_t p[THREAD];
    //pthread_attr_t attr[THREAD];
    blk_nod_hash thread_args[THREAD];
    blk_t blk_node[THREAD];
    unsigned char one_diff[HASH_BLOCK_SIZE];
    size_t diff_q, diff_m;
    int vCPU = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t cpu_info;
    success = 0;
    diff_q = diff / 8;
    diff_m = diff % 8;
    memset(one_diff, 0xFF, sizeof(unsigned char) * HASH_BLOCK_SIZE);
    memset(one_diff, 0, sizeof(unsigned char) * diff_q);
    one_diff[diff_q] = ((uint8_t)0xFF) >> diff_m;





    // copy first node
    blk_node[0].header.index = node->header.index;
    blk_node[0].header.timestamp = node->header.timestamp;
    blk_node[0].header.nonce = node->header.nonce;
    memcpy(blk_node[0].hash, node->hash, sizeof(unsigned char) * HASH_BLOCK_SIZE);
    memset(blk_node[0].header.data, 0,sizeof(unsigned char) * 256);
    memcpy(blk_node[0].header.prev_hash, node->header.prev_hash, HASH_BLOCK_SIZE);
    memcpy(blk_node[0].header.data, node->header.data, sizeof(unsigned char) * 256);
    // prepare first thread
    thread_args[0].node = &blk_node[0];
    thread_args[0].func = func;
    thread_args[0].diff_q = diff_q;
    thread_args[0].real_node = node; 
    thread_args[0].real_hash_buff = hash_buf;
    memcpy(thread_args[0].one_diff, one_diff, sizeof(unsigned char) * HASH_BLOCK_SIZE);


    for (short i = 0; i <THREAD; i++){
        if (i > 0){
            blk_node[i] = blk_node[i-1];
            blk_node[i].header.nonce +=1;
            thread_args[i] = thread_args[i-1];
            thread_args[i].node = &blk_node[i];
        }

    // set CPU 
    // CPU_ZERO(&(cpuset[i]));
    // CPU_SET(i, &(cpuset[i]));

    CPU_ZERO(&cpu_info);
    CPU_SET(i % vCPU, &cpu_info);

    //pthread_setaffinity_np(p[i], sizeof(cpu_set_t), &(cpuset[i]));
    // run first node
    printf("running thread %d\n", i);
    pthread_create(&p[i], NULL, ith_hlk_nod_hash, (void*)&thread_args[i]);
    pthread_setaffinity_np(p[i], sizeof(cpu_set_t), &cpu_info);

    }
    
    for (short i = 0; i <THREAD; i++)
        pthread_join(p[i], NULL);

    return;
}
