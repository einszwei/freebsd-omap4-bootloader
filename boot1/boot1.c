/*-
 * Copyright (c) 2015
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <boot1.h>
#include <io.h>
#include <omap4/hw.h>

void
memtest(void *x, unsigned count)
{
	unsigned *w = x;
	unsigned n;
	count /= 4;

	printf("memtest write - %d\n", count);
	for (n = 0; n < count; n++) {
		unsigned chk = 0xa5a5a5a5 ^ n;
		w[n] = chk;
	}
	printf("memtest read\n");
	for (n = 0; n < count; n++) {
		unsigned chk = 0xa5a5a5a5 ^ n;
		if (w[n] != chk) {
			printf("ERROR @ %x (%x != %x)\n",
				(unsigned) (w+n), w[n], chk);
			return;
		}
	}
	printf("OK!\n");
}

void
boot1(void)
{
	if (warm_reset())
		force_emif_self_refresh();

	mux_init();
	enable_uart_clocks();
	serial_init();
	scale_vcores();
	clock_init();
	sdram_init();

	printf("boot1\n");
	printf("MLO\n");

	memtest((void *)0x82000000, 8*1024*1024);
	memtest((void *)0xA0208000, 8*1024*1024);
}
