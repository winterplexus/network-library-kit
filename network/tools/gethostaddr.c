/*
**  @(#)gethostaddr.c
**
**  libnetwork utility - get IP address from host name utility
**  ----------------------------------------------------------
**
**  copyright 2001-2024 Code Construct Systems (CCS)
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
** Get host IP address utility
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
    GetOptions(argc, argv, hostname);

    /*
    ** Display usage if no hostname was given
    */
    if (strlen(hostname) < 1) {
        DisplayUsage();
    }

    /*
    ** Get host IP address
    */
    if (GetHostIPAddress(hostname, address, _MAX_IP_ADDRESS_SIZE) == EXIT_SUCCESS) {
        printf("host name  : %s\n", hostname);
        printf("IP address : %s\n\n", address);
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
static void GetOptions(int argc, string_c_t argv[], string_c_t hostname) {
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
        c = getopt(argc, argv, (const string_c_t)"?h:v");
        if (c == EOF) {
            break;
        }
        switch (c) {
            case '?': DisplayUsage();
                      break;
            case 'h': strcpy_p(hostname, _MAX_HOST_NAME_SIZE, optarg, _MAX_HOST_NAME_SIZE);
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

    printf("%s - get host address\n", _GETHOSTADDR_VERSION_PRODUCT);
    printf("%s network tools\n\n", release);
}

/*
** Display usage
*/
static void DisplayUsage(void) {
    printf("usage: %s (options)\n\n", _GETHOSTADDR_VERSION_PRODUCT);
    printf("where (options) include:\n\n");
    printf("-h  hostname\n");
    printf("-v  print version information and exit\n");
    printf("-?  print this usage\n\n");

    /*
    ** Terminate application
    */
    exit(EXIT_SUCCESS);
}