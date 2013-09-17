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

#include "files.h"
#include "dbSqliteError.h"

namespace sqlitepp {

/**
 *  @brief  Constructor
 *  @param  path  path of the file to be opened
 *
 *  This is a helper function that is used by "dbSqliteConnection" to verify
 *  if the specified file exists and if is a valid Sqlite3 database file.
 */
dbSqliteFile::dbSqliteFile(const string& path): file_path(path)
{
	file.open(file_path.c_str(), std::ios::in | std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		file_size = (long) file.tellg();
		file.seekg(0, std::ios::beg);
		
		buffer = new char[file_size];
	};
};

/**
 *  @brief  Destructor
 */
dbSqliteFile::~dbSqliteFile()
{
	file.close();
	delete[] buffer;
};


const char* dbSqliteFile::read(int size)
{
	if (file.is_open()) {
		file.seekg(0, std::ios::beg);

		if (file_size == 0) {
			file.read(buffer, file_size);
		} else {
			if ((file_size - file.tellg()) > size) {
				file.read(buffer, size);
			} else {
				throw dbFileBufferOverflow();
			};
		};
	};

	return buffer;
};

bool dbSqliteFile::write(const char* buffer, int size)
{
	if (file.is_open()) {
		file.close();
	};

	file.open(file_path.c_str(), std::ios::out | std::ios::binary |
			std::ios::trunc);

	if (file.is_open()) {
		file.write(buffer, size);
	};

	file.close();

	file.open(file_path.c_str(), std::ios::in | std::ios::binary);
};

long dbSqliteFile::dbSqliteFile::size() const
{
	return file_size;
};

void dbSqliteFile::begin()
{
	if (file.is_open()) {
		file.seekg(0, std::ios::beg);
	};
};

void dbSqliteFile::end()
{
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
	};
};

/**
 *  @brief  Return if the file is opened or not
 *  @return  @c bool true if exist otherwise false
 */
bool dbSqliteFile::isOpen() const
{
	return file.is_open();
};

};
