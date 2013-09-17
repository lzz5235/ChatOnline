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

#ifndef __DBSQLITERECORDSET_H
#define __DBSQLITERECORDSET_H

#include <iostream>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

#include "dbSqliteField.h"

namespace sqlitepp {

typedef vector<dbSqliteField> Record;
typedef vector<Record> Table;
typedef map<string,int> Index;

typedef vector<dbSqliteField>::iterator RecordIterator;
typedef map<string,int>::const_iterator IndexIterator;

class dbSqliteQuery;
class dbSqliteTable;

class dbSqliteRecordset {
public:
	friend class dbSqliteQuery;
	friend class dbSqliteTable;

	dbSqliteRecordset();
	~dbSqliteRecordset();

	bool first();
	bool previous();
	bool next();
	bool last();
	bool bof();
	bool eof();

	int count() const;
	int position();

	dbSqliteField& operator[] (int field);
	dbSqliteField& operator[] (const string& field);

protected:
	void clear();

protected:
	Table dbTable;
	Index dbIndex;

	bool rcIsEditing;
	bool rcIsNew;
	int pos;
	
private:
	bool rcBof;
	bool rcEof;
};

};

#endif
