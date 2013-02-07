/*
 * %CopyrightBegin%
 * 
 * Copyright Ericsson AB 2005-2011. All Rights Reserved.
 * 
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 * 
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 * 
 * %CopyrightEnd%
 */

#ifndef ERL_PRINTF_FORMAT_H__
#define ERL_PRINTF_FORMAT_H__

#ifdef VXWORKS
#include <vxWorks.h>
#endif

#include "erl_int_sizes_config.h"
#if !((SIZEOF_VOID_P >= 4) && (SIZEOF_VOID_P == SIZEOF_SIZE_T) \
      && ((SIZEOF_VOID_P == SIZEOF_INT) || (SIZEOF_VOID_P == SIZEOF_LONG) || \
          (SIZEOF_VOID_P == SIZEOF_LONG_LONG)))
#error Cannot handle this combination of int/long/void*/size_t sizes
#endif

#if SIZEOF_VOID_P != SIZEOF_SIZE_T
#error sizeof(void*) != sizeof(size_t)
#endif

#if HALFWORD_HEAP

#if SIZEOF_INT == 4
typedef unsigned int ErlPfEterm;
typedef unsigned int ErlPfUint;
typedef int          ErlPfSint;
#else
#error Found no appropriate type to use for 'Eterm', 'Uint' and 'Sint'
#endif

#else /* !HALFWORD_HEAP */

#if SIZEOF_VOID_P == SIZEOF_LONG
typedef unsigned long ErlPfEterm;
typedef unsigned long ErlPfUint;
typedef long          ErlPfSint;
#elif SIZEOF_VOID_P == SIZEOF_INT
typedef unsigned int ErlPfEterm;
typedef unsigned int ErlPfUint;
typedef int          ErlPfSint;
#elif SIZEOF_VOID_P == SIZEOF_LONG_LONG
typedef unsigned long long ErlPfEterm;
typedef unsigned long long ErlPfUint;
typedef long long          ErlPfSint;
#else
#error Found no appropriate type to use for 'Eterm', 'Uint' and 'Sint'
#endif

#endif /* HALFWORD_HEAP */

#include <sys/types.h>
#include <stdarg.h>
#include <stdlib.h>

typedef int (*fmtfn_t)(void*, char*, size_t);

extern int erts_printf_format(fmtfn_t, void*, char*, va_list);

extern int erts_printf_char(fmtfn_t, void*, char);
extern int erts_printf_string(fmtfn_t, void*, char *);
extern int erts_printf_buf(fmtfn_t, void*, char *, size_t);
extern int erts_printf_pointer(fmtfn_t, void*, void *);
extern int erts_printf_uint(fmtfn_t, void*, char, int, int, ErlPfUint);
extern int erts_printf_sint(fmtfn_t, void*, char, int, int, ErlPfSint);
extern int erts_printf_double(fmtfn_t, void *, char, int, int, double);

extern int (*erts_printf_eterm_func)(fmtfn_t, void*, ErlPfEterm, long, ErlPfEterm*);


#endif

