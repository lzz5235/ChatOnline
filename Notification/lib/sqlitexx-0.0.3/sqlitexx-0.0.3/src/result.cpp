/*
    sqlite3xx - sqlite3 C++ layer, following ideas of libpqxx
    Copyright (C) 2009  Andreas Baumann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "port/string.h"

#include "sqlite3xx/result.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <cassert>
#include <cstdlib>

#include "sqlite3xx/except.hpp"

#include "port/unused.h"
#include "port/sleep.h"

using namespace std;

namespace sqlite3xx {

/* field */

ostream& operator<<( ostream& o, const result::field& f ) {
	int type = f._t.column_type( f._c );
	switch( type ) {
		case SQLITE_INTEGER: {
			int value = f._t.GetValueInt( f._c );
			o << value;
			}
			break;

		case SQLITE3_TEXT: {
			const unsigned char* value = f._t.GetValueText( f._c );
			o << value;
			}
			break;

		case SQLITE_FLOAT: {
			double value = f._t.GetValueDouble( f._c );
			o << value;
			}
			break;

		case SQLITE_NULL:
			o << "(NULL)";
			break;

		default:
			o << "(Unknown type " << type << "!)";
	}
	return o;
}

/* result */

void result::Step( ) {
	int rc;

TRY_AGAIN_STEP:
	rc = sqlite3_step( _stmt );
	switch( rc ) {
		case SQLITE_DONE:
			if( _crow == 0 ) {
				/* never had a result, will never read-ahead and buffer */
				_status = st_nodata;
			} else {
				/* last row */
				_status = st_lastrow;
				_crow++;
			}
			break;

		case SQLITE_ROW:
			_status = st_hasdata;
			_crow++;
			break;

		/* hotfix for ticket #13 */
		case SQLITE_BUSY:
			sqlitexx_port_sleep( 1 );
			goto TRY_AGAIN_STEP;

		default: {
			ostringstream s;
			s << "Illegal state after sqlite3_step (sqlite code: " << rc << ")";
			string str = s.str( );
			string msg = sqlite3_errmsg( sqlite3_db_handle( _stmt ) );
			throw sql_error( str, msg );
			}
	}
}

void result::BufferData( ) {
	const char *tmp = NULL;

	_cache.resize( columns( ) + 1 );

	for( size_type i = 0; i < columns( ); i++ ) {
		CachedValue value;
		value.type = column_type( i );
		switch( value.type ) {
			case SQLITE_INTEGER:
				value.value.i = sqlite3_column_int( _stmt, i );
				break;
			
			case SQLITE3_TEXT:
				/* KLUDGE: the documentation is not specific about returning NULL here (but
				 * it happens, see ticket #16). I get the feeling this is undefined behaviour,
				 * so people should not relly on it from outside. */
				tmp = (const char *)sqlite3_column_text( _stmt, i );
				if( tmp != NULL ) {
					value.value.s = (unsigned char *)strdup( tmp );
				} else {
					value.type = SQLITE_NULL;
					value.value.s = NULL;
				}
				break;

			case SQLITE_FLOAT:
				value.value.d = sqlite3_column_double( _stmt, i );
				break;

			case SQLITE_NULL:
				value.value.s = NULL;
				break;

			default: {
				ostringstream s;
				s << "Illegal type " << value.type << " when buffering row " << _row;
				string msg = s.str( );
				throw logic_error( msg );
			}
		}
		_cache.at( i ) = value;
	}
}

void result::FillColNameMap( ) {
	size_type i;
	const char* colname;
	for( i = 0; i < columns( ); i++ ) {
		colname = sqlite3_column_name( _stmt, i );
		_colmap.insert( make_pair( string( colname ), i ) );
	}
}

void result::FillColTypeMap( ) {
	size_type i;
	_coltype.resize( columns( ) + 1 );
	for( i = 0; i < columns( ); i++ ) {
		_coltype.at( i ) = sqlite3_column_type( _stmt, i );
	}
}

result::result( const result& r ) {
	_stmt = r._stmt;
	_status = r._status;
	_colmap = r._colmap;
	_coltype = r._coltype;
	_cache = r._cache;
	_row = r._row;
	_crow = r._crow;
}


