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

#include "dbSqliteRecordset.h"
#include "dbSqliteError.h"

namespace sqlitepp {

/**
 *  @brief  Constructor
 */
dbSqliteRecordset::dbSqliteRecordset(): pos(0), rcEof(false), rcBof(false),
		rcIsEditing(false), rcIsNew(false)
{};

/**
 *  @brief  Destructor
 */
dbSqliteRecordset::~dbSqliteRecordset()
{};

/**
 *  @brief  Move to the first record in the recordset
 *  @return @c bool true if succeed otherwise false
 *
 *  If the current is being edited then it throws an "dbEditingRecord"
 *  exception.
 *
 *  The editing mode can be entered by the following "dbSqliteTable"
 *  functions: "dbSqliteTable::new" or "dbSqliteTable::edit".
 *
 *  To leave the editing mode is necessary a call to any of the following
 *  "dbSqliteTable" functions: "dbSqliteTable::save" or
 *  "dbSqliteTable::cancel"
 */
bool dbSqliteRecordset::first()
{
	if (rcIsEditing == true) {
		throw dbEditingRecord();
	};

	if ((dbTable.size() > 0) && (pos != 0)) {
		pos = 0;
	} else {
		return false;
	};

	return true;
};

/**
 *  @brief  Move to the previous record in the recordset
 *  @return @c bool true if succeed otherwise false
 *
 *  If the current is being edited then it throws an "dbEditingRecord"
 *  exception.
 *
 *  The editing mode can be entered by the following "dbSqliteTable"
 *  functions: "dbSqliteTable::new" or "dbSqliteTable::edit".
 *
 *  To leave the editing mode is necessary a call to any of the following
 *  "dbSqliteTable" functions: "dbSqliteTable::save" or
 *  "dbSqliteTable::cancel"
 */
bool dbSqliteRecordset::previous()
{
	if (rcIsEditing == true) {
		throw dbEditingRecord();
	};

	if ((dbTable.size() > 0) && (pos > 0)) {
		--pos;

		rcBof = false;
	} else {
		rcBof = true;
	
		return false;
	};

	return true;
};

/**
 *  @brief  Move to the next record in the recordset
 *  @return @c bool true if succeed otherwise false
 *
 *  If the current is being edited then it throws an "dbEditingRecord"
 *  exception.
 *
 *  The editing mode can be entered by the following "dbSqliteTable"
 *  functions: "dbSqliteTable::new" or "dbSqliteTable::edit".
 *
 *  To leave the editing mode is necessary a call to any of the following
 *  "dbSqliteTable" functions: "dbSqliteTable::save" or
 *  "dbSqliteTable::cancel"
 */
bool dbSqliteRecordset::next()
{
	if (rcIsEditing == true) {
		throw dbEditingRecord();
	};

	if ((dbTable.size() > 0) && (pos < dbTable.size() - 1)) {
		++pos;

		rcEof = false;
	} else {
		rcEof = true;
		
		return false;
	};

	return true;
};

/**
 *  @brief  Move to the last record in the recordset
 *  @return @c bool true if succeed otherwise false
 *
 *  If the current is being edited then it throws an "dbEditingRecord"
 *  exception.
 *
 *  The editing mode can be entered by the following "dbSqliteTable"
 *  functions: "dbSqliteTable::new" or "dbSqliteTable::edit".
 *
 *  To leave the editing mode is necessary a call to any of the following
 *  "dbSqliteTable" functions: "dbSqliteTable::save" or
 *  "dbSqliteTable::cancel"
 */
bool dbSqliteRecordset::last()
{
	if (rcIsEditing == true) {
		throw dbEditingRecord();
	};

	if ((dbTable.size() > 0) && (pos < dbTable.size() - 1)) {
		pos = dbTable.size() - 1;
	} else {
		return false;
	};

	return true;
};

/**
 *  @brief  Returns the bof flag
 *  @return @c true if in the begin of the recordset otherwise false
 */
bool dbSqliteRecordset::bof()
{
	return rcBof;
};

/**
 *  @brief  Returns the oef flag
 *  @return @c true if in the end of the recordset otherwise false
 */
bool dbSqliteRecordset::eof()
{
	return rcEof;
};

/**
 *  @brief  Return the number of record in the recordset
 *  @return  @c int
 */
int dbSqliteRecordset::count() const
{
	return dbTable.size();
};

/**
 *  @brief  Return the current record position in the recordset
 *  @return  @c this
 */
int dbSqliteRecordset::position()
{
	if ((dbTable.size() > 0)) {
		return (pos + 1);
	}
	
	return pos;
};

/**
 *  @brief  Clear all record in the recordset
 *
 *  This protected function is used by "dbSqliteQuery" for clear all records
 *  in the recordset. This is done when a SQL query is executed thru the
 *  "dbSqliteQuery::execute" function.
 */
void dbSqliteRecordset::clear()
{
	dbTable.clear();
	dbIndex.clear();
};

/**
 *  @brief  Return a field by its position
 *  @param  field  field position in the recordset
 *  @return  @c dbSqliteField
 *
 *  Return an field stored in @a field position of the recordset. If this
 *  position doesn't refer to any field an "dbIndexOutOfBounds" exception is
 *  thrown.
 */
dbSqliteField& dbSqliteRecordset::operator[] (const int field)
{
	if (field > (dbTable[pos].size() - 1)) {
		throw dbIndexOutOfBounds(field);
	};

	return dbTable[pos][field];
};

/**
 *  @brief  Return a field by its name
 *  @param  field  field name
 *  @return  @c dbSqliteField
 *
 *  Return an field stored in the recordset with the name of @a field. If this
 *  name doesn't refer to any field an "dbFieldNameNotFound" exception is
 *  thrown.
 */
dbSqliteField& dbSqliteRecordset::operator[] (const string& field)
{
	if (dbIndex.find(field) == dbIndex.end()) {
		throw dbFieldNameNotFound(field);
	};

	return dbTable[pos][dbIndex[field]];
};

};
