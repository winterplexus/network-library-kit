/*
**  @(#)url.h
**
**  libnetwork - HTTP URL functions
**  -------------------------------
**
**  copyright 2001-2024 Code Construct Systems (CCS)
*/
#ifndef __URL_H
#define __URL_H

/*
** Define allocate URL encode or decode buffer
*/
#ifndef ALLOCATE_URL_ENCODE_DECODE_BUFFER
#define ALLOCATE_URL_ENCODE_DECODE_BUFFER(s) (string_c_t)malloc(strlen(s) * 3 + 1)
#else
#error  ALLOCATE_URL_ENCODE_DECODE_BUFFER is defined in another include file
#endif

/*
** Function prototypes
*/
extern int URLEncode(string_c_t, string_c_t);
extern int URLDecode(string_c_t, string_c_t);

#endif /* __URL_H */