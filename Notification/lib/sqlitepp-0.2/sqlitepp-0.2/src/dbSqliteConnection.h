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

#ifndef __DBSQLITECONNECTION_H
#define __DBSQLITECONNECTION_H

#include <iostream>

#include "sqlite3.h"

using std::string;

namespace sqlitepp {

enum enOpenFlags {
	ofReadWrite = SQLITE_OPEN_READWRITE,
	ofReadOnly = SQLITE_OPEN_READONLY,
	ofCreate = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE,
};

class dbSqliteConnection {
public:
	dbSqliteConnection();
	dbSqliteConnection(const string& path, enOpenFlags flags = ofCreate);
	~dbSqliteConnection();

	dbSqliteConnection& open(const string& path, enOpenFlags flags = ofCreate);
	dbSqliteConnection& close();
	const sqlite3* handle() const;
	bool isOpen() const;

private:
	sqlite3* dbHandle;
	string dbPath;
};

};

#endif
