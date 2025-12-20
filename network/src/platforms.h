/*
**  @(#platforms.h
**
**  libnetwork - modules
**  --------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#ifndef __PLATFORMS_H
#define __PLATFORMS_H

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

#endif /* __PLATFORMS_H */