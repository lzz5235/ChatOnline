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

#ifndef __DBSQLITEQUERY_H
#define __DBSQLITEQUERY_H

#include <iostream>

using std::string;

#include "dbSqliteRecordset.h"

namespace sqlitepp {

class dbSqliteConnection;

class dbSqliteQuery {
public:
	dbSqliteQuery();
	dbSqliteQuery(const dbSqliteConnection& connection, const string& sql = "");
	~dbSqliteQuery();

	const dbSqliteConnection& connection(const dbSqliteConnection*
			connection = 0);

	string sql(const string& sql = "", bool exec = true);
	
	dbSqliteQuery& execute();

public:
	dbSqliteRecordset records;

protected:
	const dbSqliteConnection* dbConnection;

private:
	string qrSQL;
};

};

#endif
