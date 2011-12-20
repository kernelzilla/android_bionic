/*	$NetBSD: getprotoent.c,v 1.12 2008/04/28 20:23:00 martin Exp $	*/

/*-
 * Copyright (c) 2004 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <sys/cdefs.h>
#include "reentrant.h"
#include <netdb.h>
#include "protoent.h"
#include <util.h>


#ifdef _REENTRANT
mutex_t _protoent_mutex = MUTEX_INITIALIZER;
#endif
struct protoent_data _protoent_data;

void
setprotoent(int f)
{
	mutex_lock(&_protoent_mutex);
	setprotoent_r(f, &_protoent_data);
	mutex_unlock(&_protoent_mutex);
}

void
endprotoent(void)
{
	mutex_lock(&_protoent_mutex);
	endprotoent_r(&_protoent_data);
	mutex_unlock(&_protoent_mutex);
}

struct protoent *
getprotoent(void)
{
	struct protoent *p;

	mutex_lock(&_protoent_mutex);
	p = getprotoent_r(&_protoent_data.proto, &_protoent_data);
	mutex_unlock(&_protoent_mutex);
	return (p);
}
