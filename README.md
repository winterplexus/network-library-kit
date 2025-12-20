Network Library Kit
===================
Network library kit based on C language for TCP/IP4 sockets and HTTP client/server applications.

Library includes the following components:

* TCP/IP4 socket functions
* HTTP request structures
* HTTP functions
* Utility tools

## TCP/IP4 Socket Functions

```
extern SOCKET_DESCRIPTOR ServerConnect(const string_c_t, const int);
extern int ServerSendRequest(SOCKET_DESCRIPTOR, const string_c_t, const string_c_t);
extern int ServerReceiveResponse(SOCKET_DESCRIPTOR, string_c_t, int);
extern int ServerGetHostAddress(string_c_t, string_c_t);
extern int ServerDisconnect(SOCKET_DESCRIPTOR);
extern int GetSocketOption(SOCKET_DESCRIPTOR, int, int, void *, int *);
extern int SetSocketOption(SOCKET_DESCRIPTOR, int, int, const void *, int);
extern int GetHostIPAddress(const string_c_t, string_c_t, size_t);
extern int GetHostName(const string_c_t, string_c_t, size_t);
```

## HTTP Request Structures

```
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

typedef enum HTTPRequestType {
        HTTP_REQ_TYPE_GET = 1,
        HTTP_REQ_TYPE_POST
} HTTP_REQUEST_TYPE;
```

## HTTP Functions

```
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
```

## Utility Tools

| Components  | Description |
| :-----------|:-------------------------------------------------------------------------------------|
| gethostaddr | Get IP4 address of a DNS host |
| gethostname | Get DNS host of a IP4 address |
| gethttp  | Get HTTP response with optional output response file (TLS protocol is not supported) |
| geturl | Get URL (encoded or decoded) per RFC 3986 specification |

### Utility Tool: gethostaddr

```
usage: gethostaddr (options)

options: -h <hostname>
         -v print version information and exit
         -? print this usage
```

### Utility Tool: gethostname

```
usage: gethostname (options)

options: -a <IP4 address>
         -v print version information and exit
         -? print this usage
```

### Utility Tool: gethttp

```
usage: gethttp (options)

options: -h <hostname>
         -p <port number>
         -r <request parameters>
         -o <response file path>
         -m <[get|post]>
         -t <timeout in seconds>
         -l <log file name>
         -f <flags>
         -d enable debug
         -v print version information and exit
         -? print this usage
```

### Utility Tool: geturl

```
usage: geturl (options)

options: -e <URL to encode>
         -d <URL to decode>
         -v print version information and exit
         -? print this usage
```