result::result( sqlite3_stmt* stmt ) {
	_stmt = stmt;
	_status = st_nascent;
	_row = 0;
	_crow = 0;
	Step( );
	if( _status == st_hasdata || _status == st_lastrow ) {
		FillColNameMap( );
		FillColTypeMap( );
		BufferData( );
		Step( );
	}
}

result::~result( ) {
	switch( _status ) {
		case st_nascent: /* created no result fetched, weird, but ok */
			break;

		case st_nodata:
			/* a command without result data, just reset the prepared statement
			 * so it can be used again for the next set of parameters
			 */
			break;

		case st_lastrow:
			break;

		case st_hasdata:
		case st_nomoredata:
			/* TODO: free row table data */
			break;

		default:
			throw logic_error( "Illegal state in destructor" );
	}
}

result& result::operator=( const result& r ) {
	if( this != &r ) {
		_stmt = r._stmt;
		_status = r._status;
		_colmap = r._colmap;
		_coltype = r._coltype;
		_cache = r._cache;
		_row = r._row;
		_crow = r._crow;
	}
	return *this;
}

result::size_type result::affected_rows( ) const {
	switch( _status ) {
		case st_nascent:
			throw logic_error( "Called affected_rows() before sqlite3_step!" );

		case st_nodata:
			return sqlite3_changes( sqlite3_db_handle( _stmt ) );

		case st_hasdata:
		case st_lastrow:
		case st_nomoredata:
			throw logic_error( "Affected rows doesn't make sence in a query!" );

		default:
			throw logic_error( "Illegal state in affected_rows()" );
	}
}

result::size_type result::size( ) const {
	/* TODO: can we get this value with sqlite3_step, I doubt!
	 * at least we know from the state wheter it's 0 or 1 and more
	 */
	switch( _status ) {
		case st_nascent:
			throw logic_error( "Called size() before sqlite3_step!" );

		case st_nodata:
			return 0;

		case st_hasdata:
			/* ..but we know that the result must be at least _row */
			return _row + 2;

		case st_nomoredata:
			return _row + 1;

		case st_lastrow:
			return _row + 1;

		default:
			throw logic_error( "Illegal state in size()" );
	}
}

result::size_type result::columns( ) const {
	return sqlite3_column_count( _stmt );
}

const result::tuple result::operator[]( result::size_type i ) throw( ) {
	if( _row == i ) {
		return tuple( this, i );
	} else if( i == _row + 1 ) {
		_row++;
		BufferData( );
		Step( );
		return tuple( this, i );
	} else {
		throw logic_error( "Illegal access outside scope of cursor!" );
	}
}

result::size_type result::column_number( string name ) const {
	ColMap::const_iterator it = _colmap.find( name );
	if( it == _colmap.end( ) ) {
		throw invalid_argument( "Unknown column '" + name + "' requested" );
	}
	return it->second;
}

int result::column_type( size_type i ) const {
	if( _status != st_hasdata && _status != st_lastrow ) {
		throw logic_error( "Fetching row after sqlite returned no data!" );
	}
	return _coltype[i];
}

/* value caching */

result::CachedValue::CachedValue( const CachedValue& v ) {
	type = v.type;
	value = v.value;
	if( type == SQLITE3_TEXT ) {
		value.s = (unsigned char *)strdup( (const char *)v.value.s );
	}
}

result::CachedValue::~CachedValue( ) {
	if( type == SQLITE3_TEXT && value.s != NULL ) {
		free( value.s );
		value.s = NULL;
	}
}

result::CachedValue& result::CachedValue::operator= ( const result::CachedValue& v ) {
	if( this != &v ) {
		type = v.type;
		value = v.value;
		if( type == SQLITE3_TEXT ) {
			value.s = (unsigned char *)strdup( (const char *)v.value.s );
		}
	}
	return *this;	
}

/* const iterator for tuples */

result::const_iterator result::const_iterator::operator++( int incr ) {
	SQLITEXX_UNUSED( incr );
	const_iterator old( *this );
	// idx++;
	return old;
}

bool result::const_iterator::operator<( const result::const_iterator& i ) const {
	SQLITEXX_UNUSED( i.dummy );
	// idx < i.idx
	return false;
}

} /* namespace sqlite3xx */
