/*
**  @(#)gethostname.c
**
**  libnetwork utility - get host name from IP4 address utility
**  ----------------------------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Local function prototype
*/
static void GetOptions(int, string_c_t[], string_c_t);
static void InterruptHandler(void);
static void DisplayVersion(void);
static void DisplayUsage(void);

/*
** Get host IP4 address utility
*/
int main(int argc, string_c_t argv[]) {
    char hostname[_MAX_HOST_NAME_SIZE + 1], address[_MAX_IP_ADDRESS_SIZE + 1];

    /*
    ** Sockets startup
    */
    SOCKETS_STARTUP;

    /*
    ** Set signal trap for signal interrupt from the console or OS
    */
    signal(SIGINT, (fptr_c_t)InterruptHandler);

    /*
    ** Setup hostname and address parameters
    */
    memset(hostname, 0, _MAX_HOST_NAME_SIZE + 1);
    memset(address, 0, _MAX_IP_ADDRESS_SIZE + 1);

    /*
    ** Get command line options
    */
    GetOptions(argc, argv, address);

    /*
    ** Display usage if no address was given
    */
    if (strlen(address) < 1) {
        DisplayUsage();
    }

    /*
    ** Get host name
    */
    if (GetHostName(address, hostname, _MAX_HOST_NAME_SIZE) == EXIT_SUCCESS) {
        printf("host name  : %s\n", hostname);
        printf("IP4 address : %s\n\n", address);
    }

    /*
    ** Sockets cleanup
    */
    SOCKETS_CLEANUP;

    /*
    ** Return status
    */
    return (EXIT_SUCCESS);
}

/*
** Get command line options
*/
static void GetOptions(int argc, string_c_t argv[], string_c_t address) {
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
        c = getopt(argc, argv, (const string_c_t)"a:hv");
        if (c == EOF) {
            break;
        }
        switch (c) {
            case '?': DisplayUsage();
                      break;
            case 'a': strcpy_p(address, _MAX_IP_ADDRESS_SIZE, optarg, _MAX_IP_ADDRESS_SIZE);
                      break;
            case 'v': DisplayVersion();
                      break;
            default:  exit(EXIT_FAILURE);
                      break;
        }
    }
}

/*
** Interrupt handler
*/
static void InterruptHandler(void) {
    /*
    ** Display interrupt message and exit application
    */
    printf("signal detected!\n");

    /*
    ** Terminate application
    */
    exit(EXIT_SUCCESS);
}

/*
** Display version
*/
static void DisplayVersion(void) {
    string_c_t release = GetNetworkLibraryVersionRelease();

    printf("%s - get host name\n", _GETHOSTNAME_VERSION_PRODUCT);
    printf("%s network tools\n\n", release);
}

/*
** Display usage
*/
static void DisplayUsage(void) {
    printf("usage: %s (options)\n\n", _GETHOSTNAME_VERSION_PRODUCT);
    printf("options: -a <IP4 address>\n");
    printf("         -v print version information and exit\n");
    printf("         -? print this usage\n");

    /*
    ** Terminate application
    */
    exit(EXIT_SUCCESS);
}