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
	(void)unlink( "test4.db" );

	try {
		cout << "creating DB.." << endl;
		connection c( "test4.db" );
		cout << "connection object is " << c << endl;

		cout << "starting transaction.." << endl;
		work wc( c, "create" );

		cout << "create table.." << endl;
		wc.exec( "create table ally( id integer primary key, name text, tag text, members integer, villages integer, points integer, all_points integer, rank integer)" );
		wc.commit( );

		work wi( c, "insert" );
		cout << "insert some data.." << endl;
		c.prepare( "ins", "insert into ally( id, name, tag, members, villages, points, all_points, rank ) values( $1, $2, $3, $4, $5, $6, $7, $8 )" )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "text", sqlite3xx::prepare::treat_direct )
				( "text", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct );
		c.prepare( "ins2", "insert into ally( id, name, tag, members, villages, points, all_points, rank ) values( $1, $2, $3, $4, $5, $6, $7, $8 )" )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "text", sqlite3xx::prepare::treat_direct )
				( "text", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct )
				( "integer", sqlite3xx::prepare::treat_direct );
		result r = wi.prepared( "ins" )(1350)("Die+EliTe")("EliTe")(34)(34)(11708)(11708)(92).exec( );
		cout << "inserted with proper types " << r.affected_rows( ) << " rows." << endl;
		r = wi.prepared( "ins2" )("1351")("Die+EliTe")("EliTe")("34")("34")("11708")("11708")("92").exec( );
		cout << "inserted all as strings " << r.affected_rows( ) << " rows." << endl;
		wi.commit( );

		cout << "end." << endl;
	} catch( sql_error& e ) {
		cerr << e.msg( ) << ": " << e.query( ) << endl;
	}
}
