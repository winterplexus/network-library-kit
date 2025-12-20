/*
**  @(#)network.h
**
**  libnetwork - network interface functions
**  ----------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#ifndef __NETWORK_H
#define __NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/*
** POSIX platform include files
*/
#ifdef _POSIX_ENVIRONMENT
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

/*
** Windows platform include files
*/
#ifdef _WINDOWS_ENVIRONMENT
#include <io.h>
#include <share.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

/*
** Define Windows sockets application startup and cleanup macros
*/
#ifdef _WINDOWS_ENVIRONMENT
#define WIN32_LEAN_AND_MEAN
#ifndef WINDOWS_SOCKETS_STARTUP
#define WINDOWS_SOCKETS_STARTUP \
        static WSADATA wsa_data; \
        int wsa_status = WSAStartup(MAKEWORD(2, 0), &wsa_data); \
        if (wsa_status != 0) { \
            printf("error-> Windows socket function WSAStartup() failed: %d\n", wsa_status); \
        }
#endif
#ifndef WINDOWS_SOCKETS_CLEANUP
#define WINDOWS_SOCKETS_CLEANUP \
        WSACleanup();
#endif
#endif

/*
** Define sockets descriptor
*/
#ifndef SOCKET_DESCRIPTOR
#ifdef _WINDOWS_ENVIRONMENT
#define SOCKET_DESCRIPTOR SOCKET
#else
#define SOCKET_DESCRIPTOR int
#endif
#else
#error SOCKET_DESCRIPTOR is defined in another include file
#endif

/*
** Define sockets startup
*/
#ifndef SOCKETS_STARTUP
#ifdef _WINDOWS_ENVIRONMENT
#define SOCKETS_STARTUP WINDOWS_SOCKETS_STARTUP
#else
#define SOCKETS_STARTUP
#endif
#else
#error SOCKETS_CLEANUP is defined in another include file
#endif

/*
** Define sockets close function
*/
#ifndef SOCKET_CLOSE
#ifdef _WINDOWS_ENVIRONMENT
#define SOCKET_CLOSE closesocket
#else
#define SOCKET_CLOSE close
#endif
#else
#error SOCKETS_CLEANUP is defined in another include file
#endif 

/*
** Define sockets cleanup
*/
#ifndef SOCKETS_CLEANUP
#ifdef _WINDOWS_ENVIRONMENT
#define SOCKETS_CLEANUP WINDOWS_SOCKETS_CLEANUP
#else
#define SOCKETS_CLEANUP
#endif
#else
#error SOCKETS_CLEANUP is defined in another include file
#endif

/*
** Define maximum IP address string size
*/
#ifndef _MAX_IP_ADDRESS_SIZE
#define _MAX_IP_ADDRESS_SIZE 16
#else
#error  _MAX_IP_ADDRESS_SIZE is defined in another include file
#endif

/*
** Define maximum host name string size
*/
#ifndef _MAX_HOST_NAME_SIZE
#define _MAX_HOST_NAME_SIZE 255
#else
#error  _MAX_HOST_NAME_SIZE is defined in another include file
#endif

/*
** Define default timeout period
*/
#ifndef _TIMEOUT_PERIOD
#define _TIMEOUT_PERIOD 10
#else
#error  _TIMEOUT_PERIOD is defined in another include file
#endif

/*
** Check if HTTP methods are defined in another include file
*/
#ifdef  _HTTP_METHOD_GET
#error  _HTTP_METHOD_GET is defined in another include file
#endif
#ifdef  _HTTP_METHOD_HEAD
#error  _HTTP_METHOD_HEAD is defined in another include file
#endif
#ifdef  _HTTP_METHOD_POST
#error  _HTTP_METHOD_POST is defined in another include file
#endif
#ifdef  _HTTP_METHOD_PUT
#error  _HTTP_METHOD_PUT is defined in another include file
#endif
#ifdef  _HTTP_METHOD_DELETE
#error  _HTTP_METHOD_DELETE is defined in another include file
#endif
#ifdef  _HTTP_METHOD_CONNECT
#error  _HTTP_METHOD_CONNECT is defined in another include file
#endif
#ifdef  _HTTP_METHOD_TRACE
#error  _HTTP_METHOD_TRACE is defined in another include file
#endif
#ifdef  _HTTP_METHOD_PATCH
#error  _HTTP_METHOD_PATCH is defined in another include file
#endif

/*
** Define HTTP methods
*/
#define _HTTP_METHOD_GET "GET"
#define _HTTP_METHOD_HEAD "HEAD"
#define _HTTP_METHOD_POST "POST"
#define _HTTP_METHOD_PUT "PUT"
#define _HTTP_METHOD_DELETE "DELETE"
#define _HTTP_METHOD_CONNECT "CONNECT"
#define _HTTP_METHOD_TRACE "TRACE"
#define _HTTP_METHOD_PATCH "PATCH"

/*
** Define allocate URL encode or decode buffer
*/
#ifndef ALLOCATE_URL_ENCODE_DECODE_BUFFER
#define ALLOCATE_URL_ENCODE_DECODE_BUFFER(s) (string_c_t)malloc(strlen(s) * 3 + 1)
#else
#error  ALLOCATE_URL_ENCODE_DECODE_BUFFER is defined in another include file
#endif

/*
** Define HTTP server action request structure and type
*/
typedef struct HTTPServerActionRequest {
        string_c_t host_name;
        int port_number;
        string_c_t request;
        int request_size;
        FILE *response_fp;
        int timeout;
        string_c_t log_file_name;
        int trace;
} HTTP_SERVER_ACTION_REQUEST;

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
extern HTTP_SERVER_ACTION_REQUEST *HTTPAllocateServerActionRequest(HTTP_SERVER_ACTION_REQUEST *);
extern void HTTPDebugPrintServerActionRequest(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPSetHost(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, size_t);
extern int HTTPSetPort(HTTP_SERVER_ACTION_REQUEST *, int);
extern int HTTPSetRequestBuffer(HTTP_SERVER_ACTION_REQUEST *, size_t);
extern int HTTPSetResponseFile(HTTP_SERVER_ACTION_REQUEST *, FILE *);
extern int HTTPSetTimeout(HTTP_SERVER_ACTION_REQUEST *, int);
extern int HTTPSetLogFileName(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, size_t);
extern int HTTPSetTrace(HTTP_SERVER_ACTION_REQUEST *, int);
extern int HTTPPrintWarningMessages(int);
extern int HTTPFreeServerActionRequest(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPFreeHost(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPFreeRequestBuffer(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPFreeResponseFile(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPFreeLogFileName(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPSendServerRequest(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPSendServerRequestNoTimeout(HTTP_SERVER_ACTION_REQUEST *);
extern int HTTPSetRequestType(HTTP_SERVER_ACTION_REQUEST *, HTTP_REQUEST_TYPE);
extern int HTTPSetRequest(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, const size_t);
extern int HTTPSetRequestParameter(string_c_t, const size_t, const string_c_t, const size_t, const string_c_t, const size_t);
extern int HTTPSetRequestParameterSeparator(string_c_t, const size_t);
extern int HTTPSetVersionHeader(HTTP_SERVER_ACTION_REQUEST *, const string_c_t, const size_t);
extern int GetHostIPAddress(const string_c_t, string_c_t, size_t);
extern int GetHostName(const string_c_t, string_c_t, size_t);
extern int URLEncode(string_c_t, string_c_t);
extern int URLDecode(string_c_t, string_c_t);
extern string_c_t GetNetworkLibraryVersionProduct(void);
extern string_c_t GetNetworkLibraryVersionRelease(void);

#endif /* __NETWORK_H */