/*
 *  sqlite3xx - sqlite3 C++ layer, following the ideas of libpqxx
 *  Copyright (C) 2009  Andreas Baumann
 *
 *  This copyrighted material is made available to anyone wishing to use,
 *  modify, copy, or redistribute it subject to the terms and conditions of
 *  the GNU Lesser General Public License, as published by the Free Software
 *  Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this distribution; if not, write to:
 *  Free Software Foundation, Inc.
 *  51 Franklin Street, Fifth Floor
 *  Boston, MA  02110-1301  USA
 *
 */

/* mark variables as being unused */

#ifndef __PORT_UNUSED_H
#define __PORT_UNUSED_H

/**
 * @brief Macro to avoid unused parameter messages in functions
 *
 * We could use __attribute__(unused) but I run into some problems
 * on OpenBSD 4.5 with it..
 */
#ifdef __GNUC__
#define SQLITEXX_UNUSED( x ) if( 0 && (x) ) { }
#else
#define SQLITEXX_UNUSED( x ) { }
#endif

#endif /* ifndef __PORT_UNUSED_H */
