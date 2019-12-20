/*
**  @(#)debug.c
**
**  libnetwork - debug functions
**  ----------------------------
**
**  copyright 2001-2020 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Local function prototypes
*/
static string_c_t FormatNullStringValue(string_c_t);

/*
** Debug (print server action request) structure
*/
void HTTPDebugPrintServerActionRequest(HTTP_SERVER_ACTION_REQUEST *hsar) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return;
    }

    /*
    ** Print debug information
    */
    printf("\ndebug -> HTTP_SERVER_ACTION_REQUEST\n");
    printf(" hsar->host_name\t: %s\n", FormatNullStringValue(hsar->host_name));
    printf(" hsar->port_number\t: %d\n", hsar->port_number);
    printf(" hsar->request\t: %s\n", FormatNullStringValue(hsar->request));
    printf(" hsar->request_size\t: %d\n", hsar->request_size);
    printf(" hsar->response_fp\t: %p\n", (void *)hsar->response_fp);
    printf(" hsar->timeout\t: %d\n", hsar->timeout);
    printf(" hsar->log_file_name\t: %s\n", FormatNullStringValue(hsar->log_file_name));
    printf(" hsar->trace\t: %d\n\n", hsar->trace);
}

/*
** Print string value
*/
static string_c_t FormatNullStringValue(string_c_t value) {
    return (value ? value : (string_c_t)"null");
}