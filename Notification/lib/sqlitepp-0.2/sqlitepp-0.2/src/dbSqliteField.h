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

#ifndef __DBSQLITEFIELD_H
#define __DBSQLITEFIELD_H

#include <iostream>

using std::string;

namespace sqlitepp {

class dbSqliteQuery;
class dbSqliteTable;
class dbSqliteRecord;

class dbSqliteField {
public:
	friend class dbSqliteQuery;
	friend class dbSqliteRecord;
	friend class dbSqliteTable;

	dbSqliteField();
	~dbSqliteField();

	string asString();
	int asInteger();
	double asDouble();
	float asFloat();

protected:
	dbSqliteField(const string& value);

private:
	string fdValue;
};

};

#endif
