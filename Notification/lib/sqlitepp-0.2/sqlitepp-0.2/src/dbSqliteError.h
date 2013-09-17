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
 *                                                                          *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __DBSQLITEERROR_H
#define __DBSQLITEERROR_H

#include <iostream>
#include <exception>

#include "sqlite3.h"
#include "strings.h"

using std::string;
using std::exception;

namespace sqlitepp {

class dbSqliteConnection;

class dbSqliteError: public exception {
public:
	dbSqliteError() throw();
	dbSqliteError(const string& message, int code = 0);
	dbSqliteError(const dbSqliteConnection* connection);
	~dbSqliteError() throw();
	
	string message() const;
	int code() const;
	const dbSqliteError& print() const;

private:
	string erMessage;
	int erCode;
};

class dbConnectionClosed: public dbSqliteError {
public:
	dbConnectionClosed(): dbSqliteError("This operation cannot be performed in "
			"a closed connection.", SQLITE_ERROR)
	{};
};

class dbEmptyRecordset: public dbSqliteError {
public:
	dbEmptyRecordset(): dbSqliteError("This operation cannot be performed in "
			"a empty recordset.", SQLITE_ERROR)
	{};
};

class dbIndexOutOfBounds: public dbSqliteError {
public:
	dbIndexOutOfBounds(int index): dbSqliteError("Index " + ToStr<int>(index) +
			" is out of bounds.", SQLITE_ERROR)
	{};
};

class dbFieldNameNotFound: public dbSqliteError {
public:
	dbFieldNameNotFound(const string& name): dbSqliteError("Field name '"
			+ name + "' not found.", SQLITE_ERROR)
	{};
};

class dbEditingRecord: public dbSqliteError {
public:
	dbEditingRecord(): dbSqliteError("This operation cannot be performed "
			"while you is editing a record.", SQLITE_ERROR)
	{};
};

class dbNotEditingRecord: public dbSqliteError {
public:
	dbNotEditingRecord(): dbSqliteError("This operation cannot be performed "
			"while you are not editing a record.", SQLITE_ERROR)
	{};
};

class dbInvalidDatabaseFile: public dbSqliteError {
public:
	dbInvalidDatabaseFile(const string& path): dbSqliteError("The especified "
			"database file '" + path + "' isn't a valid Sqlite3 file.",
			SQLITE_ERROR)
	{};
};

class dbInvalidSql: public dbSqliteError {
public:
	dbInvalidSql(const string& sql): dbSqliteError("The SQL that you entered "
			"'"+ sql + "' is not a valid.", SQLITE_ERROR)
	{};
};

class dbFileNotFound: public dbSqliteError {
public:
	dbFileNotFound(const string& path): dbSqliteError("The specified file '"
			+ path + "' could not be found.", SQLITE_ERROR)
	{};
};

class dbFileBufferOverflow: public dbSqliteError {
public:
	dbFileBufferOverflow(): dbSqliteError("The size to read from the file has "
			"passed the end of the file.")
	{};
};

};

#endif
