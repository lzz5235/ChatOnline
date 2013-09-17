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

#include "port/sleep.h"

/**
 * There are different sleep functions on POSIX and WIN32 systems.
 */

#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#include <windows.h>		/* for Sleep */
#else
#include <unistd.h>		/* for sleep */
#endif

void sqlitexx_port_sleep( const unsigned int seconds ) {
#ifdef _WIN32
	Sleep( seconds * 1000 );
#else
	sleep( seconds );
#endif
}

