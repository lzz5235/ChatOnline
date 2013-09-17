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

#include "sqlite3xx/prepared_statement.hpp"

#include <sstream>
#include <cstdlib>
#include <cassert>
#include <cstring>

#include "sqlite3xx/except.hpp"
#include "sqlite3xx/connection.hpp"

#include "port/unused.h"

namespace sqlite3xx {

/* declaration */

prepare::declaration::declaration( connection& c, const string& stmt ) :
	_c( c ),
	_stmt( stmt ) {
}

const prepare::declaration&
prepare::declaration::operator( )( const string& sql_type, param_treatment treat ) const {
	_c.prepare_param_declare( _stmt, sql_type, treat );
	return *this;
}

/* invocation */

prepare::invocation::invocation( connection& c, transaction& t, const string& stmt ) :
	_c( c ),
	_t( t ),
	_stmt( stmt ) {
	_c.prepared_reset( _stmt );
	_pos = 0;
}

result prepare::invocation::exec( ) const {
	return _c.prepared_exec( _stmt );
}

prepare::invocation& prepare::invocation::setparam( const int& value, bool nonnull ) {
	SQLITEXX_UNUSED( nonnull );
	_pos++;
	_c.prepare_setparam( _stmt, _pos, value );
	return *this;
}

prepare::invocation& prepare::invocation::setparam( const char* value, bool nonnull ) {
	SQLITEXX_UNUSED( nonnull );
	_pos++;
	_c.prepare_setparam( _stmt, _pos, value );
	return *this;
}

prepare::invocation& prepare::invocation::setparam( const string& value, bool nonnull ) {
	SQLITEXX_UNUSED( nonnull );
	_pos++;
	_c.prepare_setparam( _stmt, _pos, value.c_str( ) );
	return *this;
}

prepare::invocation& prepare::invocation::setparam( const double& value, bool nonnull ) {
	SQLITEXX_UNUSED( nonnull );
	_pos++;
	_c.prepare_setparam( _stmt, _pos, value );
	return *this;
}

prepare::invocation& prepare::invocation::setparam( const long& value, bool nonnull ) {
	SQLITEXX_UNUSED( nonnull );
	_pos++;
	_c.prepare_setparam( _stmt, _pos, value );
	return *this;
}

prepare::invocation& prepare::invocation::setparam( const uintmax_t& value, bool nonnull ) {
	SQLITEXX_UNUSED( nonnull );
	_pos++;
	_c.prepare_setparam( _stmt, _pos, value );
	return *this;
}

/* prepared statement */

prepared_stmt::prepared_stmt( sqlite3 *db, string __sql ) :
	_db( db ) {
	int rc;
	const char *tail;
	_sql = __sql;
#if SQLITE_VERSION_NUMBER >= 3005000
	rc = sqlite3_prepare_v2( db, _sql.c_str( ), -1, &_stmt, &tail );
#else
	rc = sqlite3_prepare( db, _sql.c_str( ), -1, &_stmt, &tail );
#endif
	if( rc != SQLITE_OK ) { 
		ostringstream s;
		s << "sqlite3::prepared_stmt::prepared_stmt error: " << sqlite3_errmsg( _db );
		string msg = s.str( );
		throw sql_error( msg, _sql );
	}
}

prepared_stmt::~prepared_stmt( ) {
	assert( _stmt != NULL );
	sqlite3_finalize( _stmt );
	_stmt = NULL;
}

string prepared_stmt::sql( ) {
	return _sql;
}

void prepared_stmt::addparam( const string& sqltype, prepare::param_treatment& treatment ) {
	parameters.push_back( param( sqltype, treatment ) );
}

void prepared_stmt::reset( ) {
	int rc;
	assert( _stmt != NULL );
	rc = sqlite3_reset( _stmt );
	if( rc != SQLITE_OK ) { 
		ostringstream s;
		s << "sqlite3::prepared_stmt::reset error: " << sqlite3_errmsg( _db );
		string msg = s.str( );
		throw sql_error( msg, _sql );
	}
}

void prepared_stmt::setparam( const int pos, const int v ) {
	int rc;
	assert( _stmt != NULL );
	rc = sqlite3_bind_int( _stmt, pos, v );
	if( rc != SQLITE_OK ) {
		ostringstream s;
		s << "sqlite3::prepared_stmt::setparam bind error: "
		  << sqlite3_errmsg( _db ) << " (rc: " << rc << ")";
		string msg = s.str( );
		throw sql_error( msg, _sql );
	}
}

void prepared_stmt::setparam( const int pos, const char* v ) {
	int rc;
	assert( _stmt != NULL );
	rc = sqlite3_bind_text( _stmt, pos, v, strlen( v ), SQLITE_STATIC );
	if( rc != SQLITE_OK ) {
		ostringstream s;
		s << "sqlite3::prepared_stmt::setparam bind error: "
		  << sqlite3_errmsg( _db ) << " (rc: " << rc << ")";
		string msg = s.str( );
		throw sql_error( msg, _sql );
	}
}

void prepared_stmt::setparam( const int pos, const double v ) {
	int rc;
	assert( _stmt != NULL );
	rc = sqlite3_bind_double( _stmt, pos, v );
	if( rc != SQLITE_OK ) {
		ostringstream s;
		s << "sqlite3::prepared_stmt::setparam bind error: "
		  << sqlite3_errmsg( _db ) << " (rc: " << rc << ")";
		string msg = s.str( );
		throw sql_error( msg, _sql );
	}
}

void prepared_stmt::setparam( const int pos, const long v ) {
	int rc;
	assert( _stmt != NULL );
	rc = sqlite3_bind_int64( _stmt, pos, v );
	if( rc != SQLITE_OK ) {
		ostringstream s;
		s << "sqlite3::prepared_stmt::setparam bind error: "
		  << sqlite3_errmsg( _db ) << " (rc: " << rc << ")";
		string msg = s.str( );
		throw sql_error( msg, _sql );
	}
}

void prepared_stmt::setparam( const int pos, const uintmax_t v ) {
	int rc;
	assert( _stmt != NULL );
	rc = sqlite3_bind_int64( _stmt, pos, v );
	if( rc != SQLITE_OK ) {
		ostringstream s;
		s << "sqlite3::prepared_stmt::setparam bind error: "
		  << sqlite3_errmsg( _db ) << " (rc: " << rc << ")";
		string msg = s.str( );
		throw sql_error( msg, _sql );
	}
}

sqlite3_stmt* prepared_stmt::getStmt( ) const {
	return _stmt;
}

} /* namespace sqlite3xx */
