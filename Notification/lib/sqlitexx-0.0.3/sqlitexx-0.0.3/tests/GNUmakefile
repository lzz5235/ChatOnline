TOPDIR = ..

SUBDIRS =

INCLUDE_DIRS = \
	$(INCLUDE_FLAGS_SQLITE3) \
	-I$(TOPDIR)/include

INCLUDE_LDFLAGS = \
	$(LDFLAGS_SQLITE3)

INCLUDE_LIBS = \
	$(TOPDIR)/src/libsqlite3xx.a \
	$(LIBS_SQLITE3) \
	$(LIBS_DL) \
	-lstdc++

TEST_CPP_BINS = \
	test1$(EXE) \
	test2$(EXE) \
	test3$(EXE) \
	test4$(EXE) \
	test5$(EXE) \
	test6$(EXE) \
	test7$(EXE) \
	test8$(EXE)

TEST_BINS = \
	testc$(EXE)

OBJS =

-include $(TOPDIR)/makefiles/gmake/sub.mk

local_all:

local_clean:
	-@rm -f *.db *.db-journal 2>/dev/null
	-@rm -f *.RES *.DIFF

local_distclean:

test1$(EXE): $(TOPDIR)/src/libsqlite3xx.a
test2$(EXE): $(TOPDIR)/src/libsqlite3xx.a
test3$(EXE): $(TOPDIR)/src/libsqlite3xx.a
test4$(EXE): $(TOPDIR)/src/libsqlite3xx.a
test5$(EXE): $(TOPDIR)/src/libsqlite3xx.a
test6$(EXE): $(TOPDIR)/src/libsqlite3xx.a
test7$(EXE): $(TOPDIR)/src/libsqlite3xx.a
test8$(EXE): $(TOPDIR)/src/libsqlite3xx.a

# disabled tests
#-@./exec_test test6 "STL iterators" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
#-@./exec_test test7 "tracing" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"

# create the must files with ./test2 | sed 's/\(time:[^\)]*\)//g' > test2.MUST
# to eliminate the execution time..
local_test:
	@./exec_test testc "test plain old C API" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
	@./exec_test test1 "create and close database" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
	@./exec_test test2 "create simple table, insert some data, query it" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
	@./exec_test test3 "prepared statements with parameter binding" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
	@./exec_test test4 "type conversion of bind parameters" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
	@./exec_test test5 "PRAGMAs outside a transaction" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
	@./exec_test test8 "ticket #14: to conversion fails with SQLITE_NULL" "$(PLATFORM)" "$(LINUX_DIST)" "$(LINUX_REV)"
