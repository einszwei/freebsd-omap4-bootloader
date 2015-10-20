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

#include <sys/types.h>
#include <sys/stddef.h>

#include <io.h>
//#include <i2c.h>
#include <gpio.h>
#include <omap4/omap4.h>
#include <omap4/omap_data.h>
#include <omap4/omap_gpio.h>
#include <omap4/clock.h>
#include <omap4/platform.h>
//#include <omap4/omap_gpio.h>
#include <omap4/emif.h>

const uint32_t sys_clk_array[8] = {
	12000000,	/* 12 MHz */
	20000000,	/* 20 MHz */
	16800000,	/* 16.8 MHz */
	19200000,	/* 19.2 MHz */
	26000000,	/* 26 MHz */
	27000000,	/* 27 MHz */
	38400000,	/* 38.4 MHz */
};

uint32_t
get_sys_clk_index(void)
{
	int8_t ind;
	/*
	 * For ES1 the ROM code calibration of sys clock is not reliable
	 * due to hw issue. So, use hard-coded value. If this value is not
	 * correct for any board over-ride this function in board file
	 * From ES2.0 onwards you will get this information from
	 * CM_SYS_CLKSEL
	 */
	if (omap_revision() == OMAP4430_ES1_0)
		ind = OMAP_SYS_CLK_IND_38_4_MHZ;
	else {
		/* SYS_CLKSEL - 1 to match the dpll param array indices */
		ind = (readl((*prcm)->cm_sys_clksel) &
			CM_SYS_CLKSEL_SYS_CLKSEL_MASK) - 1;
	}
	return ind;
}

uint32_t
get_sys_clk_freq(void)
{
	uint8_t index = get_sys_clk_index();
	return sys_clk_array[index];
}

void
setup_post_dividers(uint32_t const base, const struct dpll_params *params)
{
	struct dpll_regs *const dpll_regs = (struct dpll_regs *)base;

	/* Setup post-dividers */
	if (params->m2 >= 0)
		writel(params->m2, &dpll_regs->cm_div_m2_dpll);
	if (params->m3 >= 0)
		writel(params->m3, &dpll_regs->cm_div_m3_dpll);
	if (params->m4_h11 >= 0)
		writel(params->m4_h11, &dpll_regs->cm_div_m4_h11_dpll);
	if (params->m5_h12 >= 0)
		writel(params->m5_h12, &dpll_regs->cm_div_m5_h12_dpll);
	if (params->m6_h13 >= 0)
		writel(params->m6_h13, &dpll_regs->cm_div_m6_h13_dpll);
	if (params->m7_h14 >= 0)
		writel(params->m7_h14, &dpll_regs->cm_div_m7_h14_dpll);
	if (params->h21 >= 0)
		writel(params->h21, &dpll_regs->cm_div_h21_dpll);
	if (params->h22 >= 0)
		writel(params->h22, &dpll_regs->cm_div_h22_dpll);
	if (params->h23 >= 0)
		writel(params->h23, &dpll_regs->cm_div_h23_dpll);
	if (params->h24 >= 0)
		writel(params->h24, &dpll_regs->cm_div_h24_dpll);
}

static inline void
do_bypass_dpll(uint32_t const base)
{
	struct dpll_regs *dpll_regs = (struct dpll_regs *)base;

	clrsetbits_le32(&dpll_regs->cm_clkmode_dpll,
			CM_CLKMODE_DPLL_DPLL_EN_MASK,
			DPLL_EN_FAST_RELOCK_BYPASS <<
			CM_CLKMODE_DPLL_EN_SHIFT);
}

static inline void
wait_for_bypass(uint32_t const base)
{
	struct dpll_regs *const dpll_regs = (struct dpll_regs *)base;

	if (!wait_on_value(ST_DPLL_CLK_MASK, 0, &dpll_regs->cm_idlest_dpll,
				LDELAY)) {
		//printf("Bypassing DPLL failed %x\n", base);
	}
}

static inline void
do_lock_dpll(uint32_t const base)
{
	struct dpll_regs *const dpll_regs = (struct dpll_regs *)base;

	clrsetbits_le32(&dpll_regs->cm_clkmode_dpll,
		      CM_CLKMODE_DPLL_DPLL_EN_MASK,
		      DPLL_EN_LOCK << CM_CLKMODE_DPLL_EN_SHIFT);
}

static inline void
wait_for_lock(uint32_t const base)
{
	struct dpll_regs *const dpll_regs = (struct dpll_regs *)base;

	if (!wait_on_value(ST_DPLL_CLK_MASK, ST_DPLL_CLK_MASK,
		&dpll_regs->cm_idlest_dpll, LDELAY)) {
		//printf("DPLL locking failed for %x\n", base);
		hang();
	}
}

inline uint32_t
check_for_lock(uint32_t const base)
{
	struct dpll_regs *const dpll_regs = (struct dpll_regs *)base;
	uint32_t lock = readl(&dpll_regs->cm_idlest_dpll) & ST_DPLL_CLK_MASK;

	return lock;
}

const struct dpll_params *
get_mpu_dpll_params(struct dplls const *dpll_data)
{
	uint32_t sysclk_ind = get_sys_clk_index();
	return &dpll_data->mpu[sysclk_ind];
}

const struct dpll_params *
get_core_dpll_params(struct dplls const *dpll_data)
{
	uint32_t sysclk_ind = get_sys_clk_index();
	return &dpll_data->core[sysclk_ind];
}

const struct dpll_params *
get_per_dpll_params(struct dplls const *dpll_data)
{
	uint32_t sysclk_ind = get_sys_clk_index();
	return &dpll_data->per[sysclk_ind];
}

const struct dpll_params *
get_iva_dpll_params(struct dplls const *dpll_data)
{
	uint32_t sysclk_ind = get_sys_clk_index();
	return &dpll_data->iva[sysclk_ind];
}

const struct dpll_params *
get_usb_dpll_params(struct dplls const *dpll_data)
{
	uint32_t sysclk_ind = get_sys_clk_index();
	return &dpll_data->usb[sysclk_ind];
}

const struct dpll_params *
get_abe_dpll_params(struct dplls const *dpll_data)
{
	return dpll_data->abe;
}

static const struct dpll_params *
get_ddr_dpll_params
			(struct dplls const *dpll_data)
{
	uint32_t sysclk_ind = get_sys_clk_index();

	if (!dpll_data->ddr)
		return NULL;
	return &dpll_data->ddr[sysclk_ind];
}

static void
do_setup_dpll(uint32_t const base, const struct dpll_params *params,
				uint8_t lock, char *dpll)
{
	uint32_t temp, M, N;
	struct dpll_regs *const dpll_regs = (struct dpll_regs *)base;

	if (!params)
		return;

	temp = readl(&dpll_regs->cm_clksel_dpll);

	if (check_for_lock(base)) {
		/*
		 * The Dpll has already been locked by rom code using CH.
		 * Check if M,N are matching with Ideal nominal opp values.
		 * If matches, skip the rest otherwise relock.
		 */
		M = (temp & CM_CLKSEL_DPLL_M_MASK) >> CM_CLKSEL_DPLL_M_SHIFT;
		N = (temp & CM_CLKSEL_DPLL_N_MASK) >> CM_CLKSEL_DPLL_N_SHIFT;
		if ((M != (params->m)) || (N != (params->n))) {
		//	debug("\n %s Dpll locked, but not for ideal M = %d,"
		//		"N = %d values, current values are M = %d,"
		//		"N= %d" , dpll, params->m, params->n,
		//		M, N);
		} else {
			/* Dpll locked with ideal values for nominal opps. */
		//	debug("\n %s Dpll already locked with ideal"
		//				"nominal opp values", dpll);
			goto setup_post_dividers;
		}
	}

	bypass_dpll(base);

	/* Set M & N */
	temp &= ~CM_CLKSEL_DPLL_M_MASK;
	temp |= (params->m << CM_CLKSEL_DPLL_M_SHIFT) & CM_CLKSEL_DPLL_M_MASK;

	temp &= ~CM_CLKSEL_DPLL_N_MASK;
	temp |= (params->n << CM_CLKSEL_DPLL_N_SHIFT) & CM_CLKSEL_DPLL_N_MASK;

	writel(temp, &dpll_regs->cm_clksel_dpll);

	/* Lock */
	if (lock)
		do_lock_dpll(base);

setup_post_dividers:
	setup_post_dividers(base, params);

	/* Wait till the DPLL locks */
	if (lock)
		wait_for_lock(base);
}

