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

#include "dbSqliteError.h"
#include "dbSqliteConnection.h"

using std::cout;
using std::endl;

namespace sqlitepp {

/**
 *  @brief  Default constructor
 */
dbSqliteError::dbSqliteError() throw(): erMessage(""), erCode(0)
{};

/**
 *  @brief  Constructor
 *  @param  message  the error message
 *  @param  code  the error code
 */
dbSqliteError::dbSqliteError(const string& message, int code):
		erMessage(message), erCode(code)
{};

/**
 *  @brief  Constructor
 *  @param  connection  a pointer for a dbSqliteConnection object
 *
 *  Setup an error object based in the error message and error code return
 *  by the Sqlite3 API function "sqlite3_errmsg" and "sqlite3_errcode".
 */
dbSqliteError::dbSqliteError(const dbSqliteConnection* connection)
{
	erMessage = sqlite3_errmsg(const_cast<sqlite3*>(connection->handle()));
	erCode = sqlite3_errcode(const_cast<sqlite3*>(connection->handle()));
};

/**
 *  @brief  Destructor
 */
dbSqliteError::~dbSqliteError() throw()
{};

/**
 *  @brief  Open an Sqlite3 database
 *  @return  @c erMessage
 *
 *  Return a string representing the error message.
 */
string dbSqliteError::message() const
{
	return erMessage;
};

/**
 *  @brief  Open an Sqlite3 database
 *  @return  @c erCode
 *
 *  Returns a integer representing the error code.
 */
int dbSqliteError::code() const
{
	return erCode;
};

/**
 *  @brief  Print the error code and message
 *  @return  @c this
 *
 *  Print colored error code and message in the terminal window.
 *  For this uses ANSI/VT100 Terminal Control Codes. For more
 *  info on ANSI/VT100 visit http://www.termsys.demon.co.uk/vtansi.htm
 *  to get a full list of control codes.
 */
const dbSqliteError& dbSqliteError::print() const
{
	cout << endl;

	// Set the font color to bright red
	cout << "\033[1m\033[31m";
	cout << "Sqlite++ Library Error" << endl;

	// Set the font color to green
	cout << "\033[0m\033[32m";
	cout << "Error code...: ";

	// Set the font color to bright green
	cout << "\033[1m\033[32m";
	cout << erCode << endl;

	// Set the font color to green
	cout << "\033[0m\033[32m";
	cout << "Error message: ";

	// Set the font color to bright green
	cout << "\033[1m\033[32m";
	cout << erMessage << endl;

	// Reset all font attributes
	cout << "\033[0m";

	cout << endl;

	return (*this);
};

};
