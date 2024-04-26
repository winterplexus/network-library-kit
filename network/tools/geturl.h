/*
**  @(#)geturl.h
**
**  libnetwork utility - get URL utility
**  ------------------------------------
**
**  copyright 2001-2024 Code Construct Systems (CCS)
*/
#ifndef __GETURL_H
#define __GETURL_H

/*
** Define maximum URL string size
*/
#ifndef _MAX_URL_SIZE
#define _MAX_URL_SIZE 255
#else
#error  _MAX_URL_SIZE is defined in another include file
#endif

/*
** Define URL operation type
*/
typedef enum {
        URL_ENCODE = 1,
        URL_DECODE
} URL_OPERATION_TYPE;

/*
** Define URL parameters structure and type
*/
typedef struct UrlParameters {
        char url[_MAX_URL_SIZE + 1];
        URL_OPERATION_TYPE operation_type;
} URL_PARAMETERS;

/*
** Define product version string
*/
#ifndef _GETURL_VERSION_PRODUCT
#define _GETURL_VERSION_PRODUCT "geturl"
#else
#error  _GETURL_VERSION_PRODUCT is defined in another include file
#endif

#endif /* __GETURL_H */