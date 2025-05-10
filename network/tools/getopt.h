/*
**  @(#)getopt.h
**
**  libnetwork utility - get options functions
**  ------------------------------------------
**
**  copyright 2001-2025 Code Construct Systems (CCS)
*/
#ifndef __GETOPT_H
#define __GETOPT_H

/*
** Option argument pointer
*/
extern string_c_t optarg;

/*
** Function prototypes
*/
extern int getopt(int, string_c_t [], string_c_t);

#endif /* __GETOPT_H */