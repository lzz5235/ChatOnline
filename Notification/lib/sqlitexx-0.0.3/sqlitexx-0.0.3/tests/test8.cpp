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
		wc.exec( "create table a( i integer, d double, s text, t text )" );
		wc.commit( );

		work wi( c, "insert" );
		cout << "insert some data.." << endl;
		c.prepare( "ins", "insert into a( i, d, s, t ) values( NULL, NULL, NULL, ? )" )
			( "text", sqlite3xx::prepare::treat_direct );
		result r = wi.prepared( "ins" )( "bla" ).exec( );
		cout << "inserted " << r.affected_rows( ) << " rows." << endl;
		r = wi.prepared( "ins" )( "blu" ).exec( );
		cout << "inserted " << r.affected_rows( ) << " rows." << endl;
		r = wi.prepared( "ins" )( "bli" ).exec( );
		cout << "inserted " << r.affected_rows( ) << " rows." << endl;
		wi.commit( );

		work wq( c, "query" );
		cout << "querying.." << endl;
		c.prepare( "qry", "select * from a" );

		r = wq.prepared( "qry" ).exec( );
		cout << "found " << r.size( ) << " records.." << endl;
		cout << "found " << r.columns( ) << " columns.." << endl;
		for( result::size_type i = 0; i < r.columns( ); i++ ) {
			cout << "column " << i << ": "  << r.column_type( i ) << endl;
		}
		assert( r.size( ) == 2 );

	        for( result::size_type i = 0; i < r.size( ); i++ ) {
			cout << "i: " << i << endl;

			// by field number
			cout << "(by col number) i: " << r[i][0] << " d: " << r[i][1] << " s: " << r[i][2] << " t: " << r[i][3] << endl;

			// associative array
			cout << "(by col name) i: " << r[i]["i"] << " d: " << r[i]["d"] << " s: " << r[i]["s"] << " t: " << r[i]["t"] << endl;

			// map to variables of a given type
			int value_i;
			double value_d;
			string value_s;
			string value_t;
			r[i]["i"].to( value_i );
			r[i]["d"].to( value_d );
			r[i]["s"].to( value_s );
			r[i]["t"].to( value_t );
			cout << "(mapping) i: " << value_i << " d: " << value_d << " s: " << value_s << " t: " << value_t << endl;
		}
		assert( r.size( ) == 3 );
		wq.commit( );

		cout << "end." << endl;
	} catch( sql_error& e ) {
		cerr << e.msg( ) << ": " << e.query( ) << endl;
	}
}
