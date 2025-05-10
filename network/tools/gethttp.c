/*
**  @(#)gethttp.c
**
**  libnetwork utility - get HTTP response utility
**  ----------------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Local function prototype
*/
static int GetOptions(int, string_c_t[], HTTP_PARAMETERS *);
static int ProcessRequest(HTTP_PARAMETERS *, HTTP_STATISTICS *);
static int ProcessResponseFile(FILE *, HTTP_PARAMETERS *, HTTP_STATISTICS *);
static void SetParameters(HTTP_PARAMETERS *);
static void SetStatistics(HTTP_STATISTICS *);
static void SetFlags(string_c_t, HTTP_PARAMETERS *);
static void InterruptHandler(void);
static void DisplayStatistics(HTTP_PARAMETERS *, HTTP_STATISTICS *);
static void DisplayVersion(void);
static void DisplayUsage(void);

/*
** Get host IP4 address utility
*/
int main(int argc, string_c_t argv[]) {
    HTTP_PARAMETERS hp;
    HTTP_STATISTICS hs;
    int status = 0;

    /*
    ** Sockets startup
    */
    SOCKETS_STARTUP;

    /*
    ** Set signal trap for signal interrupt from the console or OS
    */
    signal(SIGINT, (fptr_c_t)InterruptHandler);

    /*
    ** Set parameters and statistics counters
    */
    SetParameters(&hp);
    SetStatistics(&hs);

    /*
    ** Get command line options and check parameters
    */
    status = GetOptions(argc, argv, &hp);
    if (status == EXIT_FAILURE) {
        return (EXIT_FAILURE);
    }

    /*
    ** Process request
    */
    status = ProcessRequest(&hp, &hs);

    /*
    ** Display statistics and return status
    */
    DisplayStatistics(&hp, &hs);

    /*
    ** Sockets cleanup
    */
    SOCKETS_CLEANUP;

    /*
    ** Return status
    */
    return (status);
}

/*
** Get command line options
*/
static int GetOptions(int argc, string_c_t argv[], HTTP_PARAMETERS *hp) {
    int c;

    /*
    ** Display usage if no command line options
    */
    if (argc < 2) {
        DisplayUsage();
    }

    /*
    ** Process each option on the command line
    */
    while (TRUE) {
        c = getopt(argc, argv, (const string_c_t)"?df:h:l:m:o:p:r:t:v");
        if (c == EOF) {
            break;
        }
        switch (c) {
            case '?': DisplayUsage();
                      break;
            case 'd': hp->trace = TRUE;
                      break;
            case 'o': strcpy_p(hp->responsefile, _MAX_FILE_NAME_SIZE, optarg, strlen(optarg));
                      break;
            case 'h': strcpy_p(hp->hostname, _MAX_HOST_NAME_SIZE, optarg, strlen(optarg));
                      break;
            case 'l': strcpy_p(hp->logfile, _MAX_FILE_NAME_SIZE, optarg, strlen(optarg));
                      break;
            case 'm': strcpy_p(hp->method, _MAX_METHOD_SIZE, optarg, strlen(optarg));
                      break;
            case 'f': SetFlags(optarg, hp);
                      break;
            case 'p': hp->port = atoi(optarg);
                      break;
            case 'r': strcpy_p(hp->request, _MAX_REQUEST_SIZE, optarg, strlen(optarg));
                      break;
            case 't': hp->timeout = TRUE;
                      break;
            case 'v': DisplayVersion();
                      break;
            default:  return (EXIT_FAILURE);
                      break;
        }
    }

    /*
    ** Check parameters
    */
    if (strlen(hp->hostname) < 1) {
        printf("error-> host name is required\n");
        return (EXIT_FAILURE);
    }
    if (strlen(hp->request) < 1) {
        printf("error-> request parameter is required\n");
        return (EXIT_FAILURE);
    }
    if (!(strcmp(hp->method, _HTTP_METHOD_GET) == 0 || strcmp(hp->method, _HTTP_METHOD_POST) == 0)) {
        return (EXIT_FAILURE);
    }

    /*
    ** Return status
    */
    return (EXIT_SUCCESS);
}

