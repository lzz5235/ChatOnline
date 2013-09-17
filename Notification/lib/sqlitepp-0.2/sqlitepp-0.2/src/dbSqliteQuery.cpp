/***************************************************************************
 *   Copyright (C) 2008 by Gustavo Ribeiro Croscato                        *
 *   croscato@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "dbSqliteQuery.h"
#include "dbSqliteConnection.h"
#include "dbSqliteError.h"

namespace sqlitepp {

/**
 *  @brief  Default constructor
 */
dbSqliteQuery::dbSqliteQuery()
{};

/**
 *  @brief  Constructor
 *  @param  connection "dbSqliteConnection" connection to the database
 *  @param  sql  SQL statement to be executed
 *
 *  Execute the SQL specified in the @a sql parameter and setup the
 *  "dbSqliteRecordset" object if necessary. The "dbSqliteRecordset" object is
 *  is the private variable "records".
 *
 *  If the @a connection is closed throws and "dbConnectionClosed" exception.
 */
dbSqliteQuery::dbSqliteQuery(const dbSqliteConnection& connection,
		const string& sql): qrSQL(sql)
{
	// Error checking
	if (connection.isOpen() == false) {
		throw dbConnectionClosed();
	};

	// dbSqliteQuery object setup
	dbConnection = &connection;
		
	if (sql != "") {
		execute();
	};
};

/**
 *  @brief  Destructor
 */
dbSqliteQuery::~dbSqliteQuery()
{
};

 /**
 *  @brief  Get/Set the connection of the query
 *  @param  connection  "dbSqliteConnection" object pointer
 *  @return  @c dbSqliteConnection
 *
 *  If called without parameters, it returns @c dbSqliteConnection.
 *
 *  If parameters are passed then it sets the query attibutes.
 *
 *  If the connection object passed refers to a closed connection then it throws
 *  an "dbConnectionClosed" exception.
 */
const dbSqliteConnection& dbSqliteQuery::connection(const dbSqliteConnection*
		conn)
{
	// Error checking
	if ((conn != 0) &&  (conn->isOpen() == false)) {
		throw dbConnectionClosed();
	};

	// Query setup
	if ((conn != 0) && (conn->isOpen() == true)) {
		dbConnection = conn;
		qrSQL = "";
	};

	return dbSqliteQuery::connection(conn);
};

 /**
 *  @brief  Get/Set the SQL used to create the query
 *  @param  sql  SQL to be executed
 *  @param  exec true if the SQL should be executed
 *  @return  @c string containing the SQL statement of the query
 *
 *  If called without parameters, it returns a @a string containing the current
 *  SQL statement of the query object.
 *
 *  If parameters are passed then it sets the query attributes and execute the
 *  SQL statament if @a exec is true.
 */
string dbSqliteQuery::sql(const string& sql, bool exec)
{
	// Query setup
	if ((dbConnection->isOpen()) && (sql != "")) {
		qrSQL = sql;

		if (exec) {
			execute();
		};
	};

	return qrSQL;
};

/**
 *  @brief  Execute the SQL statement of the query
 *  @return  @c this
 *
 *  This function prepares a SQL statement and execute it via Sqlite3 API
 *  functions. If the statement return records then it setup the
 *  "dbSqliteRecordset" object represented by the "records" attribute.
 *  It also setup the "dbIndex" and "dbTable" objects.
 *
 *  If the query don't have any SQL statement set it throws an "dbInvalidSql"
 *  exception.
 *
 *  If when the SQL statement is being prepared to be executed or when the
 *  statement return records, and a loop is executed to read then and fill
 *  the necessaries structures, an error ocurs, then it throws an
 * "dbSqliteError" exception.
 */
dbSqliteQuery& dbSqliteQuery::execute()
{
	// Initial error checking
	if (qrSQL == "") {
		throw dbInvalidSql(qrSQL);
	};

	// Pointer to the Sqlite Statement that will be prepared with
	// the SQL stored in qrSQL attribute
	sqlite3_stmt* statement;

	// Call this function to clear all data that could be stored in the
	// recordset. This empty the "dbTable" and "dbIndex" attributes.
	records.clear();
	
	// Parse the SQL stored in qrSQL and set statement to the prepared
	// Sqlite statement object
	if (sqlite3_prepare_v2(const_cast<sqlite3*>(dbConnection->handle()),
			qrSQL.c_str(), -1, &statement, 0) != SQLITE_OK) {
		sqlite3_finalize(statement);

		throw dbSqliteError(dbConnection);
	};

	// Loop through all rows in the prepared statement and fill in
	// the appropriate objects
	while (int ret = sqlite3_step(statement)) {
		// If the statement is already done we finalize the statement
		// and exit the loop. This is tested here because when a
		// statement like delete or update is executed no records are
        // returned.
		if (ret == SQLITE_DONE) {
			// Fill in the "dbIndex" object with the fields of the
			// resulting table
			for (int i = 0; i < sqlite3_column_count(statement); ++i) {
				records.dbIndex[(const char*)
						sqlite3_column_name(statement, i)] = i;
			};

			sqlite3_finalize(statement);

			break;
		};

		// If the statement has returned records, store them in the appropriate
		// objects
		if (ret = SQLITE_ROW) {
			Record dbRec;

			// This loop generate a Record object
			for (int i = 0; i < sqlite3_data_count(statement); ++i) {
				// This is necessary in the case of a record field be null.
				// The function sqlite3_column_text returns a null pointer
				// that if it if used to initiate a string object it throws
				// an exception.
				const char* chrColumnText = (const char*)
						sqlite3_column_text(statement,i);

				string strColumnText = "";

				// Before we initialize the string object, test if
				// chrColumnText has a valid pointer.
				if (chrColumnText) {
					strColumnText = chrColumnText;
				};

				// Create a field and add it to the record
				dbSqliteField dbField(strColumnText);
				dbRec.push_back(dbField);
			};

			// Add the created record to the table
			records.dbTable.push_back(dbRec);
		// In case of some error finalize the statement and throw an exception
		} else if (ret == SQLITE_ERROR) {
			sqlite3_finalize(statement);

			throw dbSqliteError(dbConnection);;
		// If the database is busy, try to access it more ten times.
		// If it fails after the 10th time throw an exception.
		} else if (ret == SQLITE_BUSY) {
			static int busyCount = 0;
			++busyCount;

			// TODO Sleep() function for give the Sqlite database
			//      a time to execute the current operation

			if (busyCount == 10) {
				sqlite3_finalize(statement);

				throw dbSqliteError(dbConnection);
			};
		};
	};

	return (*this);
};

};
