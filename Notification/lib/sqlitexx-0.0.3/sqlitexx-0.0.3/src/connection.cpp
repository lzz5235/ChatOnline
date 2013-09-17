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

#include "sqlite3xx/connection.hpp"
#include "sqlite3xx/except.hpp"

#include "port/sqlite.h"
#include "port/unused.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

#include <sstream>

namespace sqlite3xx {

connection::connection( ) {
	db = NULL;
	_internal_tno = 0;
	_trace = false;
}

connection::connection( string filename ) :
	_filename( filename) {
	_internal_tno = 0;
	_trace = false;
	sqlite3_open( filename.c_str( ), &db );
}

connection::connection( const connection& c ) {
	db = c.db;
	prepared_stmts = c.prepared_stmts;
	_internal_tno = 0;
	_trace = false;
}

connection::~connection( ) {
	assert( db != NULL );
	sqlite3_close( db );
}

extern "C" void profiling_callback( void *a, const char *b, sqlite3_uint64 c ) {
	SQLITEXX_UNUSED( a );
	cout << "TRACE: " << b << " (time: " << c / 1000 << " ms)" << endl;
}

void connection::trace( bool __trace ) {
	_trace = __trace;
	if( _trace ) {
		sqlite3_profile( db, profiling_callback, NULL );
	} else {
		sqlite3_profile( db, NULL, NULL );
	}
}

ostream& operator<<( ostream& o, const connection& c ) {
	o << "sqlite3xx::connection(" << c._filename << ")";
	return o;
}

result connection::exec( string sql ) {
	ostringstream s;
	s << "internal_" << *this << "_" << ++_internal_tno;
	prepare::declaration decl = prepare( s.str( ), sql );
	return prepared_exec( s.str( ) );
}

result connection::prepared_exec( const string& name ) {
	PSMap::iterator it;
	prepared_stmt* stmt = find_prepared( name );
	if( _trace ) cout << "TRACE: exec '" << name << "'" << endl;
	return result( stmt->getStmt( ) );
	// TODO: remove the prepared statement again!
}

prepared_stmt* connection::find_prepared( const string& name ) {
	PSMap::iterator it;
	it = prepared_stmts.find( name );
	if( it == prepared_stmts.end( ) ) {
		throw invalid_argument( "Unknown prepared statement '" + name + "'" );
	}
	return it->second;
}

prepare::declaration connection::prepare( const string& name, string sql ) {
	PSMap::iterator it;
	it = prepared_stmts.find( name );
	if( it != prepared_stmts.end( ) ) {
		if( it->second->sql( ) == sql ) {
			ostringstream s;
			s << "Inconsistent redefinition "
				"of prepared statement " << name 
				<< "(SQL: " << sql << ")";
			throw new invalid_argument( s.str( ) );
		}
	} else {
		prepared_stmts.insert( make_pair( name,
			new prepared_stmt( this->db, sql.c_str( ) ) ) );
	}
	if( _trace ) cout << "TRACE: prepared '" << name << "' as '" << sql << "'" << endl;
	return prepare::declaration( *this, name );
}

void connection::prepare_param_declare( const string& name, const string& sqltype, prepare::param_treatment& treatment ) {
	prepared_stmt* stmt = find_prepared( name );
	stmt->addparam( sqltype, treatment );
}

void connection::unprepare( string name ) {
	prepared_stmt* stmt = find_prepared( name );
	delete stmt;
	prepared_stmts.erase( name );
}

void connection::prepared_reset( const string& name ) {
	prepared_stmt* stmt = find_prepared( name );
	stmt->reset( );
}

void connection::prepare_setparam( const string& name, const int pos, const int value ) {
	prepared_stmt* stmt = find_prepared( name );
	if( _trace ) cout << "TRACE: prepared '" << name << "' param '" <<
		pos << "'" << " value: " << value << endl;
	stmt->setparam( pos, value );
}

void connection::prepare_setparam( const string& name, const int pos, const char* value ) {
	prepared_stmt* stmt = find_prepared( name );
	if( _trace ) cout << "TRACE: prepared '" << name << "' param '" <<
		pos << "'" << " value: " << value << endl;
	stmt->setparam( pos, value );
}

void connection::prepare_setparam( const string& name, const int pos, const double value ) {
	prepared_stmt* stmt = find_prepared( name );
	if( _trace ) cout << "TRACE: prepared '" << name << "' param '" <<
		pos << "'" << " value: " << value << endl;
	stmt->setparam( pos, value );
}

void connection::prepare_setparam( const string& name, const int pos, const long value ) {
	prepared_stmt* stmt = find_prepared( name );
	if( _trace ) cout << "TRACE: prepared '" << name << "' param '" <<
		pos << "'" << " value: " << value << endl;
	stmt->setparam( pos, value );
}

void connection::prepare_setparam( const string& name, const int pos, const uintmax_t value ) {
	prepared_stmt* stmt = find_prepared( name );
	if( _trace ) cout << "TRACE: prepared '" << name << "' param '" <<
		pos << "'" << " value: " << value << endl;
	stmt->setparam( pos, value );
}

} /* namespace sqlite3xx */
