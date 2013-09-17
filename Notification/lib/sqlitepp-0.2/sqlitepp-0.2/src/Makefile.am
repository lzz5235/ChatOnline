
# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
lib_LTLIBRARIES = sqlitepp.so.la
sqlitepp_so_la_LDFLAGS = -module -no-undefined
include_HEADERS = sqlitepp.h
pkginclude_HEADERS = dbSqliteConnection.h dbSqliteError.h dbSqliteField.h \
	dbSqliteQuery.h dbSqliteRecordset.h dbSqliteTable.h files.h strings.h
sqlitepp_so_la_SOURCES = dbSqliteConnection.cpp dbSqliteError.cpp \
	dbSqliteField.cpp dbSqliteQuery.cpp dbSqliteRecordset.cpp dbSqliteTable.cpp files.cpp \
	sqlitepp.cpp
sqlitepp_so_la_LIBADD = -lsqlite3
