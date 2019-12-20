/*
**  @(#)httputil.h
**
**  libnetwork - HTTP networking utility functions
**  ----------------------------------------------
**
**  copyright 2001-2020 Code Construct Systems (CCS)
*/
#ifndef __HTTPUTIL_H
#define __HTTPUTIL_H

/*
** Define minimum request buffer size
*/
#ifndef _MIN_REQUEST_SIZE
#define _MIN_REQUEST_SIZE 256
#else
#error  _MIN_REQUEST_SIZE is defined in another include file
#endif

/*
** Define maximum request size
*/
#ifndef _MAX_REQUEST_SIZE
#define _MAX_REQUEST_SIZE 5
#else
#error  _MAX_REQUEST_SIZE is defined in another include file
#endif

/*
** Define minimum HTTP URL encode buffer size macro based on given URL size
*/
#ifndef MIN_URL_ENCODE_SIZE
#define MIN_URL_ENCODE_SIZE(_url_size) ((_url_size  * 3) + 1)
#else
#error  MIN_URL_ENCODE_SIZE is defined in another include file
#endif

/*
** Define HTTP request type
*/
typedef enum HTTPRequestType {
        HTTP_REQ_TYPE_GET = 1,
        HTTP_REQ_TYPE_POST
} HTTP_REQUEST_TYPE;

/*
** Function prototypes
*/
extern int HTTPSetRequestType(HTTP_SERVER_ACTION_REQUEST *, HTTP_REQUEST_TYPE);
extern int HTTPSetRequest(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, const int);
extern int HTTPSetRequestParameterSeparator(string_c_t, const int);
extern int HTTPSetVersionHeader(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, const int);

#endif /* __HTTPUTIL_H */