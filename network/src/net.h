/*
**  @(#)net.h
**
**  libnetwork - TCP/IP network interface functions
**  -----------------------------------------------
**
**  copyright 2001-2024 Code Construct Systems (CCS)
*/
#ifndef __NET_H
#define __NET_H

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
** Function prototypes
*/
extern SOCKET_DESCRIPTOR ServerConnect(const string_c_t, const int);
extern int ServerSendRequest(SOCKET_DESCRIPTOR, const string_c_t, const string_c_t);
extern int ServerReceiveResponse(SOCKET_DESCRIPTOR, string_c_t, int);
extern int ServerGetHostAddress(string_c_t, string_c_t);
extern int ServerDisconnect(SOCKET_DESCRIPTOR);
extern int GetSocketOption(SOCKET_DESCRIPTOR, int, int, void *, int *);
extern int SetSocketOption(SOCKET_DESCRIPTOR, int, int, const void *, int);
extern int GetHostIPAddress(const string_c_t, string_c_t, size_t);
extern int GetHostName(const string_c_t, string_c_t, size_t);

#endif /* __NET_H */