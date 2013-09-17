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

#ifndef __STRINGS_H
#define __STRINGS_H

#include <sstream>

using std::string;
using std::istringstream;
using std::ostringstream;

namespace sqlitepp {

/**
 * StrTo - Template function to convert a string to a number
 * value: string value to be converted
 */
template<class T>
T StrTo(const string& value) {
	istringstream strBuf(value);
	T ret;

	strBuf >> ret;

	return ret;
};

/**
 * ToStr - Template function to convert a number to a string
 * value: number value to converted
 */
template<class T>
string ToStr(T value) {
	ostringstream tmpStr;

	tmpStr << value;

	return tmpStr.str();
};

};

#endif