uint32_t
omap_ddr_clk(void)
{
	uint32_t ddr_clk, sys_clk_khz, omap_rev, divider;
	const struct dpll_params *core_dpll_params;

	omap_rev = omap_revision();
	sys_clk_khz = get_sys_clk_freq() / 1000;

	core_dpll_params = get_core_dpll_params(*dplls_data);

//	debug("sys_clk %d\n ", sys_clk_khz * 1000);

	/* Find Core DPLL locked frequency first */
	ddr_clk = sys_clk_khz * 2 * core_dpll_params->m /
			(core_dpll_params->n + 1);

	if (omap_rev < OMAP5430_ES1_0) {
		/*
		 * DDR frequency is PHY_ROOT_CLK/2
		 * PHY_ROOT_CLK = Fdpll/2/M2
		 */
		divider = 4;
	} else {
		/*
		 * DDR frequency is PHY_ROOT_CLK
		 * PHY_ROOT_CLK = Fdpll/2/M2
		 */
		divider = 2;
	}

	ddr_clk = ddr_clk / divider / core_dpll_params->m2;
	ddr_clk *= 1000;	/* convert to Hz */
	//debug("ddr_clk %d\n ", ddr_clk);

	return ddr_clk;
}

/*
 * Lock MPU dpll
 *
 * Resulting MPU frequencies:
 * 4430 ES1.0	: 600 MHz
 * 4430 ES2.x	: 792 MHz (OPP Turbo)
 * 4460		: 920 MHz (OPP Turbo) - DCC disabled
 */
void
configure_mpu_dpll(void)
{
	const struct dpll_params *params;
	struct dpll_regs *mpu_dpll_regs;
	uint32_t omap_rev;
	omap_rev = omap_revision();

	/*
	 * DCC and clock divider settings for 4460.
	 * DCC is required, if more than a certain frequency is required.
	 * For, 4460 > 1GHZ.
	 *     5430 > 1.4GHZ.
	 */
	if ((omap_rev >= OMAP4460_ES1_0) && (omap_rev < OMAP5430_ES1_0)) {
		mpu_dpll_regs =
			(struct dpll_regs *)((*prcm)->cm_clkmode_dpll_mpu);
		bypass_dpll((*prcm)->cm_clkmode_dpll_mpu);
		clrbits_le32((*prcm)->cm_mpu_mpu_clkctrl,
			MPU_CLKCTRL_CLKSEL_EMIF_DIV_MODE_MASK);
		setbits_le32((*prcm)->cm_mpu_mpu_clkctrl,
			MPU_CLKCTRL_CLKSEL_ABE_DIV_MODE_MASK);
		clrbits_le32(&mpu_dpll_regs->cm_clksel_dpll,
			CM_CLKSEL_DCC_EN_MASK);
	}

	params = get_mpu_dpll_params(*dplls_data);

	do_setup_dpll((*prcm)->cm_clkmode_dpll_mpu, params, DPLL_LOCK, "mpu");
	//debug("MPU DPLL locked\n");
}

static void
setup_usb_dpll(void)
{
	const struct dpll_params *params;
	uint32_t sys_clk_khz, sd_div, num, den;

	sys_clk_khz = get_sys_clk_freq() / 1000;
	/*
	 * USB:
	 * USB dpll is J-type. Need to set DPLL_SD_DIV for jitter correction
	 * DPLL_SD_DIV = CEILING ([DPLL_MULT/(DPLL_DIV+1)]* CLKINP / 250)
	 *      - where CLKINP is sys_clk in MHz
	 * Use CLKINP in KHz and adjust the denominator accordingly so
	 * that we have enough accuracy and at the same time no overflow
	 */
	params = get_usb_dpll_params(*dplls_data);
	num = params->m * sys_clk_khz;
	den = (params->n + 1) * 250 * 1000;
	num += den - 1;
	sd_div = num / den;
	clrsetbits_le32((*prcm)->cm_clksel_dpll_usb,
			CM_CLKSEL_DPLL_DPLL_SD_DIV_MASK,
			sd_div << CM_CLKSEL_DPLL_DPLL_SD_DIV_SHIFT);

	/* Now setup the dpll with the regular function */
	do_setup_dpll((*prcm)->cm_clkmode_dpll_usb, params, DPLL_LOCK, "usb");
}

static void
setup_dplls(void)
{
	uint32_t temp;
	const struct dpll_params *params;

	//debug("setup_dplls\n");

	/* CORE dpll */
	params = get_core_dpll_params(*dplls_data);	/* default - safest */
	/*
	 * Do not lock the core DPLL now. Just set it up.
	 * Core DPLL will be locked after setting up EMIF
	 * using the FREQ_UPDATE method(freq_update_core())
	 */
	if (emif_sdram_type() == EMIF_SDRAM_TYPE_LPDDR2)
		do_setup_dpll((*prcm)->cm_clkmode_dpll_core, params,
							DPLL_NO_LOCK, "core");
	else
		do_setup_dpll((*prcm)->cm_clkmode_dpll_core, params,
							DPLL_LOCK, "core");
	/* Set the ratios for CORE_CLK, L3_CLK, L4_CLK */
	temp = (CLKSEL_CORE_X2_DIV_1 << CLKSEL_CORE_SHIFT) |
	    (CLKSEL_L3_CORE_DIV_2 << CLKSEL_L3_SHIFT) |
	    (CLKSEL_L4_L3_DIV_2 << CLKSEL_L4_SHIFT);
	writel(temp, (*prcm)->cm_clksel_core);
	//debug("Core DPLL configured\n");

	/* lock PER dpll */
	params = get_per_dpll_params(*dplls_data);
	do_setup_dpll((*prcm)->cm_clkmode_dpll_per,
			params, DPLL_LOCK, "per");
	//debug("PER DPLL locked\n");

	/* MPU dpll */
	configure_mpu_dpll();

	setup_usb_dpll();
	params = get_ddr_dpll_params(*dplls_data);
	do_setup_dpll((*prcm)->cm_clkmode_dpll_ddrphy,
		      params, DPLL_LOCK, "ddr");
}

uint32_t
get_offset_code(uint32_t volt_offset, struct pmic_data *pmic)
{
	uint32_t offset_code;

	volt_offset -= pmic->base_offset;

	offset_code = (volt_offset + pmic->step - 1) / pmic->step;

	/*
	 * Offset codes 1-6 all give the base voltage in Palmas
	 * Offset code 0 switches OFF the SMPS
	 */
	return offset_code + pmic->start_code;
}

