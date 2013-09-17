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

#include "dbSqliteField.h"
#include "dbSqliteError.h"
#include "strings.h"

namespace sqlitepp {

/**
 *  @brief  Default constructor
 */
dbSqliteField::dbSqliteField(): fdValue("")
{};

/**
 *  @brief  Destructor
 */
dbSqliteField::~dbSqliteField()
{};

/**
 *  @brief  Protected constructor
 *  @param  value  value of the field
 *
 *  This constructor is used by "dbSqliteQuery" and "dbSqliteTable" to
 *  initialize the field value. This is done when a field is being inserted in
 *  a "dbSqliteRecordset".
 */
dbSqliteField::dbSqliteField(const string& value): fdValue(value)
{};

/**
 *  @brief  Return the value of the field
 *  @return  @c string
 *
 *  Return the current value of the field as an string.
 */
string dbSqliteField::asString()
{
	return fdValue;
};

/**
 *  @brief  Return the value of the field
 *  @return  @c integer
 *
 *  Return the current value of the field as an integer.
 */
int dbSqliteField::asInteger()
{
	return StrTo<int>(fdValue);
};

/**
 *  @brief  Return the value of the field
 *  @return  @c double
 *
 *  Return the current value of the field as an double.
 */
double dbSqliteField::asDouble()
{
	return StrTo<double>(fdValue);
};

/**
 *  @brief  Return the value of the field
 *  @return  @c float
 *
 *  Return the current value of the field as an float.
 */
float dbSqliteField::asFloat()
{
	return StrTo<float>(fdValue);
};

};
