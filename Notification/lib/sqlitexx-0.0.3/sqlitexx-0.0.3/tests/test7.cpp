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
#include <cassert>
#include "sqlite3xx/sqlite3xx"
/* test needs 'unlink' from 'unistd.h' */
#if !defined _WIN32
#include <unistd.h>
#endif /* !defined _WIN32 */

using namespace sqlite3xx;
using namespace std;

int main( ) {
	(void)unlink( "test7.db" );

	try {
		cout << "creating DB.." << endl;
		connection c( "test7.db" );
		c.trace( true );
		cout << "connection object is " << c << endl;

		cout << "starting transaction.." << endl;
		work wc( c, "create" );

		cout << "create table.." << endl;
		wc.exec( "create table a( i integer, s text, d double )" );
		wc.commit( );

		work wi( c, "insert" );
		cout << "insert some data.." << endl;
		c.prepare( "ins", "insert into a( i, s, d ) values( $1, $2, $3 )" )
			( "integer", prepare::treat_direct )
			( "text", prepare::treat_direct )
			( "double", prepare::treat_direct );
		result r = wi.prepared( "ins" )( 5 )( "bla" )( 8.933 ).exec( );
		cout << "inserted " << r.affected_rows( ) << " rows." << endl;
		r = wi.prepared( "ins" )( 18 )( "bli" )( 4.7771 ).exec( );
		cout << "inserted " << r.affected_rows( ) << " rows." << endl;
		r = wi.prepared( "ins" )( 7 )( "blu" )( -1.11111 ).exec( );
		cout << "inserted " << r.affected_rows( ) << " rows." << endl;
		wi.commit( );

		work wq( c, "query" );
		cout << "querying.." << endl;
		c.prepare( "qry", "select * from a where i>=$1 and i<=$2" )
			( "integer", prepare::treat_direct )
			( "integer", prepare::treat_direct );

		r = wq.prepared( "qry" )( 4 )( 8 ).exec( );
		wq.commit( );

		cout << "end." << endl;
	} catch( sql_error& e ) {
		cerr << e.msg( ) << ": " << e.query( ) << endl;
	}
}
