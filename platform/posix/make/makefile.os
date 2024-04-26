################################################################################
#                                                                              #
# makefile.os                                                                  #
#                                                                              #
# libnetwork library version 8.1.0 release 1                                   #
#                                                                              #
# copyright 2001-2024 Code Construct Systems (CCS) [CONFIDENTIAL]              #
#                                                                              #
################################################################################

# Open systems OS/OE port

#
# network library name.
#
TARGET = libnetwork.a

#
# Include path.
#
INCPATH = ../inc

#
# Library path.
#
LIBPATH = ../lib

#
# C compiler definitions and flags.
#
CC = c99
CDEBUG = -g
COPTIMIZE = -O3
CDEFS = -D_POSIX_ENVIRONMENT -D_POSIX_C_SOURCE=200122L
CFLAGS = -c $(CDEBUG) $(COPTIMIZE) $(CDEFS)

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
# Archiver and flags.
#
AR = ar
ARFLAGS = crvs

#
# Include flags.
#
INCLUDE = -I.

#
# List of include files.
#
INCLUDES = \
 	network.h

#
# Library path.
#
LIB = ../lib

#
# List of object files.
#
OBJECTS = \
	http.o \
	httputil.o \
	url.o \
	net.o \
	log.o \
	debug.o \
	version.o

all: $(TARGET)

#
# Rule for creating the network library file.
#
$(TARGET): $(OBJECTS)
	@echo "building $@"
	@$(AR) $(ARFLAGS) $@ $(OBJECTS)
	mv $(TARGET) $(LIBPATH)
	cp $(INCLUDES) $(INCPATH)

#
# Rule for building HTTP networking functions object.
#
http.o: http.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building HTTP networking utility functions object.
#
httputil.o: httputil.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building HTTP URL functions object.
#
url.o: url.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building TCP/IP network interface functions object.
#
net.o: net.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building library logging functions object.
#
log.o: log.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building debug functions object.
#
debug.o: debug.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building library version information object.
#
version.o: version.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for cleaning out generated files.
#
clean:
	rm -f *.o

