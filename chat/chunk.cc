#include "chunk.h"
#include <arpa/inet.h>
#include <string.h>

void serialize_uint32(uint32_t val, char *p/*out*/)
{
    uint32_t val_nl = htonl(val);
    memcpy(p, (const void *)&val_nl, sizeof (uint32_t));
}

uint32_t parse_uint32(char *p)
{
    return ntohl(*(uint32_t *)p);
}

