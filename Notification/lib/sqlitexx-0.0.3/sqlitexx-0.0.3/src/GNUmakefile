TOPDIR = ..

SUBDIRS =

INCLUDE_DIRS = \
	$(INCLUDE_FLAGS_SQLITE3) \
	-I$(TOPDIR)/include \
	-I.

INCLUDE_LDFLAGS = \
	$(LDFLAGS_SQLITE3)

INCLUDE_LIBS = \
	$(LIBS_SQLITE3)

PORT_OBJS = \
	port/string.o \
	port/sleep.o
	
OBJS = \
	$(PORT_OBJS)

CPP_OBJS = \
	connection.o \
	prepared_statement.o \
	transaction.o \
	result.o \
	except.o

STATIC_LIB = libsqlite3xx.a

DYNAMIC_LIB = libsqlite3xx.so
DYNAMIC_LIB_MAJOR = 0
DYNAMIC_LIB_MINOR = 0
DYNAMIC_LIB_PATCH = 0

-include $(TOPDIR)/makefiles/gmake/sub.mk

local_all:

local_clean:

local_distclean:

local_install:

local_uninstall:
