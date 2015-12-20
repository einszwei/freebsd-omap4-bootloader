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

#ifndef _OMAP4_MMCHS_H_
#define _OMAP4_MMCHS_H_

#define SOFTRESET			(0x1 << 1)
#define RESETDONE			(0x1 << 0)
#define NOOPENDRAIN			(0x0 << 0)
#define OPENDRAIN			(0x1 << 0)
#define OD				(0x1 << 0)
#define INIT_NOINIT			(0x0 << 1)
#define INIT_INITSTREAM			(0x1 << 1)
#define HR_NOHOSTRESP			(0x0 << 2)
#define STR_BLOCK			(0x0 << 3)
#define MODE_FUNC			(0x0 << 4)
#define DW8_1_4BITMODE			(0x0 << 5)
#define MIT_CTO				(0x0 << 6)
#define CDP_ACTIVEHIGH			(0x0 << 7)
#define WPP_ACTIVEHIGH			(0x0 << 8)
#define RESERVED_MASK			(0x3 << 9)
#define CTPL_MMC_SD			(0x0 << 11)
#define BLEN_512BYTESLEN		(0x200 << 0)
#define NBLK_STPCNT			(0x0 << 16)
#define DE_DISABLE			(0x0 << 0)
#define BCE_DISABLE			(0x0 << 1)
#define BCE_ENABLE			(0x1 << 1)
#define ACEN_DISABLE			(0x0 << 2)
#define DDIR_OFFSET			(4)
#define DDIR_MASK			(0x1 << 4)
#define DDIR_WRITE			(0x0 << 4)
#define DDIR_READ			(0x1 << 4)
#define MSBS_SGLEBLK			(0x0 << 5)
#define MSBS_MULTIBLK			(0x1 << 5)
#define RSP_TYPE_OFFSET			(16)
#define RSP_TYPE_MASK			(0x3 << 16)
#define RSP_TYPE_NORSP			(0x0 << 16)
#define RSP_TYPE_LGHT136		(0x1 << 16)
#define RSP_TYPE_LGHT48			(0x2 << 16)
#define RSP_TYPE_LGHT48B		(0x3 << 16)
#define CCCE_NOCHECK			(0x0 << 19)
#define CCCE_CHECK			(0x1 << 19)
#define CICE_NOCHECK			(0x0 << 20)
#define CICE_CHECK			(0x1 << 20)
#define DP_OFFSET			(21)
#define DP_MASK				(0x1 << 21)
#define DP_NO_DATA			(0x0 << 21)
#define DP_DATA				(0x1 << 21)
#define CMD_TYPE_NORMAL			(0x0 << 22)
#define INDEX_OFFSET			(24)
#define INDEX_MASK			(0x3f << 24)
#define INDEX(i)			(i << 24)
#define DATI_MASK			(0x1 << 1)
#define CMDI_MASK			(0x1 << 0)
#define DATI_CMDDIS			(0x1 << 1)
#define DTW_1_BITMODE			(0x0 << 1)
#define DTW_4_BITMODE			(0x1 << 1)
#define DTW_8_BITMODE                   (0x1 << 5) /* CON[DW8]*/
#define SDBP_PWROFF			(0x0 << 8)
#define SDBP_PWRON			(0x1 << 8)
#define SDVS_1V8			(0x5 << 9)
#define SDVS_3V0			(0x6 << 9)
#define ICE_MASK			(0x1 << 0)
#define ICE_STOP			(0x0 << 0)
#define ICS_MASK			(0x1 << 1)
#define ICS_NOTREADY			(0x0 << 1)
#define ICE_OSCILLATE			(0x1 << 0)
#define CEN_MASK			(0x1 << 2)
#define CEN_DISABLE			(0x0 << 2)
#define CEN_ENABLE			(0x1 << 2)
#define CLKD_OFFSET			(6)
#define CLKD_MASK			(0x3ff << 6)
#define DTO_MASK			(0xf << 16)
#define DTO_15THDTO			(0xe << 16)
#define SOFTRESETALL			(0x1 << 24)
#define CC_MASK				(0x1 << 0)
#define TC_MASK				(0x1 << 1)
#define BWR_MASK			(0x1 << 4)
#define BRR_MASK			(0x1 << 5)
#define ERRI_MASK			(0x1 << 15)
#define IE_CC				(0x01 << 0)
#define IE_TC				(0x01 << 1)
#define IE_BWR				(0x01 << 4)
#define IE_BRR				(0x01 << 5)
#define IE_CTO				(0x01 << 16)
#define IE_CCRC				(0x01 << 17)
#define IE_CEB				(0x01 << 18)
#define IE_CIE				(0x01 << 19)
#define IE_DTO				(0x01 << 20)
#define IE_DCRC				(0x01 << 21)
#define IE_DEB				(0x01 << 22)
#define IE_CERR				(0x01 << 28)
#define IE_BADA				(0x01 << 29)

#define RSP_TYPE_NONE		(RSP_TYPE_NORSP   | CCCE_NOCHECK | CICE_NOCHECK)
#define RSP_TYPE_R1		(RSP_TYPE_LGHT48  | CCCE_CHECK   | CICE_CHECK)
#define RSP_TYPE_R1B		(RSP_TYPE_LGHT48B | CCCE_CHECK   | CICE_CHECK)
#define RSP_TYPE_R2		(RSP_TYPE_LGHT136 | CCCE_CHECK   | CICE_NOCHECK)
#define RSP_TYPE_R3		(RSP_TYPE_LGHT48  | CCCE_NOCHECK | CICE_NOCHECK)
#define RSP_TYPE_R4		(RSP_TYPE_LGHT48  | CCCE_NOCHECK | CICE_NOCHECK)
#define RSP_TYPE_R5		(RSP_TYPE_LGHT48  | CCCE_CHECK   | CICE_CHECK)
#define RSP_TYPE_R6		(RSP_TYPE_LGHT48  | CCCE_CHECK   | CICE_CHECK)
#define RSP_TYPE_R7		(RSP_TYPE_LGHT48  | CCCE_CHECK   | CICE_CHECK)

#define MMC_CMD0	(INDEX(0)  | RSP_TYPE_NONE | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD1	(INDEX(1)  | RSP_TYPE_R3   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD2	(INDEX(2)  | RSP_TYPE_R2   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD3	(INDEX(3)  | RSP_TYPE_R1   | DP_NO_DATA | DDIR_WRITE)
#define MMC_SDCMD3	(INDEX(3)  | RSP_TYPE_R6   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD4	(INDEX(4)  | RSP_TYPE_NONE | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD6	(INDEX(6)  | RSP_TYPE_R1B  | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD7_SELECT	(INDEX(7)  | RSP_TYPE_R1B  | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD7_DESELECT \
	(INDEX(7)  | RSP_TYPE_NONE | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD8	(INDEX(8)  | RSP_TYPE_R1   | DP_DATA    | DDIR_READ)
#define MMC_SDCMD8	(INDEX(8)  | RSP_TYPE_R7   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD9	(INDEX(9)  | RSP_TYPE_R2   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD12	(INDEX(12) | RSP_TYPE_R1B  | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD13	(INDEX(13) | RSP_TYPE_R1   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD15	(INDEX(15) | RSP_TYPE_NONE | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD16	(INDEX(16) | RSP_TYPE_R1   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD17	(INDEX(17) | RSP_TYPE_R1   | DP_DATA    | DDIR_READ)
#define MMC_CMD24	(INDEX(24) | RSP_TYPE_R1   | DP_DATA    | DDIR_WRITE)

#define MMC_CMD23      (INDEX(23) | RSP_TYPE_R1   | DP_NO_DATA | DDIR_WRITE)
#define MMC_CMD25      (INDEX(25) | RSP_TYPE_R1   | DP_DATA    | DDIR_WRITE)

#define MMC_ACMD6	(INDEX(6)  | RSP_TYPE_R1   | DP_NO_DATA | DDIR_WRITE)
#define MMC_ACMD41	(INDEX(41) | RSP_TYPE_R3   | DP_NO_DATA | DDIR_WRITE)
#define MMC_ACMD51	(INDEX(51) | RSP_TYPE_R1   | DP_DATA    | DDIR_READ)
#define MMC_CMD55	(INDEX(55) | RSP_TYPE_R1   | DP_NO_DATA | DDIR_WRITE)

#define VS30_3V0SUP			(1 << 25)
#define VS18_1V8SUP			(1 << 26)

#define MMCSD_SECTOR_SIZE		512
#define MMC_CARD			0
#define SD_CARD				1
#define BYTE_MODE			0
#define SECTOR_MODE			1
#define CLK_INITSEQ			0
#define CLK_400KHZ			1
#define CLK_MISC			2

#define MMC_CLOCK_REFERENCE		(96)
#define MMC_RELATIVE_CARD_ADDRESS	(0x1234)
#define MMC_INIT_SEQ_CLK		(MMC_CLOCK_REFERENCE * 1000 / 80)
#define MMC_400kHz_CLK			(MMC_CLOCK_REFERENCE * 1000 / 400)
#define CLKDR(r, f, u)			( ( ((r)*100) / ((f)*(u)) ) + 1 )
#define CLKD(f, u)			(CLKDR(MMC_CLOCK_REFERENCE, f, u))

#define mmc_reg_out(addr, mask, val)\
	writel((readl(addr) & (~(mask))) | ((val) & (mask)), (addr))

struct mmchs {
	unsigned char res1[0x10];
	unsigned int sysconfig;		/* 0x10 */
	unsigned int sysstatus;		/* 0x14 */
	unsigned char res2[0x14];
	unsigned int con;		/* 0x2C */
	unsigned char res3[0xd4];
	unsigned int blk;		/* 0x104 */
	unsigned int arg;		/* 0x108 */
	unsigned int cmd;		/* 0x10C */
	unsigned int rsp10;		/* 0x110 */
	unsigned int rsp32;		/* 0x114 */
	unsigned int rsp54;		/* 0x118 */
	unsigned int rsp76;		/* 0x11C */
	unsigned int data;		/* 0x120 */
	unsigned int pstate;		/* 0x124 */
	unsigned int hctl;		/* 0x128 */
	unsigned int sysctl;		/* 0x12C */
	unsigned int stat;		/* 0x130 */
	unsigned int ie;		/* 0x134 */
	unsigned char res4[0x8];
	unsigned int capa;		/* 0x140 */
};

#endif /* !_OMAP4_MMCHS_H_ */
