/*
**  @(#)log.h
**
**  libnetwork - library logging functions
**  --------------------------------------
**
**  copyright 2001-2020 Code Construct Systems (CCS)
*/
#ifndef __LOG_H
#define __LOG_H

/*
** Define default log file name
*/
#ifndef _LOGFILE_NAME
#define _LOGFILE_NAME "libnetwork"
#else
#error  _LOGFILE_NAME is defined in another include file
#endif

/*
** Define file mode string size
*/
#ifndef _FILE_MODE_SIZE
#define _FILE_MODE_SIZE 8
#else
#error  _FILE_MODE_SIZE is defined in another include file
#endif

/*
** Function prototypes
*/
extern void LogFileDirectory(const string_c_t, size_t);
extern void LogFileSetFileName(const string_c_t);
extern void LogFileOpen(void);
extern void LogFilePrint(string_c_t, ...);
extern void LogFileFlush(void);
extern void LogFileClose(void);

#endif /* __LOG_H */