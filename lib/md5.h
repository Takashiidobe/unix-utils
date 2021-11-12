#ifndef MD5_H
#define MD5_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

typedef struct MD5Result {
  uint32_t h0, h1, h2, h3;
} MD5Result;

MD5Result *md5(uint8_t *initial_msg, size_t initial_len);

void md5_print(const MD5Result *md5_result);

#endif
