/*	$OpenBSD: sha2.h,v 1.9 2013/04/15 15:54:17 millert Exp $	*/

/*
 * FILE:	sha2.h
 * AUTHOR:	Aaron D. Gifford <me@aarongifford.com>
 * 
 * Copyright (c) 2000-2001, Aaron D. Gifford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTOR(S) ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTOR(S) BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $From: sha2.h,v 1.1 2001/11/08 00:02:01 adg Exp adg $
 */

#ifndef _PYBC_SHA2_H
#define _PYBC_SHA2_H

/*** SHA-256/384/512 Various Length Definitions ***********************/
#define PYBC_SHA512_BLOCK_LENGTH		128
#define PYBC_SHA512_DIGEST_LENGTH		64
#define PYBC_SHA512_DIGEST_STRING_LENGTH	(PYBC_SHA512_DIGEST_LENGTH * 2 + 1)


/*** SHA-224/256/384/512 Context Structure *******************************/
typedef struct _PYBC_SHA2_CTX {
	union {
		u_int32_t	st32[8];
		u_int64_t	st64[8];
	} state;
	u_int64_t	bitcount[2];
	u_int8_t	buffer[PYBC_SHA512_BLOCK_LENGTH];
} PYBC_SHA2_CTX;

void PYBC_SHA512Init(PYBC_SHA2_CTX *);
void PYBC_SHA512Transform(u_int64_t state[8], const u_int8_t [PYBC_SHA512_BLOCK_LENGTH]);
void PYBC_SHA512Update(PYBC_SHA2_CTX *, const u_int8_t *, size_t);
void PYBC_SHA512Pad(PYBC_SHA2_CTX *);
void PYBC_SHA512Final(u_int8_t [PYBC_SHA512_DIGEST_LENGTH], PYBC_SHA2_CTX *);
char *PYBC_SHA512End(PYBC_SHA2_CTX *, char *);

#endif /* _PYBC_SHA2_H */
