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

#ifndef __DBSQLITETABLE_H
#define __DBSQLITERABLE_H

#include <iostream>
#include <algorithm>

using std::string;

#include "dbSqliteQuery.h"
#include "dbSqliteError.h"

namespace sqlitepp {

class dbSqliteConnection;
class dbSqliteRecord;

class dbSqliteTable: public dbSqliteQuery {
public:
	dbSqliteTable();
 	dbSqliteTable(const dbSqliteConnection& connection, const string& name);
 	~dbSqliteTable();

	dbSqliteTable& open(const dbSqliteConnection& connection,
			const string& name);

	const dbSqliteConnection& connection(const dbSqliteConnection* conn);

	string table(const string& name = "");

	dbSqliteTable& insert();
	dbSqliteTable& remove();
	dbSqliteTable& edit();
	dbSqliteTable& save();
	dbSqliteTable& cancel();

	bool isEditing() const;
	bool isNew() const;

	dbSqliteTable& setField(const string& name, const string& value);
	dbSqliteTable& setField(const string& name, int value);
	dbSqliteTable& setField(const string& name, double value);
	dbSqliteTable& setField(const string& name, float value);
	dbSqliteTable& setField(const string& name, const void* value);
	dbSqliteTable& setFieldFromFile(const string& name, const string& path);

	dbSqliteTable& setField(int position, const string& value);
	dbSqliteTable& setField(int position, int value);
	dbSqliteTable& setField(int position, double value);
	dbSqliteTable& setField(int position, float value);
	dbSqliteTable& setField(int position, const void* value);
	dbSqliteTable& setFieldFromFile(int position, const string& path);

private:
	void sql();
	void execute();

private:
	string tbName;
	Record rcEdited;
};

};

#endif
