/*
* Taken from the Zephyr project:
* Copyright (c) 2015-2016, Intel Corporation.
*
* SPDX-License-Identifier: Apache-2.0
*/

#ifndef REGMAP_BYTEORDER_H
#define REGMAP_BYTEORDER_H
#include <stdint.h>

/* Internal helpers only used by the sys_* APIs further below */
#define __bswap_16(x) ((uint16_t)((((x) >> 8) & 0xff) | (((x)&0xff) << 8)))
#define __bswap_24(x) ((uint32_t)((((x) >> 16) & 0xff) | \
                                  (((x)) & 0xff00) |     \
                                  (((x)&0xff) << 16)))
#define __bswap_32(x) ((uint32_t)((((x) >> 24) & 0xff) |  \
                                  (((x) >> 8) & 0xff00) | \
                                  (((x)&0xff00) << 8) |   \
                                  (((x)&0xff) << 24)))
#define __bswap_48(x) ((uint64_t)((((x) >> 40) & 0xff) |    \
                                  (((x) >> 24) & 0xff00) |  \
                                  (((x) >> 8) & 0xff0000) | \
                                  (((x)&0xff0000) << 8) |   \
                                  (((x)&0xff00) << 24) |    \
                                  (((x)&0xff) << 40)))
#define __bswap_64(x) ((uint64_t)((((x) >> 56) & 0xff) |      \
                                  (((x) >> 40) & 0xff00) |    \
                                  (((x) >> 24) & 0xff0000) |  \
                                  (((x) >> 8) & 0xff000000) | \
                                  (((x)&0xff000000) << 8) |   \
                                  (((x)&0xff0000) << 24) |    \
                                  (((x)&0xff00) << 40) |      \
                                  (((x)&0xff) << 56)))

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define sys_le16_to_cpu(val) (val)
#define sys_cpu_to_le16(val) (val)
#define sys_le24_to_cpu(val) (val)
#define sys_cpu_to_le24(val) (val)
#define sys_le32_to_cpu(val) (val)
#define sys_cpu_to_le32(val) (val)
#define sys_le48_to_cpu(val) (val)
#define sys_cpu_to_le48(val) (val)
#define sys_le64_to_cpu(val) (val)
#define sys_cpu_to_le64(val) (val)
#define sys_be16_to_cpu(val) __bswap_16(val)
#define sys_cpu_to_be16(val) __bswap_16(val)
#define sys_be24_to_cpu(val) __bswap_24(val)
#define sys_cpu_to_be24(val) __bswap_24(val)
#define sys_be32_to_cpu(val) __bswap_32(val)
#define sys_cpu_to_be32(val) __bswap_32(val)
#define sys_be48_to_cpu(val) __bswap_48(val)
#define sys_cpu_to_be48(val) __bswap_48(val)
#define sys_be64_to_cpu(val) __bswap_64(val)
#define sys_cpu_to_be64(val) __bswap_64(val)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define sys_le16_to_cpu(val) __bswap_16(val)
#define sys_cpu_to_le16(val) __bswap_16(val)
#define sys_le24_to_cpu(val) __bswap_24(val)
#define sys_cpu_to_le24(val) __bswap_24(val)
#define sys_le32_to_cpu(val) __bswap_32(val)
#define sys_cpu_to_le32(val) __bswap_32(val)
#define sys_le48_to_cpu(val) __bswap_48(val)
#define sys_cpu_to_le48(val) __bswap_48(val)
#define sys_le64_to_cpu(val) __bswap_64(val)
#define sys_cpu_to_le64(val) __bswap_64(val)
#define sys_be16_to_cpu(val) (val)
#define sys_cpu_to_be16(val) (val)
#define sys_be24_to_cpu(val) (val)
#define sys_cpu_to_be24(val) (val)
#define sys_be32_to_cpu(val) (val)
#define sys_cpu_to_be32(val) (val)
#define sys_be48_to_cpu(val) (val)
#define sys_cpu_to_be48(val) (val)
#define sys_be64_to_cpu(val) (val)
#define sys_cpu_to_be64(val) (val)
#else
#error "Unknown byte order"
#endif

static inline void sys_put_be16(uint16_t val, uint8_t dst[2])
{
    dst[0] = val >> 8;
    dst[1] = val;
}

static inline void sys_put_be24(uint32_t val, uint8_t dst[3])
{
    dst[0] = val >> 16;
    sys_put_be16(val, &dst[1]);
}

static inline void sys_put_be32(uint32_t val, uint8_t dst[4])
{
    sys_put_be16(val >> 16, dst);
    sys_put_be16(val, &dst[2]);
}

static inline void sys_put_be48(uint64_t val, uint8_t dst[6])
{
    sys_put_be16(val >> 32, dst);
    sys_put_be32(val, &dst[2]);
}

static inline void sys_put_be64(uint64_t val, uint8_t dst[8])
{
    sys_put_be32(val >> 32, dst);
    sys_put_be32(val, &dst[4]);
}

static inline void sys_put_le16(uint16_t val, uint8_t dst[2])
{
    dst[0] = val;
    dst[1] = val >> 8;
}

static inline void sys_put_le24(uint32_t val, uint8_t dst[3])
{
    sys_put_le16(val, dst);
    dst[2] = val >> 16;
}

static inline void sys_put_le32(uint32_t val, uint8_t dst[4])
{
    sys_put_le16(val, dst);
    sys_put_le16(val >> 16, &dst[2]);
}

static inline void sys_put_le48(uint64_t val, uint8_t dst[6])
{
    sys_put_le32(val, dst);
    sys_put_le16(val >> 32, &dst[4]);
}

static inline void sys_put_le64(uint64_t val, uint8_t dst[8])
{
    sys_put_le32(val, dst);
    sys_put_le32(val >> 32, &dst[4]);
}

static inline uint16_t sys_get_be16(const uint8_t src[2])
{
    return ((uint16_t)src[0] << 8) | src[1];
}

static inline uint32_t sys_get_be24(const uint8_t src[3])
{
    return ((uint32_t)src[0] << 16) | sys_get_be16(&src[1]);
}

static inline uint32_t sys_get_be32(const uint8_t src[4])
{
    return ((uint32_t)sys_get_be16(&src[0]) << 16) | sys_get_be16(&src[2]);
}

static inline uint64_t sys_get_be48(const uint8_t src[6])
{
    return ((uint64_t)sys_get_be32(&src[0]) << 16) | sys_get_be16(&src[4]);
}

static inline uint64_t sys_get_be64(const uint8_t src[8])
{
    return ((uint64_t)sys_get_be32(&src[0]) << 32) | sys_get_be32(&src[4]);
}

static inline uint16_t sys_get_le16(const uint8_t src[2])
{
    return ((uint16_t)src[1] << 8) | src[0];
}

static inline uint32_t sys_get_le24(const uint8_t src[3])
{
    return ((uint32_t)src[2] << 16) | sys_get_le16(&src[0]);
}

static inline uint32_t sys_get_le32(const uint8_t src[4])
{
    return ((uint32_t)sys_get_le16(&src[2]) << 16) | sys_get_le16(&src[0]);
}

static inline uint64_t sys_get_le48(const uint8_t src[6])
{
    return ((uint64_t)sys_get_le32(&src[2]) << 16) | sys_get_le16(&src[0]);
}

static inline uint64_t sys_get_le64(const uint8_t src[8])
{
    return ((uint64_t)sys_get_le32(&src[4]) << 32) | sys_get_le32(&src[0]);
}

#endif