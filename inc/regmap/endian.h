#pragma once
/* *nix people have a real version of this header
 * windows people do not */
#ifndef ENDIAN_H
#define ENDIAN_H

/* only the short operations are needed */

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
#define htobe16(x) __builtin_bswap16(x)
#define be16toh(x) __builtin_bswap16(x)
#else 
#ifdef(_WIN32)
#include <winsock.h>
#else
#include <arpa/inet.h>
#define htobe16(x) htons(x)
#define be16toh(x) ntohs(x)
#endif
#endif

#endif