void
do_scale_vcore(uint32_t vcore_reg, uint32_t volt_mv, struct pmic_data *pmic)
{
	uint32_t offset_code;
	uint32_t offset = volt_mv;
	int ret = 0;

	if (!volt_mv)
		return;

	pmic->pmic_bus_init();
	/* See if we can first get the GPIO if needed */
	if (pmic->gpio_en)
		ret = gpio_request(pmic->gpio, "PMIC_GPIO");

	if (ret < 0) {
		//printf("%s: gpio %d request failed %d\n", __func__,
		//					pmic->gpio, ret);
		return;
	}

	/* Pull the GPIO low to select SET0 register, while we program SET1 */
	if (pmic->gpio_en)
		gpio_direction_output(pmic->gpio, 0);

	/* convert to uV for better accuracy in the calculations */
	offset *= 1000;

	offset_code = get_offset_code(offset, pmic);

	//debug("do_scale_vcore: volt - %d offset_code - 0x%x\n", volt_mv,
//		offset_code);

	if (pmic->pmic_write(pmic->i2c_slave_addr, vcore_reg, offset_code))
		//printf("Scaling voltage failed for 0x%x\n", vcore_reg);

	if (pmic->gpio_en)
		gpio_direction_output(pmic->gpio, 1);
}

static uint32_t
optimize_vcore_voltage(struct volts const *v)
{
	uint32_t val;
	if (!v->value)
		return 0;
	if (!v->efuse.reg)
		return v->value;

	switch (v->efuse.reg_bits) {
	case 16:
		val = readw(v->efuse.reg);
		break;
	case 32:
		val = readl(v->efuse.reg);
		break;
	default:
		//printf("Error: efuse 0x%08x bits=%d unknown\n",
		//v->efuse.reg, v->efuse.reg_bits);
		return v->value;
	}

	if (!val) {
		//printf("Error: efuse 0x%08x bits=%d val=0, using %d\n",
		//v->efuse.reg, v->efuse.reg_bits, v->value);
		return v->value;
	}

	//debug("%s:efuse 0x%08x bits=%d Vnom=%d, using efuse value %d\n",
	  //    __func__, v->efuse.reg, v->efuse.reg_bits, v->value, val);
	return val;
}

/*
 * Setup the voltages for vdd_mpu, vdd_core, and vdd_iva
 * We set the maximum voltages allowed here because Smart-Reflex is not
 * enabled in bootloader. Voltage initialization in the kernel will set
 * these to the nominal values after enabling Smart-Reflex
 */
void
scale_vcores(struct vcores_data const *vcores)
{
	uint32_t val;

	val = optimize_vcore_voltage(&vcores->core);
	do_scale_vcore(vcores->core.addr, val, vcores->core.pmic);

	val = optimize_vcore_voltage(&vcores->mpu);
	do_scale_vcore(vcores->mpu.addr, val, vcores->mpu.pmic);

	/* Configure MPU ABB LDO after scale */
	abb_setup((*ctrl)->control_std_fuse_opp_vdd_mpu_2,
		  (*ctrl)->control_wkup_ldovbb_mpu_voltage_ctrl,
		  (*prcm)->prm_abbldo_mpu_setup,
		  (*prcm)->prm_abbldo_mpu_ctrl,
		  (*prcm)->prm_irqstatus_mpu_2,
		  OMAP_ABB_MPU_TXDONE_MASK,
		  OMAP_ABB_FAST_OPP);

	val = optimize_vcore_voltage(&vcores->mm);
	do_scale_vcore(vcores->mm.addr, val, vcores->mm.pmic);

	val = optimize_vcore_voltage(&vcores->gpu);
	do_scale_vcore(vcores->gpu.addr, val, vcores->gpu.pmic);

	val = optimize_vcore_voltage(&vcores->eve);
	do_scale_vcore(vcores->eve.addr, val, vcores->eve.pmic);

	val = optimize_vcore_voltage(&vcores->iva);
	do_scale_vcore(vcores->iva.addr, val, vcores->iva.pmic);
}

static inline void
enable_clock_domain(uint32_t const clkctrl_reg, uint32_t enable_mode)
{
	clrsetbits_le32(clkctrl_reg, CD_CLKCTRL_CLKTRCTRL_MASK,
			enable_mode << CD_CLKCTRL_CLKTRCTRL_SHIFT);
	//debug("Enable clock domain - %x\n", clkctrl_reg);
}

