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
	(void)unlink( "test3.db" );

	try {
		cout << "creating DB.." << endl;
		connection c( "test3.db" );
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
		cout << "found " << r.size( ) << " records.." << endl;
		cout << "found " << r.columns( ) << " columns.." << endl;
		for( result::size_type i = 0; i < r.columns( ); i++ ) {
			cout << "column " << i << ": "  << r.column_type( i ) << endl;
		}
		assert( r.size( ) == 2 );

	        for( result::size_type i = 0; i < r.size( ); i++ ) {
			cout << "i: " << i << endl;

			// by field number
			cout << "(by col number) i: " << r[i][0] << ", s: " << r[i][1] << ", d: " << r[i][2] << endl;

			// associative array
			cout << "(by col name) i: " << r[i]["i"] << ", s: " << r[i]["s"] << ", d: " << r[i]["d"] << endl;

			// map to variables of a given type
			int value_i;
			string value_s;
			double value_d;
			r[i]["i"].to( value_i );
			r[i]["s"].to( value_s );
			r[i]["d"].to( value_d );
			cout << "(mapped) i: " << value_i << ", s: " << value_s << ", d: " << value_d << endl;
		}
		assert( r.size( ) == 2 );
		wq.commit( );

		cout << "end." << endl;
	} catch( sql_error& e ) {
		cerr << e.msg( ) << ": " << e.query( ) << endl;
	}
}
