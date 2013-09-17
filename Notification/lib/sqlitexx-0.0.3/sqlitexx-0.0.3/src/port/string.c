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

#include "port/string.h"

/**
 * strdup is not always part of the C library or they need insane flags to
 * be set which would enable too many non-standard things.
 */

#if !defined HAVE_STRDUP || defined TEST_STRDUP

#include <stdlib.h>		/* for malloc, NULL */

char *sqlitexx_port_strdup( const char *s ) {
	char *d;
	d = (char *)malloc( strlen( s ) + 1 );
	if( d == NULL ) return NULL;
	strcpy( d, s );
	return d;
}

#endif /* !defined HAVE_STRDUP || defined TEST_STRDUP */

