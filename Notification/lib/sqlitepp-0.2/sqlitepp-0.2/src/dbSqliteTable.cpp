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

#include "dbSqliteTable.h"
#include "dbSqliteConnection.h"
#include "dbSqliteError.h"
#include "files.h"

namespace sqlitepp {

/**
 *  @brief  Default constructor
 */
dbSqliteTable::dbSqliteTable(): tbName("")
{};

/**
 *  @brief  Constructor
 *  @param  connection  "dbSqliteConnection" connection to the database
 *  @param  name  name of the table to open
 *
 *  This function is just a wrapper for the "dbSqliteTable::open" function.
 */
dbSqliteTable::dbSqliteTable(const dbSqliteConnection& connection,
		const string& name)
 {
	open(connection, name);
 };

/**
 *  @brief  Destructor
 */
dbSqliteTable::~dbSqliteTable()
{};

/**
 *  @brief  Open a table in the database
 *  @param  connection  "dbSqliteConnection" connection to the database
 *  @param  name  name of the table to open
 *  @return @c this
 *
 *  Open a table in with the name @a name in the database.
 *
 *  This function is a wrapper for the inherited function "dbSqliteQuery::sql",
 *  it may throw any exceptions thrown by this function.
 */
dbSqliteTable& dbSqliteTable::open(const dbSqliteConnection& connection,
		const string& name)
{
	dbConnection = &connection;
	tbName = name;

	dbSqliteQuery::sql(string("SELECT * FROM ") + tbName, true);

	// Make the edited record object has the same number of fields than the
	// records contained in the table records
	rcEdited.resize(records.dbIndex.size());

	return (*this);
};

/**
 *  @brief  Get/Set the connection of the table
 *  @param  connection  "dbSqliteConnection" object pointer
 *  @return  @c dbSqliteConnection
 *
 *  If called without parameters, it returns @c dbSqliteConnection.
 *
 *  If parameters are passed then it sets the query attibutes.
 *
 *  If the connection object passed refers to a closed connection then it throws
 *  an "dbConnectionClosed" exception.
 */
const dbSqliteConnection& dbSqliteTable::connection(const dbSqliteConnection*
		conn)
{
	// Error checking
	if ((conn != 0) &&  (conn->isOpen() == false)) {
		throw dbConnectionClosed();
	};

	// Table setup
	if ((conn != 0) && (conn->isOpen() == true)) {
		dbConnection = conn;
		tbName = "";
	};

	return dbSqliteQuery::connection(conn);
};

