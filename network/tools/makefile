################################################################################
#                                                                              #
# makefile.tools.os                                                            #
#                                                                              #
# libnetwork library - tools version 9.0.0 release 1                           #
#                                                                              #
# copyright 2001-2025 Code Construct Systems (CCS) [CONFIDENTIAL]              #
#                                                                              #
################################################################################

# Open Systems OS/OE port

#
# Get host address tool.
#
GETHOSTADDR = gethostaddr

#
# Get host name tool.
#
GETHOSTNAME = gethostname

#
# Get HTTP response tool.
#
GETHTTP = gethttp

#
# Get HTTP URL tool.
#
GETURL = geturl

#
# C compiler definitions and flags.
#
CC = c99
CDEBUG = -g
COPTIMIZE = -O3
CDEFS = -D_POSIX_ENVIRONMENT
CFLAGS = -c $(CDEBUG) $(COPTIMIZE) -ansi -pedantic -std=c99 $(CDEFS)

#
# C compiler warning flags.
#
CWARNS = \
	-Werror \
	-Wall \
	-Wextra \
	-Wwrite-strings \
	-Winit-self \
	-Wcast-align \
	-Wpointer-arith \
	-Wstrict-aliasing \
	-Wformat=2 \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wno-unused-parameter \
	-Wuninitialized \
	-Wold-style-definition \
	-Wstrict-prototypes \
	-Wmissing-prototypes

#
# Include flags.
#
INCLUDE = -I. -I../inc

#
# Library flags.
#
LIB = -L../lib -lnetwork

#
# List of object files.
#
OBJECTS = \
	gethostaddr.o \
	gethostname.o \
	gethttp.o \
    geturl.o \
	getopt.o \
	port.o

#
# List of targets to be made.
#
all: $(GETHOSTADDR) $(GETHOSTNAME) $(GETHTTP) $(GETURL)

#
# Rule for building get host address tool the using specified objects and network library file.
#
$(GETHOSTADDR): gethostaddr.o getopt.o port.o 
	@echo "building $@"
	@$(CC) gethostaddr.o getopt.o port.o $(LIB) -o $@

#
# Rule for building get host name tool the using specified objects and network library file.
#
$(GETHOSTNAME): gethostname.o getopt.o port.o 
	@echo "building $@"
	@$(CC) gethostname.o getopt.o port.o $(LIB) -o $@

#
# Rule for building get HTTP response tool the using specified objects and network library file.
#
$(GETHTTP): gethttp.o getopt.o port.o 
	@echo "building $@"
	@$(CC) gethttp.o getopt.o port.o $(LIB) -o $@

#
# Rule for building get HTTP URL tool the using specified objects and network library file.
#
$(GETURL): geturl.o geturl.o port.o 
	@echo "building $@"
	@$(CC) geturl.o getopt.o port.o $(LIB) -o $@

#
# Rule for building the get host address utility object
#
gethostaddr.o: gethostaddr.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building the get host name utility object.
#
gethostname.o: gethostname.c 
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building the get HTTP response utility object.
#
gethttp.o: gethttp.c 
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building the get HTTP URL utility object.
#
geturl.o: geturl.c 
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building the get options functions object.
#
getopt.o: getopt.c 
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building the portable functions object.
#
port.o: port.c 
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for cleaning out generated files.
#
clean:
	rm -f *.o
	rm -f $(GETHOSTADDR)
	rm -f $(GETHOSTNAME)
	rm -f $(GETHTTP)
	rm -f $(GETURL)

