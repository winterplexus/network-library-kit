/*
**  @(#)modules.h
**
**  libnetwork - modules
**  --------------------
**
**  copyright 2001-2020 Code Construct Systems (CCS)
*/
#ifndef __MODULES_H
#define __MODULES_H

/*
** Standard C include files
*/
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

/*
** Include platforms file
*/
#include "platforms.h"

/*
** Network library include files
*/
#include "common.h"
#include "http.h"
#include "httputil.h"
#include "net.h"
#include "log.h"
#include "debug.h"
#include "port.h"
#include "url.h"
#include "version.h"

#endif /* __MODULES_H */