static inline void
wait_for_clk_enable(uint32_t clkctrl_addr)
{
	uint32_t clkctrl, idlest = MODULE_CLKCTRL_IDLEST_DISABLED;
	uint32_t bound = LDELAY;

	while ((idlest == MODULE_CLKCTRL_IDLEST_DISABLED) ||
		(idlest == MODULE_CLKCTRL_IDLEST_TRANSITIONING)) {

		clkctrl = readl(clkctrl_addr);
		idlest = (clkctrl & MODULE_CLKCTRL_IDLEST_MASK) >>
			 MODULE_CLKCTRL_IDLEST_SHIFT;
		if (--bound == 0) {
			//printf("Clock enable failed for 0x%x idlest 0x%x\n",
				//clkctrl_addr, clkctrl);
			return;
		}
	}
}

static inline void
enable_clock_module(uint32_t const clkctrl_addr, uint32_t enable_mode,
				uint32_t wait_for_enable)
{
	clrsetbits_le32(clkctrl_addr, MODULE_CLKCTRL_MODULEMODE_MASK,
			enable_mode << MODULE_CLKCTRL_MODULEMODE_SHIFT);
	//debug("Enable clock module - %x\n", clkctrl_addr);
	if (wait_for_enable)
		wait_for_clk_enable(clkctrl_addr);
}

void
freq_update_core(void)
{
	uint32_t freq_config1 = 0;
	const struct dpll_params *core_dpll_params;
	uint32_t omap_rev = omap_revision();

	core_dpll_params = get_core_dpll_params(*dplls_data);
	/* Put EMIF clock domain in sw wakeup mode */
	enable_clock_domain((*prcm)->cm_memif_clkstctrl,
				CD_CLKCTRL_CLKTRCTRL_SW_WKUP);
	wait_for_clk_enable((*prcm)->cm_memif_emif_1_clkctrl);
	wait_for_clk_enable((*prcm)->cm_memif_emif_2_clkctrl);

	freq_config1 = SHADOW_FREQ_CONFIG1_FREQ_UPDATE_MASK |
	    SHADOW_FREQ_CONFIG1_DLL_RESET_MASK;

	freq_config1 |= (DPLL_EN_LOCK << SHADOW_FREQ_CONFIG1_DPLL_EN_SHIFT) &
				SHADOW_FREQ_CONFIG1_DPLL_EN_MASK;

	freq_config1 |= (core_dpll_params->m2 <<
			SHADOW_FREQ_CONFIG1_M2_DIV_SHIFT) &
			SHADOW_FREQ_CONFIG1_M2_DIV_MASK;

	writel(freq_config1, (*prcm)->cm_shadow_freq_config1);
	if (!wait_on_value(SHADOW_FREQ_CONFIG1_FREQ_UPDATE_MASK, 0,
			(uint32_t *) (*prcm)->cm_shadow_freq_config1, LDELAY)) {
		//puts("FREQ UPDATE procedure failed!!");
		hang();
	}

	/*
	 * Putting EMIF in HW_AUTO is seen to be causing issues with
	 * EMIF clocks and the master DLL. Keep EMIF in SW_WKUP
	 * in OMAP5430 ES1.0 silicon
	 */
	if (omap_rev != OMAP5430_ES1_0) {
		/* Put EMIF clock domain back in hw auto mode */
		enable_clock_domain((*prcm)->cm_memif_clkstctrl,
					CD_CLKCTRL_CLKTRCTRL_HW_AUTO);
		wait_for_clk_enable((*prcm)->cm_memif_emif_1_clkctrl);
		wait_for_clk_enable((*prcm)->cm_memif_emif_2_clkctrl);
	}
}

void
bypass_dpll(uint32_t const base)
{
	do_bypass_dpll(base);
	wait_for_bypass(base);
}

void
lock_dpll(uint32_t const base)
{
	do_lock_dpll(base);
	wait_for_lock(base);
}

