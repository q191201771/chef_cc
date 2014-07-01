#ifndef _CHEF_CHUNK_H_
#define _CHEF_CHUNK_H_

#include <inttypes.h>

void serialize_uint32(uint32_t val, char *p/*out*/);
uint32_t parse_uint32(char *p);

#endif

