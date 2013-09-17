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

#include <iostream>
#include "sqlite3xx/sqlite3xx"
/* test needs 'unlink' from 'unistd.h' */
#if !defined _WIN32
#include <unistd.h>
#endif /* !defined _WIN32 */

using namespace sqlite3xx;
using namespace std;

int main( ) {
	(void)unlink( "test6.db" );

	try {
		cout << "creating DB.." << endl;
		connection c( "test6.db" );

		cout << "starting transaction.." << endl;
		work wc( c, "create" );

		cout << "create table.." << endl;
		wc.exec( "create table a( b integer )" );
		wc.commit( );

		work wi( c, "insert" );
		cout << "insert some data.." << endl;
		wi.exec( "insert into a( b ) values( 5 )" );
		wi.exec( "insert into a( b ) values( 18 )" );
		wi.exec( "insert into a( b ) values( 7 )" );
		wi.commit( );

		work wq( c, "query" );
		cout << "querying.." << endl;
		result r = wq.exec( "select * from a" );

		// traditional STL iterator
	        for( result::const_iterator i = r.begin( ); i < r.end( ); i++ ) {
			cout << i->rownumber( ) << i["b"] << endl;
		}
		wq.commit( );

		cout << "end." << endl;
	} catch( sql_error& e ) {
		cerr << e.msg( ) << ": " << e.query( ) << endl;
	}
}