void
setup_clocks_for_console(void)
{
	/* Do not add any spl_debug prints in this function */
	clrsetbits_le32((*prcm)->cm_l4per_clkstctrl, CD_CLKCTRL_CLKTRCTRL_MASK,
			CD_CLKCTRL_CLKTRCTRL_SW_WKUP <<
			CD_CLKCTRL_CLKTRCTRL_SHIFT);

	/* Enable all UARTs - console will be on one of them */
	clrsetbits_le32((*prcm)->cm_l4per_uart1_clkctrl,
			MODULE_CLKCTRL_MODULEMODE_MASK,
			MODULE_CLKCTRL_MODULEMODE_SW_EXPLICIT_EN <<
			MODULE_CLKCTRL_MODULEMODE_SHIFT);

	clrsetbits_le32((*prcm)->cm_l4per_uart2_clkctrl,
			MODULE_CLKCTRL_MODULEMODE_MASK,
			MODULE_CLKCTRL_MODULEMODE_SW_EXPLICIT_EN <<
			MODULE_CLKCTRL_MODULEMODE_SHIFT);

	clrsetbits_le32((*prcm)->cm_l4per_uart3_clkctrl,
			MODULE_CLKCTRL_MODULEMODE_MASK,
			MODULE_CLKCTRL_MODULEMODE_SW_EXPLICIT_EN <<
			MODULE_CLKCTRL_MODULEMODE_SHIFT);

	clrsetbits_le32((*prcm)->cm_l4per_uart4_clkctrl,
			MODULE_CLKCTRL_MODULEMODE_MASK,
			MODULE_CLKCTRL_MODULEMODE_SW_EXPLICIT_EN <<
			MODULE_CLKCTRL_MODULEMODE_SHIFT);

	clrsetbits_le32((*prcm)->cm_l4per_clkstctrl, CD_CLKCTRL_CLKTRCTRL_MASK,
			CD_CLKCTRL_CLKTRCTRL_HW_AUTO <<
			CD_CLKCTRL_CLKTRCTRL_SHIFT);
}

void
do_enable_clocks(uint32_t const *clk_domains,
			    uint32_t const *clk_modules_hw_auto,
			    uint32_t const *clk_modules_explicit_en,
			    uint8_t wait_for_enable)
{
	uint32_t i, max = 100;

	/* Put the clock domains in SW_WKUP mode */
	for (i = 0; (i < max) && clk_domains[i]; i++) {
		enable_clock_domain(clk_domains[i],
				    CD_CLKCTRL_CLKTRCTRL_SW_WKUP);
	}

	/* Clock modules that need to be put in HW_AUTO */
	for (i = 0; (i < max) && clk_modules_hw_auto[i]; i++) {
		enable_clock_module(clk_modules_hw_auto[i],
				    MODULE_CLKCTRL_MODULEMODE_HW_AUTO,
				    wait_for_enable);
	};

	/* Clock modules that need to be put in SW_EXPLICIT_EN mode */
	for (i = 0; (i < max) && clk_modules_explicit_en[i]; i++) {
		enable_clock_module(clk_modules_explicit_en[i],
				    MODULE_CLKCTRL_MODULEMODE_SW_EXPLICIT_EN,
				    wait_for_enable);
	};

	/* Put the clock domains in HW_AUTO mode now */
	for (i = 0; (i < max) && clk_domains[i]; i++) {
		enable_clock_domain(clk_domains[i],
				    CD_CLKCTRL_CLKTRCTRL_HW_AUTO);
	}
}

void
prcm_init(void)
{
	enable_basic_clocks();
	timer_init();
	scale_vcores(*omap_vcores);
	setup_dplls();

//	if (OMAP_INIT_CONTEXT_SPL != omap_hw_init_context())
//		enable_basic_uboot_clocks();
}
/*
void
gpi2c_init(void)
{
	static int gpi2c = 1;

	if (gpi2c) {
		i2c_init(CONFIG_SYS_OMAP24_I2C_SPEED,
			 CONFIG_SYS_OMAP24_I2C_SLAVE);
		gpi2c = 0;
	}
}
*/

