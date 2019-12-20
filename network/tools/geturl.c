/*
**  @(#)geturl.c
**
**  libnetwork utility - get encoded/decoded URL utility
**  ----------------------------------------------------
**
**  copyright 2001-2020 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Local function prototype
*/
static int GetOptions(int, string_c_t[], URL_PARAMETERS *);
static void EncodeDecode(URL_PARAMETERS *);
static void DisplayVersion(void);
static void DisplayUsage(void);

/*
** Get encoded or decoded URL utility
*/
int main(int argc, string_c_t argv[]) {
    URL_PARAMETERS up;
    int status = 0;

    /*
    ** Get command line options and check parameters
    */
    status = GetOptions(argc, argv, &up);
    if (status == EXIT_FAILURE) {
        return (EXIT_FAILURE);
    }

    /*
    ** Encode or decode (URL)
    */
    EncodeDecode(&up);

    /*
    ** Return status
    */
    return (status);
}

/*
** Get command line options
*/
static int GetOptions(int argc, string_c_t argv[], URL_PARAMETERS *up) {
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
        c = getopt(argc, argv, (const string_c_t)"?d:e:v");
        if (c == EOF) {
            break;
        }
        switch (c) {
            case '?': DisplayUsage();
                      break;
            case 'd': strcpy_p(up->url, _MAX_URL_SIZE, optarg, strlen(optarg));
                      up->operation_type = URL_DECODE;
                      break;
            case 'e': strcpy_p(up->url, _MAX_URL_SIZE, optarg, strlen(optarg));
                      up->operation_type = URL_ENCODE;
                      break;
            case 'v': DisplayVersion();
                      break;
            default:  exit(EXIT_FAILURE);
                      break;
        }
    }

    /*
    ** Check parameters
    */
    if (!strlen(up->url)) {
        printf("error-> URL is empty\n");
        return (EXIT_FAILURE);
    }

    /*
    ** Return status
    */
    return (EXIT_SUCCESS);
}

/*
** Encode or decode (URL)
*/
static void EncodeDecode(URL_PARAMETERS *up) {
    string_c_t buffer;

    /*
    ** Allocate memory for encode or decode buffer
    */
    buffer = ALLOCATE_URL_ENCODE_DECODE_BUFFER(up->url);
    if (buffer == NULL) {
        printf("error-> insufficient memory for encode (or decode) buffer\n");
        return;
    }

    /*
    ** Encode or decode URL
    */
    if (up->operation_type == URL_ENCODE) {
        if (URLEncode(up->url, buffer) != -1) {
            printf("%s\n", buffer);
        }
        else {
            printf("error-> unable to encode URL\n");
        }
    }
    if (up->operation_type == URL_DECODE) {
        if (URLDecode(up->url, buffer) != -1) {
            printf("%s\n", buffer);
        }
        else {
            printf("error-> unable to decode URL\n");
        }
    }

    /*
    ** Free memory for encode or decode buffer
    */
    free(buffer);
}

/*
** Display version
*/
static void DisplayVersion(void) {
    string_c_t release = GetNetworkLibraryVersionRelease();

    printf("%s - get URL (encoded or decoded)\n", _GETURL_VERSION_PRODUCT);
    printf("%s network tools\n\n", release);
}

/*
** Display usage
*/
static void DisplayUsage(void) {
    printf("usage: %s (options)\n\n", _GETURL_VERSION_PRODUCT);
    printf("where (options) include:\n\n");
    printf("-e  encode\n");
    printf("-d  decode\n");
    printf("-v  print version information and exit\n");
    printf("-?  print this usage\n\n");

    /*
    ** Terminate application
    */
    exit(EXIT_SUCCESS);
}