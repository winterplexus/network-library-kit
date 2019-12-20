/*
**  @(#)url.c
**
**  libnetwork - HTTP URL functions
**  -------------------------------
**
**  copyright 2001-2020 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Local function prototypes
*/
static char ConvertHexadecimal(char);
static char ConvertASCII(char);

/*
** HTTP URL encode
*/
int URLEncode(string_c_t url, string_c_t encode) {
    /*
    ** Is URL or encode buffer valid?
    */
    if (!url || !encode) {
        return (-1);
    }

    /*
    ** Set pointers to URL and encode buffer
    */
    string_c_t u = url, e = encode;

    /*
    ** Process each character in URL buffer
    */
    while (*u) {
        /*
        ** Store URL character in encode buffer if URL character is: alphanumeric, dash, underscore, period or tilde character
        */
        if (isalnum((unsigned char)*u) || *u == '-' || *u == '_' || *u == '.' || *u == '~') {
            *e++ = *u;
        }
        /*
        ** Store '+' character in encode buffer if URL character is a space
        */
        else if (*u == ' ') {
            *e++ = '+';
        }
        /*
        ** Otherwise, encode URL character and store result in encode buffer
        */
        else {
            *e++ = '%', *e++ = ConvertHexadecimal(*u >> 4), *e++ = ConvertHexadecimal(*u & 15);
        }

        /*
        ** Go to next character in URL buffer
        */
        u++;
    }

    /*
    ** Null terminate encode buffer
    */
    *e = '\0';

    /*
    ** Return length of encode buffer
    */
    return ((int)strlen(encode));
}

/*
** HTTP URL decode
*/
int URLDecode(string_c_t encode, string_c_t decode) {
    /*
    ** Is decode or encode buffer valid?
    */
    if (!encode || !decode) {
        return (-1);
    }

    /*
    ** Set pointers to URL and encode buffers
    */
    string_c_t e = encode, d = decode;

    /*
    ** Process each character in encode buffer
    */
    while (*e) {
        /*
        ** Decode character if encode character is a percent and store in decode buffer
        */
        if (*e == '%') {
            if (e[1] && e[2]) {
                *d++ = ConvertASCII(e[1]) << 4 | ConvertASCII(e[2]);
                e += 2;
            }
        }
        /*
        ** Store space character in decode buffer if URL character is a space
        */
        else if (*e == '+') {
            *d++ = ' ';
        }
        /*
        ** Otherwise, store character in decode buffer
        */
        else {
            *d++ = *e;
        }

        /*
        ** Go to next character in encode buffer
        */
        e++;
    }

    /*
    ** Null terminate decode buffer
    */
    *d = '\0';

    /*
    ** Return length of decode buffer
    */
    return ((int)strlen(decode));
}

/*
** Convert to hexadecimal representation
*/
static char ConvertHexadecimal(char code) {
    static char hexadecimal[] = "0123456789abcdef";

    return (hexadecimal[code & 15]);
}

/*
** Convert to ASCII representation
*/
static char ConvertASCII(char ch) {
    return (isdigit((unsigned char)ch) ? ch - '0' : tolower(ch) - 'a' + 10);
}