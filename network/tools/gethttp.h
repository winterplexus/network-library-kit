/*
**  @(#)gethttp.h
**
**  libnetwork utility - get HTTP response utility
**  ----------------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#ifndef __GETHTTP_H
#define __GETHTTP_H

/*
** Default default parameters
*/
#ifndef _DEF_HOST_PORT
#define _DEF_HOST_PORT 80
#else
#error  _DEF_HOST_PORT is defined in another include file
#endif
#ifndef _DEF_NETWORK_TIMEOUT
#define _DEF_NETWORK_TIMEOUT 5
#else
#error  _DEF_NETWORK_TIMEOUT is defined in another include file
#endif
#ifndef _DEF_LOG_FILE
#define _DEF_LOG_FILE "gethttp"
#else
#error  _DEF_LOG_FILE is defined in another include file
#endif

/*
** Define maximum method string size
*/
#ifndef _MAX_METHOD_SIZE
#define _MAX_METHOD_SIZE 8
#else
#error  _MAX_METHOD_SIZE is defined in another include file
#endif

/*
** Define maximum request string size
*/
#ifndef _MAX_REQUEST_SIZE
#define _MAX_REQUEST_SIZE BUFSIZ
#else
#error  _MAX_REQUEST_SIZE is defined in another include file
#endif

/*
** Mode bit flags
*/
#ifndef _MODE_OUTPUT_ON
#define _MODE_OUTPUT_ON 01
#else
#error  _MODE_OUTPUT_ON is defined in another include file
#endif
#ifndef _MODE_STATISTICS_ON
#define _MODE_STATISTICS_ON 02
#else
#error  _MODE_STATISTICS_ON is defined in another include file
#endif

/*
** Define HTTP parameters structure and type
*/
typedef struct HTTPParameters {
        char hostname[_MAX_HOST_NAME_SIZE + 1];
        int port;
        int timeout;
        char logfile[_MAX_FILE_NAME_SIZE + 1];
        bool_c_t trace;
        char method[_MAX_METHOD_SIZE + 1];
        char request[_MAX_REQUEST_SIZE + 1];
        char responsefile[_MAX_FILE_NAME_SIZE + 1];
        int mode;
} HTTP_PARAMETERS;

/*
** Define HTTP statistics structure and type
*/
typedef struct HTTPStatistics {
        long bytecount;
        long linecount;
} HTTP_STATISTICS;

/*
** Define product version string
*/
#ifndef _GETHTTP_VERSION_PRODUCT
#define _GETHTTP_VERSION_PRODUCT "gethttp"
#else
#error  _GETHTTP_VERSION_PRODUCT is defined in another include file
#endif

#endif /* __GETHTTP_H */   