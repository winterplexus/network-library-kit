/*
**  @(#)version.c
**
**  libnetwork - library version information
**  ----------------------------------------
**
**  copyright 2001-2024 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Get version product
*/
string_c_t GetNetworkLibraryVersionProduct(void) {
    return ((string_c_t)_NETWORK_PRODUCT);
}

/*
** Get version release
*/
string_c_t GetNetworkLibraryVersionRelease(void) {
    return ((string_c_t)_NETWORK_RELEASE);
}