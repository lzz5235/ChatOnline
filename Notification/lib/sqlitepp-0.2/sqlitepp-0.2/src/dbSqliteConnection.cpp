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

#include "dbSqliteConnection.h"
#include "dbSqliteError.h"
#include "files.h"

using std::cout;
using std::endl;

namespace sqlitepp {

/**
 *  @brief  Default constructor
 */
dbSqliteConnection::dbSqliteConnection(): dbHandle(0), dbPath("")
{};

/**
 *  @brief  Constructor
 *  @param  path  path to the database file
 *  @param  flags  open mode flags
 *
 *  This constructor is just a wrapper for the open function.
 */
dbSqliteConnection::dbSqliteConnection(const string& path, enOpenFlags flags):
		dbHandle(0), dbPath("")
{
	open(path, flags);
};

/**
 *  @brief  Destructor
 *
 *  Do the object cleanup if the user hasn't done it.
 */
dbSqliteConnection::~dbSqliteConnection()
{
	if (isOpen()) {
		close();
	};
};

/**
 *  @brief  Open an Sqlite3 database
 *  @param  path  path to the database file
 *  @param  flags  open mode flags
 *  @return  @c this
 *
 *  If @a path is "" or ":memory:" opens a on-disk or on-memory database and
 *  print a warning message in the console.
 *
 *  If @a path is "" or ":memory:" and @a flags contains the "ofReadOnly" flag
 *  the database becomes useless. So we print a warning message in the
 *  console.
 *
 *  It tries to open the file specified by @a path, if it fails throws a
 *  "dbFileNotFound" exception. If it succeed, verifies if it is a valid
 *  Sqlite3 database file. When this fails a "dbInvalidDatabaseFile" exception
 *  is thrown.
 *
 *  Finaly when the database connection is being opened if occurs and error then
 *  a "dbSqliteError" exception is thrown.
 */
dbSqliteConnection& dbSqliteConnection::open(const string& path,
		enOpenFlags flags)
{
	if (isOpen()) {
		close();
	};

	// Test if the user opted for creating a in disk or memory temporary
	// database and print a warning message in the console
	if ((path == "") && (flags & ofReadWrite)) {
		cout << "WARNING: Creating a private temporary on-disk database.\n"
				"This database will be automatically deleted as soon as \n"
				"the database connection is closed.\n" << endl;
	} else if ((path == ":memory:") && (flags & ofReadWrite)) {
		cout << "WARNING: Creating a private temporary on-memory database.\n"
				"This database will be automatically deleted as soon as \n"
				"the database connection is closed.\n" << endl;
	} else if (((path == "") || (path == ":memory:")) && (flags & ofReadOnly)) {
 		cout << "WARNING: Creating a private temporary on-disk or\n"
 				"on-memory database. This database will be automatically\n"
 				"deleted as soon as the database connection is closed.\n"
 				"Also this database is useless because the read-only\n"
 				"attribute is set.\n" <<endl;
	} else {
		dbSqliteFile file(path);

		// Test if the specified filename exists an is a valid Sqlite3
		// database file
		if (file.isOpen() == false) {
			throw dbFileNotFound(path);
		} else if (string(file.read(15)) != "SQLite format 3") {
			throw dbInvalidDatabaseFile(path);
		};
	};

	// Open the connection with the database through Sqlite3 API
	if (sqlite3_open_v2(path.c_str(), &dbHandle, flags, 0) != SQLITE_OK) {
		throw dbSqliteError(this);
	};

	return (*this);
};

/**
 *  @brief  Close the connection with the database
 *  @return  @c this
 *
 *  Tries to close the connection with the database file. In case of any error
 *  throws a "dbSqliteError" exception.
 */
 //TODO Should the connection object be invalidated in case of error when
 // executing this close function?
dbSqliteConnection& dbSqliteConnection::close()
{
	if (isOpen()) {
		if (sqlite3_close(dbHandle) != SQLITE_OK) {
			throw(dbSqliteError(this));
		};
	};

	return (*this);
};

/**
 *  @brief  Return the pointer to the handle of the opened database
 *  @return  @c dbHandle - typedef for sqlite3* datatype
 *
 *  Returns the pointer, obtained by the "sqlite3_open_v2" function from the
 *  Sqlite3 API, that is used for any operations on a Sqlite3 database.
 *  This should be used if the users wants to call any Sqlite3 API function
 *  directely.
 */
const sqlite3* dbSqliteConnection::handle() const
{
	return dbHandle;
};

/**
 *  @brief  Return the current connection state
 *  @return  @c bool - true if open, false if closed
 */
bool dbSqliteConnection::isOpen() const
{
	return (dbHandle != 0);
};

};