 /**
 *  @brief  Get/Set the table name
 *  @param  name  name of the table in the database
 *  @return  @c string containing the table name
 *
 *  If called without parameters, it returns a @a string containing the current
 *  table name.
 *
 *  If parameters are passed then it sets the atributes and open the table.
 *  This function uses the "dbSqliteTable.open" function and it may throw any
 *  exception thrown by this function.
 */
string dbSqliteTable::table(const string& name)
{
	if (name != "") {
		tbName = name;

		open(dbSqliteQuery::connection(), tbName);
	}

	return tbName;
};

/**
 *  @brief  Insert a new record in the table
 *  @return  @c this
 *
 *  Create a new blank record in the table and put it in the editing mode.
 *  To fill in this new record use the appropriated setField functions.
 *
 *  If the connection wich the table refers to is closed then an
 *  "dbConnectionClosed" exception is thrown. If the table is already in
 *  editing mode then a "dbEditingRecord" exception is thrown.
 */
dbSqliteTable& dbSqliteTable::insert()
{
	// Error checking
	if ((dbConnection) && (dbConnection->isOpen() == false)) {
		throw dbConnectionClosed();
	};

	if (records.rcIsEditing == true) {
		throw dbEditingRecord();
	};

	// Change to editing mode
	records.rcIsEditing = true;
	records.rcIsNew = true;

	// Set to null all the values for the current edited record object.
	// This is done because this is a new blank record. The values of this
	// record should now be replaced by the setField function.

	for (int i = 0; i < records.dbIndex.size(); ++i) {
		rcEdited[i] = dbSqliteField("null");
	};

	return (*this);
};

/**
 *  @brief  Remove the current record from the table
 *  @return  @c this
 *
 *  Remove the current record in the recordset. This function calls the
 *  inherited function "dbSqliteQuery::sql". It may throw any exceptions
 *  thrown by this function.
 *
 *  If the connection which the table refers to is closed then an
 *  "dbConnectionClosed" exception is thrown. If the table is already in
 *  editing mode then a "dbEditingRecord" exception is thrown.
 *
 *  In the case of the recordset be empty an "dbSqliteEmptyRecordset" exception
 *  is thrown.
 */
dbSqliteTable& dbSqliteTable::remove()
{
	// Error checking
	if ((dbConnection) && (dbConnection->isOpen() == false)) {
		throw dbConnectionClosed();
	};

	if (records.rcIsEditing == true) {
		throw dbEditingRecord();
	};

	if (records.dbTable.size() == 0) {
		throw dbEmptyRecordset();
	};

	// Remove the current record

	RecordIterator recIt = records.dbTable[records.pos].begin();
	IndexIterator idxIt = records.dbIndex.begin();

	map<int,string> revIndex;
	map<int,string>::iterator revIdx;

	// Hack to reverse the Index Map so the fields names could
	// be retrieve in their natural order. This is necessary for
	// create the SQL statement that will be executed to remove the
	// current field.
	for (idxIt; idxIt != records.dbIndex.end(); ++idxIt) {
		revIndex[(*idxIt).second] = (*idxIt).first;
	};

	string sql = "DELETE FROM " + tbName + " WHERE ";

	revIdx = revIndex.begin();

	// Loop through all indexes stored in dbIndex and all sqliteFields
	// stored in dbTable[records.pos], to generate a string that will
	// be part of the SQL statement, executed to remove the current field.
	// This loop generate a string like 'fieldname=value and
	// fieldname=value and fieldname and'.
	for (recIt, revIdx; recIt !=
			records.dbTable[records.pos].begin(),
			revIdx !=revIndex.end(); ++recIt, ++revIdx) {

		sql += (*revIdx).second + "=";

		if ((*recIt).asString().find(" ", 0) != string::npos) {
			sql += "'" + (*recIt).asString() + "' and ";
		} else {
			sql += (*recIt).asString() + " and ";
		};
	};

	// Remove the leading ' and' in the SQL string
	sql.replace(sql.size() - 5, 4, ";");

	// Execute the generated SQL
	dbSqliteQuery::sql(sql,true);

	// Invalidate the current record position
	records.pos = 0;

	// Reselect all fields from the current table
	dbSqliteQuery::sql("SELECT * FROM " + tbName + ";", true);

	return (*this);
};

/**
 *  @brief  Put the table in editing mode
 *  @return  @c this
 *
 *  Set the table state to editing and the current record fields could be
 *  modified by the appropriateds setField functions.
 *
 *  If the connection wich the table refers to is closed then an
 *  "dbConnectionClosed" exception is thrown. If the table is already in
 *  editing mode then a "dbEditingRecord" exception is thrown.
 *
 *  In case of the recordset being empty an "dbSqliteEmptyRecordset" exception
 *  is thrown.
 */
 dbSqliteTable& dbSqliteTable::edit()
 {
 	// Error checking
	if ((dbConnection) && (dbConnection->isOpen() == false)) {
		throw dbConnectionClosed();
	};

	if (records.dbTable.size() == 0) {
		throw dbEmptyRecordset();
	};

	if (records.rcIsEditing == true) {
		throw dbEditingRecord();
	};
 
	// Put the table in editing mode
	records.rcIsEditing = true;

	// Set the fields of the edited record with the values of the
	// current field of the table
	rcEdited = records.dbTable[records.pos];
 };

/**
 *  @brief  Save modifications made in the record
 *  @return  @c this
 *
 *  It saves all modification made to the record through the setField function
 *  and also put the table in browsing mode again.
 *
 *  This function should be called after a "dbSqliteTable::new" or
 *  "dbSqliteTable::edit".
 *
 *  If the connection wich the table refers to is closed then an
 *  "dbConnectionClosed" exception is thrown. If the table is already in
 *  editing mode then a "dbEditingRecord" exception is thrown.
 */
dbSqliteTable& dbSqliteTable::save()
{
	// Error checking
	if ((dbConnection) && (dbConnection->isOpen() == false)) {
		throw dbConnectionClosed();
	};

	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Save the modifications made in the current record

	// This code must generate two diferente SQL statement to execute.
	// One for when a new record is being saved and another for when the current
	// record values are being updated.
	RecordIterator recIt = rcEdited.begin();
	string sql = "";

	// Choose which SQL statement to create, insert a new record or
	// update a existent one.
	if (records.rcIsNew == true) {
		sql = "INSERT INTO " + tbName + " VALUES (";
	} else {
		sql = "UPDATE " + tbName + " SET ";
	};

	// SQL statement to create a new record
	if (records.rcIsNew == true) {
		// This loop is used to generate a piece of the SQL statement used to
		// create a new record in the table. It generate a string like
		// "fieldvalue, 'fieldvalue', fieldvalue,"
		for (recIt; recIt != rcEdited.end(); ++recIt) {
			if ((*recIt).asString().find(" ", 0) != string::npos) {
				sql += "'" + (*recIt).asString() + "', ";
			} else {
				sql += (*recIt).asString() + ", ";
			};
		};
	// SQL statement to update the current record
	} else {
		IndexIterator idxIt = records.dbIndex.begin();

		// This loop is used to generate a piece of the SQL statement used to
		// update the current record of the table. It generate a string like
		// "fieldname=value, fieldname='value', fieldname=value,"
		for (idxIt; idxIt != records.dbIndex.end(); ++idxIt) {
			if (rcEdited[records.dbIndex[idxIt->first]].asString()
					.find(" ", 0) != string::npos) {
				sql += idxIt->first + "='" +
						rcEdited[records.dbIndex[idxIt->first]].asString()
						+ "', ";
			} else {
				sql += idxIt->first + "=" +
						rcEdited[records.dbIndex[idxIt->first]].asString()
						+ ", ";
			};
		};
	};

	// SQL statement to create a new record
	if (records.rcIsNew) {
		// Remove the leading "," and put the final
		// part of the SQL statement
		sql.replace(sql.size() - 2, 2, ");");
	// SQL statement to update the current record
	} else {
		// Remove the leading "," and generate the rest
		// of the SQL statement;
		sql.replace(sql.size() - 2, 2, " WHERE ");

		IndexIterator idxIt = records.dbIndex.begin();

		// This loop is used to genereate the second part of the SQL
		// statement that will update the current record. It generate the
		// comparission clause of the statement. This string is like
		// "fieldname=value and fieldname='value' and fieldname=value and"
		for (idxIt; idxIt != records.dbIndex.end(); ++idxIt) {
			sql += idxIt->first + "=";

			if (records.dbTable[records.pos]
					[records.dbIndex[idxIt->first]].asString().
					find(" ", 0) != string::npos) {
				sql += "'" + records.dbTable[records.pos]
						[records.dbIndex[idxIt->first]].asString()
						+ "' and ";
			} else {
				sql += records.dbTable[records.pos]
						[records.dbIndex[idxIt->first]].asString()
						+ " and ";
			};
		};

		// Replace the leading " and" and put the final
		// part of the SQL statement
		sql.replace(sql.size() - 5, 5, ";");
	};

	// Execute the prepated SQL statement
	dbSqliteQuery::sql(sql, true);

	// Reselect all fields of the table
	dbSqliteQuery::sql("SELECT * FROM " + tbName + ";", true);

	// Put the table in browsing mode
	records.rcIsEditing = false;
	records.rcIsNew = false;

	return (*this);
};

/**
 *  @brief  Cancel modifications made in the record
 *  @return  @c this
 *
 *  It cancels all modification made to the record through the setField function
 *  and also put the table in browsing mode again.
 *
 *  This function should be called after a "dbSqliteTable::new" or
 *  "dbSqliteTable::edit".
 *
 *  If the connection wich the table refers to is closed then an
 *  "dbConnectionClosed" exception is thrown. If the table isn't in
 *  editing mode then a "dbNotEditingRecord" exception is thrown.
 */
dbSqliteTable& dbSqliteTable::cancel()
{
	// Error checking
	if ((dbConnection) && (dbConnection->isOpen() == false)) {
		throw dbConnectionClosed();
	};

	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Put the table in browsing mode
	records.rcIsEditing = false;
	records.rcIsNew = false;

	return (*this);
};

/**
 *  @brief  Tells if a table is in editing mode
 *  @return  @c bool true if in editing mode, false otherwise
 */
bool dbSqliteTable::isEditing() const
{
	return records.rcIsEditing;
};

/**
 *  @brief  Tells if is editing a new record
 *  @return  @c bool true if in editing a new record, false otherwise
 */
bool dbSqliteTable::isNew() const
{
	return records.rcIsNew;
};

/**
 *  @brief  Set a field value for the record being edited by it's name
 *  @param  name  name of the field to be modified
 *  @param  value  new string value for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a name parameter.
 *
 *  If the field name doesn't exist in the record throws an
 *  "dbFieldNameNotFound" exception. If the table isn't in editing mode throws
 *  an"dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(const string& name,
		const string& value)
{
	// Error checking
	if (records.dbIndex.find(name) == records.dbIndex.end()) {
		throw dbFieldNameNotFound(name);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[records.dbIndex[name]] = dbSqliteField(value);

	return (*this);
};

/**
 *  @brief  Set a field value for the record being edited by it's name
 *  @param  name  name of the field to be modified
 *  @param  value  new intger value for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a name parameter.
 *
 *  If the field name doesn't exist in the record throws an
 *  "dbFieldNameNotFound" exception. If the table isn't in editing mode throws
 *  an"dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(const string& name, int value)
{
	// Error checking
	if (records.dbIndex.find(name) == records.dbIndex.end()) {
		throw dbFieldNameNotFound(name);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[records.dbIndex[name]] = dbSqliteField(ToStr<int>(value));

	return (*this);
};

/**
 *  @brief  Set a field value for the record being edited by it's name
 *  @param  name  name of the field to be modified
 *  @param  value  new double value for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a name parameter.
 *
 *  If the field name doesn't exist in the record throws an
 *  "dbFieldNameNotFound" exception. If the table isn't in editing mode throws
 *  an"dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(const string& name, double value)
{
	// Error checking
	if (records.dbIndex.find(name) == records.dbIndex.end()) {
		throw dbFieldNameNotFound(name);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[records.dbIndex[name]] = dbSqliteField(ToStr<double>(value));

	return (*this);
};

/**
 *  @brief  Set a field value for the record being edited by it's name
 *  @param  name  name of the field to be modified
 *  @param  value  new float value for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a name parameter.
 *
 *  If the field name doesn't exist in the record throws an
 *  "dbFieldNameNotFound" exception. If the table isn't in editing mode throws
 *  an"dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(const string& name, float value)
{
	// Error checking
	if (records.dbIndex.find(name) == records.dbIndex.end()) {
		throw dbFieldNameNotFound(name);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[records.dbIndex[name]] = dbSqliteField(ToStr<float>(value));

	return (*this);
};

dbSqliteTable& dbSqliteTable::setField(const string& name, const void* value)
{
	// Error checking
	if (records.dbIndex.find(name) == records.dbIndex.end()) {
		throw dbFieldNameNotFound(name);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[records.dbIndex[name]] =
		dbSqliteField(string(reinterpret_cast<const char*>(value)));

	return (*this);
};

dbSqliteTable& dbSqliteTable::setFieldFromFile(const string& name,
		const string& path)
{
	// Error checking
	if (records.dbIndex.find(name) == records.dbIndex.end()) {
		throw dbFieldNameNotFound(name);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	dbSqliteFile file(path);

	// Set the field value
	if (file.isOpen()) {
		rcEdited[records.dbIndex[name]] = dbSqliteField(string(file.read()));
	};

	return (*this);
};

/**
 *  @brief  Set a field value for the record being edited by it's position
 *  @param  position  position of the field in the recordset
 *  @param  value  new string value for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a position parameter.
 *
 *  If the field position doesn't exist in the record throws an
 *  "dbIndexOutOfBounds" exception. If the table isn't in editing mode throws
 *  an "dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(int position, const string& value)
{
	// Error checking
	if ((position > records.dbIndex.size() - 1) || (position < 0)) {
		throw dbIndexOutOfBounds(position);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[position] = dbSqliteField(value);

	return (*this);
};

/**
 *  @brief  Set a field value for the record being edited by it's position
 *  @param  position  position of the field in the recordset
 *  @param  value  new integer value for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a position parameter.
 *
 *  If the field position doesn't exist in the record throws an
 *  "dbIndexOutOfBounds" exception. If the table isn't in editing mode throws
 *  an "dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(int position, int value)
{
	// Error checking
	if ((position > records.dbIndex.size() - 1) || (position < 0)) {
		throw dbIndexOutOfBounds(position);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[position] = dbSqliteField(ToStr<int>(value));

	return (*this);
};

/**
 *  @brief  Set a field value for the record being edited by it's position
 *  @param  position  position of the field in the recordset
 *  @param  value  new double value for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a position parameter.
 *
 *  If the field position doesn't exist in the record throws an
 *  "dbIndexOutOfBounds" exception. If the table isn't in editing mode throws
 *  an "dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(int position, double value)
{
	// Error checking
	if ((position > records.dbIndex.size() - 1) || (position < 0)) {
		throw dbIndexOutOfBounds(position);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[position] = dbSqliteField(ToStr<int>(value));

	return (*this);
};

/**
 *  @brief  Set a field value for the record being edited by it's position
 *  @param  position  position of the field in the recordset
 *  @param  value  new string float for the field
 *  @return  @c this
 *
 *  Change the value of a field specified by the @a position parameter.
 *
 *  If the field position doesn't exist in the record throws an
 *  "dbIndexOutOfBounds" exception. If the table isn't in editing mode throws
 *  an "dbNotEditingRecord" exception.
 */
dbSqliteTable& dbSqliteTable::setField(int position, float value)
{
	// Error checking
	if ((position > records.dbIndex.size() - 1) || (position < 0)) {
		throw dbIndexOutOfBounds(position);
	};
	
	if (records.rcIsEditing == false) {
		throw dbNotEditingRecord();
	};

	// Set the field value
	rcEdited[position] = dbSqliteField(ToStr<int>(value));

	return (*this);
};

dbSqliteTable& dbSqliteTable::setField(int position, const void* value)
{
	return (*this);
};

dbSqliteTable& dbSqliteTable::setFieldFromFile(int position, const string& path)
{
	return (*this);
};

/**
 *  @brief  Private function to hide inherited "dbSqliteQuery::sql"
 */
void dbSqliteTable::sql()
{};

/**
 *  @brief  Private function to hide inherited "dbSqliteQuery::execute"
 */
void dbSqliteTable::execute()
{};

};
