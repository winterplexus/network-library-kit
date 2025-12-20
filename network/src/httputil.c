/*
**  @(#)httputil.c
**
**  libnetwork - HTTP networking utility functions
**  ----------------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Set request type
*/
int HTTPSetRequestType(HTTP_SERVER_ACTION_REQUEST *hsar, HTTP_REQUEST_TYPE type) {
    string_c_t format;

    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Are request buffer and request buffer size valid?
    */
    if (!hsar->request || !hsar->request_size) {
        return (-1);
    }

    /*
    ** Allocate memory for format buffer
    */
    format = (string_c_t)malloc(_MAX_REQUEST_SIZE + 1);
    if (format != NULL) {
        memset(format, 0, _MAX_REQUEST_SIZE + 1);
    }
    else {
        LogFilePrint((string_c_t)"error-> insufficient memory for format buffer (%s line: %d)\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Format request type
    */
    if (type == HTTP_REQ_TYPE_POST) {
        strfmt_p(format, _MAX_REQUEST_SIZE, (const string_c_t)"%s ", _HTTP_METHOD_POST);
    }
    else {
        strfmt_p(format, _MAX_REQUEST_SIZE, (const string_c_t)"%s ", _HTTP_METHOD_GET);
    }

    /*
    ** Copy formatted request type to request buffer
    */
    strcat_p(hsar->request, hsar->request_size, format, _MAX_REQUEST_SIZE);

    /*
    ** Free format buffer
    */
    free(format);

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Set request
*/
int HTTPSetRequest(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t value, const int value_size) {
    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Are request buffer and request buffer size valid?
    */
    if (!hsar->request || !hsar->request_size) {
        return (-1);
    }

    /*
    ** Are value and value size valid?
    */
    if (!value || !value_size || hsar->request_size < value_size) {
        return (-1);
    }

    /*
    ** Concatenate request value to request buffer
    */
    strcat_p(hsar->request, hsar->request_size, value, value_size);

    /*
    ** Return value size
    */
    return (value_size);
}

/*
** Set request parameter separator
*/
int HTTPSetRequestParameterSeparator(string_c_t request, const int req_size) {
    /*
    ** Are request buffer and request buffer size valid?
    */
    if (!request || !req_size) {
        return (-1);
    }

    /*
    ** Concatenate HTTP URL separator to request buffer
    */
    strcat_p(request, req_size, (const string_c_t)"&", sizeof("&"));

    /*
    ** Return status (success)
    */
    return (EXIT_SUCCESS);
}

/*
** Set HTTP version header
*/
int HTTPSetVersionHeader(HTTP_SERVER_ACTION_REQUEST *hsar, const string_c_t host, const int host_size) {
    int allocate_size;
    string_c_t format;
    int size = 0;

    /*
    ** Is HTTP server action request valid?
    */
    if (!hsar) {
        return (-1);
    }

    /*
    ** Are request buffer and request buffer size valid?
    */
    if (!hsar->request || !hsar->request_size) {
        return (-1);
    }

    /*
    ** Are host name and host name size valid?
    */
    if (!host || !host_size) {
        return (-1);
    }

    /*
    ** Calculate allocation size
    */
    allocate_size = hsar->request_size - 1;

    /*
    ** Allocate memory for format buffer
    */
    format = (string_c_t)malloc(allocate_size);
    if (format != NULL) {
        memset(format, 0, allocate_size);
    }
    else {
        LogFilePrint((string_c_t)"error-> insufficient memory for format buffer (%s line: %d)\n", __FILE__, __LINE__);
        return (-2);
    }

    /*
    ** Format HTTP version with parameter host name
    */
    strfmt_p(format, allocate_size, (const string_c_t)" HTTP/1.0\nHost: %s\n\n", host);

    /*
    ** Get length of formatted HTTP version header
    */
    size = (int)strlen(format);

    /*
    ** Concatenate formatted HTTP version header to request buffer
    */
    strcat_p(hsar->request, hsar->request_size, format, size);

    /*
    ** Free format buffers
    */
    free(format);

    /*
    ** Return length of formatted HTTP version header
    */
    return (size);
}