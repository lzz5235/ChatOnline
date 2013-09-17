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

#ifndef __PORT_STRING_H
#define __PORT_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "port/sys_internal.h"

#include <string.h>

/* on some platforms we must also include the old strings.h to get
 * functions like str(n)casecmp */
#ifdef HAVE_STRINGS_H
#include <strings.h>		/* for strcasecmp and strncasecmp */
#endif

#include <sys/types.h>		/* for size_t */

#if defined _WIN32
#include <memory.h>		/* for memcpy */
#endif

#if !defined HAVE_STRDUP || defined TEST_STRDUP
char *sqlitexx_port_strdup( const char *s );
#endif
#if !defined HAVE_STRDUP
#define strdup sqlitexx_port_strdup
#endif

#ifdef __cplusplus
}
#endif

#endif /* ifndef __PORT_STRING_H */
