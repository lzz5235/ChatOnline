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

#include "sqlite3xx/transaction.hpp"

#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

namespace sqlite3xx {

transaction::transaction( connection &c, string name ) :
	_c( c ),
	_name( name ),
	_status( st_nascent ) {
}

transaction::~transaction( ) {
}

void transaction::commit( ) {
	switch( _status ) {
		case st_nascent:
			// skip, nothing to do
			return;

		case st_active:
			// continue below, this is what we expect
			break;

		case st_committed:
			// already commited, skip
			// TODO: we should warn the user about double commits
			break;

		case st_aborted:
			throw logic_error( "Attempt to commit previously aborted transaction!" );

		default:
			throw logic_error( "Illegal state in sqlite3::transaction::commit( )!" );
	}

	ostringstream s;
	s << "COMMIT TRANSACTION trans_" << _name;
	_c.exec( s.str( ).c_str( ) );
	_status = st_committed;
}

void transaction::abort( ) {
	switch( _status ) {
		case st_nascent:
			// skip, nothing to do
			return;

		case st_active:
			// continue below, this is what we expect
			break;

		case st_committed:
			throw logic_error( "Attempt to abort previously committed transaction!" );

		case st_aborted:
			// already aborted, skip
			// TODO: we should warn the user about double commits

		default:
			throw logic_error( "Illegal state in sqlite3::transaction::abort( )!" );
	}

	ostringstream s;
	s << "ROLLBACK TRANSACTION trans_" << _name;
	_c.exec( s.str( ).c_str( ) );
	_status = st_aborted;
}

void transaction::Begin( ) {
	switch( _status ) {
		case st_nascent:
			break;

		case st_active:
		case st_committed:
		case st_aborted:
		default:
			throw logic_error( "Illegal state in sqlite3::transaction::Begin( )!" );
	}

	ostringstream s;
	s << "BEGIN TRANSACTION trans_" << _name;
	_c.exec( s.str( ).c_str( ) );
}

result transaction::exec( string sql ) {
	switch( _status ) {
		case st_nascent:
			Begin( );
			break;

		case st_active:
			break;

		case st_committed:
		case st_aborted:
			throw logic_error( "Attempt to execute query " + sql + " in a transaction " +
				"which is already closed" );

		default:
			throw logic_error( "Illegal state in sqlite3::transaction::exec( )!" );
	}

	result r = _c.exec( sql );
	_status = st_active;

	return r;
}

prepare::invocation transaction::prepared( const string& name ) {
	return prepare::invocation( _c, *this, name ); 
}

} /* namespace sqlite3xx */
