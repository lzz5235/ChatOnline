/*
 *  sqlite3xx - sqlite3 C++ layer, following the ideas of libpqxx
 *  Copyright (C) 2009  Andreas Baumann
 *
 *  This copyrighted material is made available to anyone wishing to use,
 *  modify, copy, or redistribute it subject to the terms and conditions of
 *  the GNU Lesser General Public License, as published by the Free Software
 *  Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this distribution; if not, write to:
 *  Free Software Foundation, Inc.
 *  51 Franklin Street, Fifth Floor
 *  Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#if !defined( _WIN32 )
#include <unistd.h>
#endif

#define UNUSED( x ) if( 0 && (x) ) { }

void DirectExec( sqlite3* db, const char *sql );
void DirectExecNoResult( sqlite3* db, const char *sql );

static int callback( void *NotUsed, int argc, char **argv, char **azColName ){
	int i;
	UNUSED( NotUsed );

	for( i = 0; i < argc; i++ ) {
		printf( "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL" );
	}

	return 0;
}

void DirectExec( sqlite3* db, const char *sql ) {
	int rc;
	char *errmsg = NULL;

	rc = sqlite3_exec( db, sql, callback, 0, &errmsg );
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "SQL error in '%s': %s\n", sql, errmsg );
		sqlite3_free( errmsg );
		(void)sqlite3_close( db );
		exit( 1 );
	}
}

void DirectExecNoResult( sqlite3* db, const char *sql ) {
	int rc;
	char *errmsg = NULL;

	rc = sqlite3_exec( db, sql, NULL, 0, &errmsg );
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "SQL error in '%s': %s\n", sql, errmsg );
		sqlite3_free( errmsg );
		(void)sqlite3_close( db );
		exit( 1 );
	}
}

int main( void ) {
	sqlite3* db;
	int rc;
	sqlite3_stmt *stmt;
	const char *ptr;
	int i;

	(void)unlink( "testc.db" );

	rc = sqlite3_open( "testc.db", &db );
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "Can't open database: %s\n",
			sqlite3_errmsg( db ) );
		(void)sqlite3_close( db );
		exit( 1 );
	}

#if SQLITE_VERSION_NUMBER >= 3005000
	printf( "thread-safe: %d\n", sqlite3_threadsafe( ) ); 
#else
	printf( "thread-safe: no\n" );
#endif

	DirectExecNoResult( db, "create table a( b integer, s text )" );
	DirectExecNoResult( db, "insert into a(b,s) values (8,'bla')" );
	DirectExecNoResult( db, "insert into a(b,s) values (4,'blu')" );
	DirectExecNoResult( db, "insert into a(b,s) values (1,'bli')" );
	printf( "number of rows changed: %d (MUST: 1)\n", sqlite3_changes( db ) );
	DirectExecNoResult( db, "delete from a where b=47" );
	printf( "number of rows changed: %d (MUST: 0)\n", sqlite3_changes( db ) );

	/* with callbacks */
	DirectExec( db, "select * from a" );

	/* prepared statement */
#if SQLITE_VERSION_NUMBER >= 3005000
	rc = sqlite3_prepare_v2( db, "select * from a where b>=$1 and b<=$2",
		-1, &stmt, &ptr );
#else
	rc = sqlite3_prepare( db, "select * from a where b>=$1 and b<=$2",
		-1, &stmt, &ptr );
#endif
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "Unable to prepare statement: %s\n", sqlite3_errmsg( db ) );
		(void)sqlite3_close( db );
		exit( 1 );
	}
	rc = sqlite3_bind_int( stmt, 1, 3 );
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "Unable to bind first parameter: %s\n", sqlite3_errmsg( db ) );
		(void)sqlite3_finalize( stmt );
		(void)sqlite3_close( db );
		exit( 1 );
	}
	rc = sqlite3_bind_int( stmt, 2, 4 );
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "Unable to bind second parameter: %s\n", sqlite3_errmsg( db ) );
		(void)sqlite3_finalize( stmt );
		(void)sqlite3_close( db );
		exit( 1 );
	}
	printf( "number of bind parameters: %d (MUST: 2)\n", sqlite3_bind_parameter_count( stmt ) );

	rc = sqlite3_step( stmt );
	while( rc == SQLITE_ROW ) {
		switch( rc ) {
			case SQLITE_ROW:
				printf( "nof columns: %d\n", sqlite3_data_count( stmt ) );
				for( i = 0; i < sqlite3_data_count( stmt ); i++ ) {
					const char *colname = sqlite3_column_name( stmt, i );
					int data_type = sqlite3_column_type( stmt, i );
					switch( data_type ) {
						case SQLITE_INTEGER: {
							int value = sqlite3_column_int( stmt, i );
							printf( "%s(%d) = %d\n", colname, data_type, value );
						}
						break;

						case SQLITE_TEXT: {
							const unsigned char *value = sqlite3_column_text( stmt, i );
							printf( "%s(%d) = %s\n", colname, data_type, value );
						}
						break;
					}
				}
				break;
	
			default:
				fprintf( stderr, "Unable to step through statement: %s\n", sqlite3_errmsg( db ) );
				(void)sqlite3_finalize( stmt );
				(void)sqlite3_close( db );
				exit( 1 );
		}
		rc = sqlite3_step( stmt );
	}

	/* finalize prepared statement */
	rc = sqlite3_finalize( stmt );
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "Unable to finalize statement: %s\n", sqlite3_errmsg( db ) );
		(void)sqlite3_close( db );
		exit( 1 );
	}

	rc = sqlite3_close( db );
	if( rc != SQLITE_OK ) {
		fprintf( stderr, "Can't close database: %s\n",
			sqlite3_errmsg( db ) );
		exit( 1 );
	}

	exit( 0 );
}
