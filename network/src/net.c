/*
**  @(#)net.c
**
**  libnetwork - TCP/IP4 network interface functions
**  -----------------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Connect to TCP/IP4 server
*/
SOCKET_DESCRIPTOR ServerConnect(const string_c_t host_name, const int port) {
    char service[16];
    struct addrinfo hints;
    struct addrinfo *results, *r;
    SOCKET_DESCRIPTOR sock;
    bool_c_t connected = FALSE;

    /*
    ** Format service using port number
    */
    strfmt_p(service, sizeof(service), (const string_c_t)"%d", port);

    /*
    ** Set hints structure with stream socket TCP parameters
    */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_TCP;

    /*
    ** Get address information about TCP/IP4 server host using service and hints structure
    */
    if (getaddrinfo(host_name, service, &hints, &results) != 0) {
        LogFilePrint((string_c_t)"error-> unable to get IP4 address information for server host name (%s:%d) [%s line: %d]\n", host_name, __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Process each result until connected to the TCP/IP4 server host
    */
    for (r = results; r != NULL; r = r->ai_next) {
        /*
        ** Create stream socket using TCP
        */
        if ((sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol)) == -1) {
            continue;
        }

        /*
        ** Establish connection to TCP/IP4 server using socket handle
        */
        if (connect(sock, r->ai_addr, (int)r->ai_addrlen) != -1) {
            connected = TRUE;
            break;
        }

        /*
        ** Close socket (connection to TCP/IP4 server host failed for this address)
        */
        SOCKET_CLOSE(sock);
    }

    /*
    ** Exit if not connected to TCP/IP4 server host
    */
    if (!connected) {
        LogFilePrint((string_c_t)"error-> unable to connect to server host (%s) [%s line: %d]\n", host_name, __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Free results
    */
    freeaddrinfo(results);

    /*
    ** Return socket handle
    */
    return (sock);
}

/*
** Send request to TCP/IP4 server
*/
int ServerSendRequest(SOCKET_DESCRIPTOR sock, const string_c_t req, const string_c_t host_name) {
    int count = 0;

    /*
    ** Is send request valid?
    */
    if (!req) {
        return (-1);
    }

    /*
    ** Send request buffer to TCP/IP4 server
    */
    count = (int)strlen(req);
    if (send(sock, req, count, 0) == count) {
        return (0);
    }
    else {
        LogFilePrint((string_c_t)"error-> unable to send request to server host: (%s) [%s line: %d]\n", host_name, __FILE__, __LINE__);
        return (-2);
    }
}

/*
** Receive response from TCP/IP4 server
*/
int ServerReceiveResponse(SOCKET_DESCRIPTOR sock, string_c_t resp, int size) {
    int count = 0;

    /*
    ** Clear response buffer
    */
    memset(resp, 0, size);

    /*
    ** Receive response data from TCP/IP4 server
    */
    count = recv(sock, resp, size, 0);
    return (count);
}

/*
** Disconnect from TCP/IP4 server
*/
int ServerDisconnect(SOCKET_DESCRIPTOR sock) {
    /*
    ** Close socket
    */
    if (sock) {
        SOCKET_CLOSE(sock);
    }
    return (0);
}

/*
** Get socket option
*/
int GetSocketOption(SOCKET_DESCRIPTOR sock, int level, int option_name, void *option_value, int *option_len) {
    return getsockopt(sock, level, option_name, option_value, (socklen_t *)option_len);
}

/*
** Set socket option
*/
int SetSocketOption(SOCKET_DESCRIPTOR sock, int level, int option_name, const void *option_value, int option_len) {
    return setsockopt(sock, level, option_name, option_value, (socklen_t)option_len);
}

/*
** Get IP4 network address (in dot notation) for a given host name
*/
int GetHostIPAddress(const string_c_t host_name, string_c_t ip_address, size_t ip_address_size) {
    struct addrinfo hints;
    struct addrinfo *results, *r;
    char address[_MAX_IP_ADDRESS_SIZE];

    /*
    ** Is host name valid?
    */
    if (!host_name || !strlen(host_name)) {
        return (-1);
    }

    /*
    ** Set hints structure with socket TCP parameters
    */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    /*
    ** Get IP4 address information for host name using hints structure
    */
    if (getaddrinfo(host_name, NULL, &hints, &results) != 0) {
        LogFilePrint((string_c_t)"error-> unable to get IP4 address information for host name: %s [%s line: %d]\n", host_name, __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Process each result until TCP/IP4 network address is found
    */
    for (r = results; r != NULL; r = r->ai_next) {
        if (getnameinfo(r->ai_addr, (int)r->ai_addrlen, address, sizeof(address), NULL, 0, NI_NUMERICHOST) == 0) {
            break;
        }
    }

    /*
    ** Free results list
    */
    freeaddrinfo(results);

    /*
    ** Return IP4 network address
    */
    strcpy_p(ip_address, ip_address_size, address, sizeof(address));
    return (0);
}

/*
** Get host name for a given TCP/IP4 network address (in dot notation)
*/
int GetHostName(const string_c_t ip_address, string_c_t host_name, size_t host_name_size) {
    struct sockaddr_in sa;
    char host[_MAX_HOST_NAME_SIZE];

    /*
    ** Is IP4 network address valid?
    */
    if (!ip_address || !strlen(ip_address)) {
        return (-1);
    }

    /*
    ** Set socket address structure with socket TCP parameters
    */
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;

    /*
    ** Convert TCP/IP4 network address to binary form in socket address structure
    */
    inet_pton(AF_INET, ip_address, &sa.sin_addr);

    /*
    ** Get host name using socket address structure
    */
    if (getnameinfo((struct sockaddr *) & sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NAMEREQD) != 0) {
        LogFilePrint((string_c_t)"error-> unable to get host name for IP4 address: %s [%s line: %d]\n", ip_address, __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Return host name
    */
    strcpy_p(host_name, host_name_size, host, sizeof(host));
    return (0);
}