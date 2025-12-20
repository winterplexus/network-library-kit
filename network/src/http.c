/*
**  @(#)http.c
**
**  libnetwork - HTTP networking functions
**  --------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Print warning messages flag
*/
static bool_c_t print_warning_messages = FALSE;

/*
** Allocate server action request structure
*/
HTTP_SERVER_ACTION_REQUEST *HTTPAllocateServerActionRequest(HTTP_SERVER_ACTION_REQUEST *hsar) {
    /*
    ** Allocate memory for HTTP server action request structure
    */
    hsar = (HTTP_SERVER_ACTION_REQUEST *)malloc(sizeof(HTTP_SERVER_ACTION_REQUEST));
    if (hsar == NULL) {
        LogFilePrint((string_c_t)"error-> insufficient memory for HTTP server action request structure [%s line: %d]\n", __FILE__, __LINE__);
        return (NULL);
    }

    /*
    ** Set default values to each structure element
    */
    hsar->host_name = NULL;
    hsar->port_number = 80;
    hsar->request = NULL;
    hsar->request_size = 0;
    hsar->response_fp = NULL;
    hsar->timeout = 0;
    hsar->log_file_name = NULL;
    hsar->trace = 0;

    /*
    ** Return HTTP server action request structure
    */
    return (hsar);
}