/*
** Process request
*/
static int ProcessRequest(HTTP_PARAMETERS *hp, HTTP_STATISTICS *hs) {
    HTTP_SERVER_ACTION_REQUEST *hsar = NULL;
    HTTP_REQUEST_TYPE method = HTTP_REQ_TYPE_GET;
    int status = 0;
    FILE *fp;

#ifdef PRINT_WARNING_MESSAGES
    HTTPPrintWarningMessages(TRUE);
#endif

    /*
    ** Allocate memory for server action request
    */
    if ((hsar = HTTPAllocateServerActionRequest(hsar)) == (HTTP_SERVER_ACTION_REQUEST *)NULL) {
        /*
        ** Display error message
        */
        printf("error-> HTTPAllocateServerActionRequest() failed: insufficient memory for HTTP_SERVER_ACTION_REQUEST\n");
        return (EXIT_FAILURE);
    }

    /*
    ** Open reponse file (or temporary file in place of response file)
    */
    if (strlen(hp->responsefile)) {
        if ((fopen_p(&fp, hp->responsefile, (const string_c_t)_F_RW_BIN)) != 0) {
            printf("error-> unable to open response file (errno %d)\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    else {
        tmpfile_p(&fp);
        if (fp == NULL) {
            printf("error-> unable to create and open temporary file\n");
            exit(EXIT_FAILURE);
        }
    }

    /*
    ** Set response file (pointer)
    */
    status += HTTPSetResponseFile(hsar, fp);

    /*
    ** Set server action request atttributes
    */
    status += HTTPSetHost(hsar, hp->hostname, strlen(hp->hostname));
    status += HTTPSetPort(hsar, hp->port);
    status += HTTPSetRequestBuffer(hsar, _MAX_REQUEST_SIZE);
    status += HTTPSetTimeout(hsar, hp->timeout);
    status += HTTPSetLogFileName(hsar, hp->logfile, strlen(hp->logfile));
    status += HTTPSetTrace(hsar, hp->trace);

    /*
    ** Set HTTP request method type
    */
    if (strcmp(hp->method, _HTTP_METHOD_GET) == 0) {
        method = HTTP_REQ_TYPE_GET;
    }
    if (strcmp(hp->method, _HTTP_METHOD_POST) == 0) {
        method = HTTP_REQ_TYPE_POST;
    }

    /*
    ** Set HTTP request method type, request and version header in request buffer
    */
    status += HTTPSetRequestType(hsar, method);
    status += HTTPSetRequest(hsar, hp->request, strlen(hp->request));
    status += HTTPSetVersionHeader(hsar, hp->hostname, strlen(hp->hostname));

    /*
    ** Send request to HTTP server and receive response in temporary file
    */
    if (HTTPSendServerRequest(hsar) < 0) {
        /*
        ** Free response file
        */
        HTTPFreeResponseFile(hsar);

        /*
        ** Free memory for server action request if server request failed
        */
        HTTPFreeServerActionRequest(hsar);
        return (EXIT_FAILURE);
    }

    /*
    ** Process response temporary file
    */
    status += ProcessResponseFile(fp, hp, hs);

    /*
    ** Free response file
    */
    HTTPFreeResponseFile(hsar);

    /*
    ** Free memory for server action request
    */
    HTTPFreeServerActionRequest(hsar);

    /*
    ** Return status
    */
    return (status);
}

/*
** Process response temporary file
*/
static int ProcessResponseFile(FILE *fp, HTTP_PARAMETERS *hp, HTTP_STATISTICS *hs) {
    char buffer[BUFSIZ];

    /*
    ** Rewind response file
    */
    rewind(fp);

    /*
    ** Get each text line from the temporary file
    */
    for (;; hs->linecount++) {
        /*
        ** Get a text line from the temporary file
        */
        memset(buffer, 0, BUFSIZ);
        fgets(buffer, sizeof(buffer), fp);
        if (feof(fp) || ferror(fp)) {
            break;
        }

        /*
        ** Increment byte counter
        */
        hs->bytecount = hs->bytecount + (long)strlen(buffer);

        /*
        ** Display line
        */
        if ((hp->mode & (_MODE_OUTPUT_ON))) {
            printf("%s", buffer);
        }
    }

    /*
    ** Return status
    */
    return (EXIT_SUCCESS);
}

/*
** Set parameters
*/
static void SetParameters(HTTP_PARAMETERS *hp) {
    /*
    ** Clear array parameters
    */
    memset(hp->hostname, 0, _MAX_HOST_NAME_SIZE + 1);
    memset(hp->request, 0, _MAX_REQUEST_SIZE + 1);
    memset(hp->responsefile, 0, _MAX_FILE_NAME_SIZE + 1);
    memset(hp->method, 0, _MAX_METHOD_SIZE + 1);
    memset(hp->logfile, 0, _MAX_FILE_NAME_SIZE + 1);

    /*
    ** Set default parameters
    */
    strcpy_p(hp->method, sizeof(_HTTP_METHOD_GET), (const string_c_t)_HTTP_METHOD_GET, sizeof(_HTTP_METHOD_GET));
    strcpy_p(hp->logfile, sizeof(_DEF_LOG_FILE), (const string_c_t)_DEF_LOG_FILE, sizeof(_DEF_LOG_FILE));

    /*
    ** Set default parameters(scalar fields)
    */
    hp->port = _DEF_HOST_PORT;
    hp->timeout = _DEF_NETWORK_TIMEOUT;
    hp->trace = FALSE;
    hp->mode = 0;
    hp->mode |= (_MODE_OUTPUT_ON);
    hp->mode |= (_MODE_STATISTICS_ON);
}

/*
** Set statistics
*/
static void SetStatistics(HTTP_STATISTICS *hs) {
    hs->bytecount = 0L;
    hs->linecount = 0L;
}

/*
** Set options
*/
static void SetFlags(string_c_t argument, HTTP_PARAMETERS *hp) {
    if (strcmp(argument, "output-on") == 0) {
        hp->mode |= _MODE_OUTPUT_ON;
    }
    if (strcmp(argument, "output-off") == 0) {
        hp->mode &= ~_MODE_OUTPUT_ON;
    }
    if (strcmp(argument, "statistics-on") == 0) {
        hp->mode |= _MODE_STATISTICS_ON;
    }
    if (strcmp(argument, "statistics-off") == 0) {
        hp->mode &= ~_MODE_STATISTICS_ON;
    }
}

/*
** Interrupt handler
*/
static void InterruptHandler(void) {
    printf("\nsignal detected!\n");

    /*
    ** Terminate application
    */
    exit(EXIT_SUCCESS);
}

/*
** Display statistics
*/
static void DisplayStatistics(HTTP_PARAMETERS *hp, HTTP_STATISTICS *hs) {
    if (!(hp->mode & (_MODE_STATISTICS_ON))) {
        return;
    }

    printf("\nbytes: %ld", hs->bytecount);
    printf("\tlines: %ld\n", hs->linecount);
}

/*
** Display version
*/
static void DisplayVersion(void) {
    string_c_t release = GetNetworkLibraryVersionRelease();

    printf("%s - get HTTP response\n", _GETHTTP_VERSION_PRODUCT);
    printf("%s network tools\n\n", release);
}

/*
** Display usage
*/
static void DisplayUsage(void) {
    printf("usage: %s (options)\n\n", _GETHTTP_VERSION_PRODUCT);
    printf("options: -h <hostname>\n");
    printf("         -p <port number>\n");
    printf("         -r <request parameters>\n");
    printf("         -o <response file path>\n");
    printf("         -m <[get|post]>\n");
    printf("         -t <timeout in seconds>\n");
    printf("         -l <log file name>\n");
    printf("         -f <flags>\n");
    printf("         -d enable debug\n");
    printf("         -v print version information and exit\n");
    printf("         -? print this usage\n\n");

    /*
    ** Terminate application
    */
    exit(EXIT_SUCCESS);
}
