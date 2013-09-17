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
 *  MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this distribution; if not, write to:
 *  Free Software Foundation, Inc.
 *  51 Franklin Street, Fifth Floor
 *  Boston, MA  02110-1301  USA
 *
 */

#ifndef SQLITE3XX_SYS_INTERNAL_H
#define SQLITE3XX_SYS_INTERNAL_H

#if defined LINUX
#if OS_MAJOR_VERSION == 2
#if OS_MINOR_VERSION == 6
#define _XOPEN_SOURCE 600
#define HAVE_STRDUP
#else
	#error unknown platform
#endif /* defined OS_MINOR_VERSION == 6 */
#else
	#error unknown platform
#endif /* defined OS_MAJOR_VERSION == 2 */
#endif /* defined LINUX */

#if defined FREEBSD
#if OS_MAJOR_VERSION == 7
#if OS_MINOR_VERSION >= 0 && OS_MINOR_VERSION <= 2
#define _XOPEN_SOURCE 600
#define HAVE_STRDUP
#else
	#error unknown platform
#endif /* defined OS_MINOR_VERSION >= 0 && OS_MINOR_VERSION <= 2 */
#else
#if OS_MAJOR_VERSION == 6
#if OS_MINOR_VERSION == 2
#define _XOPEN_SOURCE 600
#define HAVE_STRDUP
#else
	#error unknown platform
#endif /* defined OS_MINOR_VERSION == 2 */
#else
	#error unknown platform
#endif /* defined OS_MAJOR_VERSION == 6 */
#endif /* defined OS_MAJOR_VERSION == 7 */
#endif /* defined FREEBSD */

#if defined OPENBSD
#if OS_MAJOR_VERSION == 4
#if OS_MINOR_VERSION >= 2 && OS_MINOR_VERSION <= 5
#define _XOPEN_SOURCE 600
#define HAVE_STRDUP
#else
	#error unknown platform
#endif /* defined OS_MINOR_VERSION >= 2 && OS_MINOR_VERSION <= 3 */
#else
	#error unknown platform
#endif /* defined OS_MAJOR_VERSION == 4 */
#endif /* defined OPENBSD */

#if defined NETBSD
#if OS_MAJOR_VERSION == 5
#if OS_MINOR_VERSION == 0
/* don't enable XOPEN_SOURCE here, we get compatibility problems
 * with libstdc++: vgwscanf undefined
 */
#define HAVE_STRDUP
#else
	#error unknown platform
#endif /* defined OS_MINOR_VERSION == 2 */
#else /* defined OS_MAJOR_VERSION == 4 */

#if OS_MAJOR_VERSION == 4
#if OS_MINOR_VERSION == 0
#define _XOPEN_SOURCE 600
#define HAVE_STRDUP
#else
	#error unknown platform
#endif /* defined OS_MINOR_VERSION == 2 */
#else
	#error unknown platform
#endif /* defined OS_MAJOR_VERSION == 4 */
#endif /* defined OS_MAJOR_VERSION == 5 */
#endif /* defined NETBSD */

#if defined SUNOS
#if OS_MAJOR_VERSION == 5
#if OS_MINOR_VERSION == 8
#if !defined __cplusplus
#define _XOPEN_SOURCE 600
#define __EXTENSIONS__
#endif
#define HAVE_STRDUP
#else
#if OS_MINOR_VERSION == 10
#if !defined __cplusplus 
#define _XOPEN_SOURCE 600
#define __EXTENSIONS__
#endif
#define HAVE_STRDUP
#else
	#error unknown platform
#endif /* OS_MINOR_VERSION == 10 */
#endif /* OS_MINOR_VERSION == 8 */
#else
	#error unknown platform
#endif /* OS_MAJOR_VERSION == 5 */
#endif /* defined SUNOS */

#if defined CYGWIN
#if OS_MAJOR_VERSION == 5
#if OS_MINOR_VERSION >= 0 && OS_MINOR_VERSION <= 1
#define _XOPEN_SOURCE 600
#else
	#error unknown platform
#endif /* OS_MINOR_VERSION >= 0 && OS_MINOR_VERSION <= 1 */
#else
	#error unknown platform
#endif /* OS_MAJOR_VERSION == 5 */
#endif /* defined CYGWIN */

#endif /* ifndef SQLITE3XX_SYS_INTERNAL_H */