/*
**  Set server action request host name parameter
*/
int HTTPSetHost(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t host_name, int host_name_size) {
    int allocate_size = host_name_size + 1;

    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is host name valid?
    */
    if (!host_name || !host_name_size) {
        return (-1);
    }

    /*
    ** Allocate memory for host name parameter
    */
    hsar->host_name = (string_c_t)malloc(allocate_size);
    if (hsar->host_name != NULL) {
        memset(hsar->host_name, 0, allocate_size);
    }
    else {
        LogFilePrint((string_c_t)"error-> insufficient memory for host name parameter [%s line: %d]\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Set host parameter and return the host name size
    */
    strcpy_p(hsar->host_name, allocate_size, host_name, host_name_size);
    return (host_name_size);
}

/*
** Set server action request port number parameter
*/
int HTTPSetPort(HTTP_SERVER_ACTION_REQUEST *hsar, int port_number) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is port number valid?
    */
    if (!port_number || port_number > _MAX_NET_SOCKET_SIZE) {
        return (-1);
    }

    /*
    ** Set port number parameter and return the port number
    */
    hsar->port_number = port_number;
    return (port_number);
}

/*
** Set server action request request buffer parameter
*/
int HTTPSetRequestBuffer(HTTP_SERVER_ACTION_REQUEST *hsar, int request_size) {
    int allocate_size = request_size + 1;

    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is request buffer size valid?
    */
    if (!request_size) {
        return (-1);
    }

    /*
    ** Allocate memory for request buffer parameter
    */
    hsar->request = (string_c_t)malloc(allocate_size);
    if (hsar->request != NULL) {
        memset(hsar->request, 0, allocate_size);
    }
    else {
        LogFilePrint((string_c_t)"error-> insufficient memory for request buffer parameter [%s line: %d]\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Set request buffer size parameter and return the request size
    */
    hsar->request_size = request_size;
    return (request_size);
}

/*
** Set response file pointer parameter
*/
int HTTPSetResponseFile(HTTP_SERVER_ACTION_REQUEST *hsar, FILE *fp) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Set response file pointer parameter and return status
    */
    if (fp) {
        hsar->response_fp = fp;
    }

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Set server action request timeout parameter
*/
int HTTPSetTimeout(HTTP_SERVER_ACTION_REQUEST *hsar, int timeout) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is timeout value valid?
    */
    if (!timeout) {
        return (-1);
    }

    /*
    ** Set timeout parameter and return the timeout value
    */
    hsar->timeout = timeout;
    return (timeout);
}

/*
** Set server action request log file name parameter
*/
int HTTPSetLogFileName(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t log_file, int log_file_size) {
    int allocate_size = log_file_size + 1;

    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is log file name valid?
    */
    if (!log_file || !log_file_size) {
        return (-1);
    }

    /*
    ** Allocate memory for log file name parameter
    */
    hsar->log_file_name = (string_c_t)malloc(allocate_size);
    if (hsar->log_file_name != NULL) {
        memset(hsar->log_file_name, 0, allocate_size);
    }
    else {
        LogFilePrint((string_c_t)"error-> insufficient memory for log file name parameter [%s line: %d]\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Set log file name parameter and return the log file size
    */
    strcpy_p(hsar->log_file_name, allocate_size, log_file, log_file_size);
    return (log_file_size);
}

/*
** Set server action request trace flag parameter
*/
int HTTPSetTrace(HTTP_SERVER_ACTION_REQUEST *hsar, int trace) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is trace flag value valid?
    */
    if (!trace) {
        return (-1);
    }

    /*
    ** Set trace flag parameter and return trace flag
    */
    hsar->trace = trace;
    return (trace);
}

/*
** Print warning messages switch
*/
int HTTPPrintWarningMessages(int flag) {
    if (flag == TRUE || flag == FALSE) {
        print_warning_messages = (bool_c_t)flag;
    }

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Free server action request structure
*/
int HTTPFreeServerActionRequest(HTTP_SERVER_ACTION_REQUEST *hsar) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Free memory for server action request
    */
    free(hsar);

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Free server action request host name parameter
*/
int HTTPFreeHost(HTTP_SERVER_ACTION_REQUEST *hsar) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is host name valid?
    */
    if (!hsar->host_name) {
        return (-1);
    }

    /*
    ** Free host name parameter
    */
    free(hsar->host_name);

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Free server action request request buffer parameter
*/
int HTTPFreeRequestBuffer(HTTP_SERVER_ACTION_REQUEST *hsar) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is request buffer valid?
    */
    if (!hsar->request) {
        return (-1);
    }

    /*
    ** Free request buffer parameter and reset request buffer size
    */
    free(hsar->request);

    /*
    ** Reset request buffer size
    */
    hsar->request_size = 0;

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Free response file
*/
int HTTPFreeResponseFile(HTTP_SERVER_ACTION_REQUEST *hsar) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is response file valid?
    */
    if (!hsar->response_fp) {
        return (-1);
    }

    /*
    ** Free response file and reset response file
    */
    fclose_p(hsar->response_fp);
    hsar->response_fp = NULL;

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Free server action request log file name parameter
*/
int HTTPFreeLogFileName(HTTP_SERVER_ACTION_REQUEST *hsar) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is log file name valid?
    */
    if (!hsar->log_file_name) {
        return (-1);
    }

    /*
    ** Free log file name parameter
    */
    free(hsar->log_file_name);

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Send server action request to HTTP server
*/
int HTTPSendServerRequest(HTTP_SERVER_ACTION_REQUEST *hsar) {
    SOCKET_DESCRIPTOR sock;
    string_c_t buffer;
    unsigned int count, total = 0;

    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is response file pointer valid?
    */
    if (!hsar->response_fp) {
        return (-1);
    }

    /*
    ** Set log file directory
    */
    LogFileDirectory(hsar->log_file_name, strlen(hsar->log_file_name));

    /*
    ** Set timeout if no timeout was given
    */
    if (hsar->timeout) {
        hsar->timeout = _TIMEOUT_PERIOD;
    }

    /*
    ** Connect to the HTTP server
    */
    sock = ServerConnect(hsar->host_name, hsar->port_number);
    if (sock < 1) {
        return (-2);
    }

    /*
    ** Trace network request
    */
    if (hsar->trace) {
        LogFilePrint((string_c_t)"trace-> request buffer: %s\n", hsar->request);
    }

    /*
    ** Send request to the HTTP server (exit if send request has failed)
    */
    if (ServerSendRequest(sock, hsar->request, hsar->host_name) != EXIT_SUCCESS) {
        ServerDisconnect(sock);
        return (-2);
    }

    /*
    ** Allocate memory for response buffer
    */
    buffer = (string_c_t)malloc(BUFSIZ + 1);
    if (buffer != NULL) {
        memset(buffer, 0, BUFSIZ + 1);
    }
    else {
        LogFilePrint((string_c_t)"error-> insufficient memory for response buffer [%s line: %d]\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Process each response from the HTTP server
    */
    do  {
        /*
        ** Exit if system call was interrupted
        */
        if (errno == EINTR) {
            ServerDisconnect(sock);
            return (-2);
        }

        /*
        ** Receive response from the HTTP server
        */
        count = ServerReceiveResponse(sock, buffer, BUFSIZ);
        total = total + count;

        /*
        ** Write contents of response buffer to response file
        */
        if (fwrite(buffer, 1, count, hsar->response_fp) != count) {
            if (print_warning_messages == TRUE) {
                LogFilePrint((string_c_t)"error-> unable to write error to response file (error number %d) [%s line: %d]\n", errno, __FILE__, __LINE__);
            }
        }

        /*
        ** Trace network response
        */
        if (hsar->trace) {
            LogFilePrint((string_c_t)"trace-> response buffer: %s\n", buffer);
        }
    } while (count > 0);

    /*
    ** Free response buffer
    */
    free(buffer);

    /*
    ** Disconnect from the HTTP server
    */
    ServerDisconnect(sock);

    /*
    ** Return total count
    */
    return (total);
}

/*
** Send server action request to HTTP server with no timeout
*/
int HTTPSendServerRequestNoTimeout(HTTP_SERVER_ACTION_REQUEST *hsar) {
    SOCKET_DESCRIPTOR sock;
    string_c_t buffer;
    unsigned int count, total = 0;

    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Is response file pointer valid?
    */
    if (!hsar->response_fp) {
        return (-1);
    }

    /*
    ** Set log file directory
    */
    LogFileDirectory(hsar->log_file_name, strlen(hsar->log_file_name));

    /*
    ** Connect to the HTTP server
    */
    sock = ServerConnect(hsar->host_name, hsar->port_number);
    if (sock < 1) {
        return (-2);
    }

    /*
    ** Trace network request
    */
    if (hsar->trace) {
        LogFilePrint((string_c_t)"trace-> request buffer: %s\n", hsar->request);
    }

    /*
    ** Send request to the HTTP server (exit if send request has failed)
    */
    if (ServerSendRequest(sock, hsar->request, hsar->host_name) != EXIT_SUCCESS) {
        ServerDisconnect(sock);
        return (-2);
    }

    /*
    ** Allocate memory for response buffer
    */
    buffer = (string_c_t)malloc(BUFSIZ + 1);
    if (buffer != NULL) {
        memset(buffer, 0, BUFSIZ + 1);
    }
    else {
        LogFilePrint((string_c_t)"error-> insufficient memory for response buffer [%s line: %d]\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Process each response from the HTTP server
    */
    do  {
        /*
        ** Exit if system call was interrupted
        */
        if (errno == EINTR) {
            ServerDisconnect(sock);
            return (-2);
        }

        /*
        ** Receive response from the HTTP server
        */
        count = ServerReceiveResponse(sock, buffer, BUFSIZ);
        total = total + count;

        /*
        ** Write contents of response buffer to response file
        */
        if (fwrite(buffer, 1, count, hsar->response_fp) != count) {
            if (print_warning_messages == TRUE) {
                LogFilePrint((string_c_t)"error-> unable to write error to response file (error number %d) [%s line: %d]\n", errno, __FILE__, __LINE__);
            }
        }

        /*
        ** Trace network response
        */
        if (hsar->trace) {
            LogFilePrint((string_c_t)"trace-> response buffer: %s\n", buffer);
        }
    } while (count > 0);

    /*
    ** Free response buffer
    */
    free(buffer);

    /*
    ** Disconnect from the HTTP server
    */
    ServerDisconnect(sock);

    /*
    ** Return total count
    */
    return (total);
}