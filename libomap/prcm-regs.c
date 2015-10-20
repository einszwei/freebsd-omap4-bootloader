
#include <omap4/omap_data.h>

struct prcm_regs const omap4_prcm = {
	/* cm1.ckgen */
	.cm_clksel_core  = 0x4a004100,
	.cm_clksel_abe = 0x4a004108,
	.cm_dll_ctrl = 0x4a004110,
	.cm_clkmode_dpll_core = 0x4a004120,
	.cm_idlest_dpll_core = 0x4a004124,
	.cm_autoidle_dpll_core = 0x4a004128,
	.cm_clksel_dpll_core = 0x4a00412c,
	.cm_div_m2_dpll_core = 0x4a004130,
	.cm_div_m3_dpll_core = 0x4a004134,
	.cm_div_m4_dpll_core = 0x4a004138,
	.cm_div_m5_dpll_core = 0x4a00413c,
	.cm_div_m6_dpll_core = 0x4a004140,
	.cm_div_m7_dpll_core = 0x4a004144,
	.cm_ssc_deltamstep_dpll_core = 0x4a004148,
	.cm_ssc_modfreqdiv_dpll_core = 0x4a00414c,
	.cm_emu_override_dpll_core = 0x4a004150,
	.cm_clkmode_dpll_mpu = 0x4a004160,
	.cm_idlest_dpll_mpu = 0x4a004164,
	.cm_autoidle_dpll_mpu = 0x4a004168,
	.cm_clksel_dpll_mpu = 0x4a00416c,
	.cm_div_m2_dpll_mpu = 0x4a004170,
	.cm_ssc_deltamstep_dpll_mpu = 0x4a004188,
	.cm_ssc_modfreqdiv_dpll_mpu = 0x4a00418c,
	.cm_bypclk_dpll_mpu = 0x4a00419c,
	.cm_clkmode_dpll_iva = 0x4a0041a0,
	.cm_idlest_dpll_iva = 0x4a0041a4,
	.cm_autoidle_dpll_iva = 0x4a0041a8,
	.cm_clksel_dpll_iva = 0x4a0041ac,
	.cm_div_m4_dpll_iva = 0x4a0041b8,
	.cm_div_m5_dpll_iva = 0x4a0041bc,
	.cm_ssc_deltamstep_dpll_iva = 0x4a0041c8,
	.cm_ssc_modfreqdiv_dpll_iva = 0x4a0041cc,
	.cm_bypclk_dpll_iva = 0x4a0041dc,
	.cm_clkmode_dpll_abe = 0x4a0041e0,
	.cm_idlest_dpll_abe = 0x4a0041e4,
	.cm_autoidle_dpll_abe = 0x4a0041e8,
	.cm_clksel_dpll_abe = 0x4a0041ec,
	.cm_div_m2_dpll_abe = 0x4a0041f0,
	.cm_div_m3_dpll_abe = 0x4a0041f4,
	.cm_ssc_deltamstep_dpll_abe = 0x4a004208,
	.cm_ssc_modfreqdiv_dpll_abe = 0x4a00420c,
	.cm_clkmode_dpll_ddrphy = 0x4a004220,
	.cm_idlest_dpll_ddrphy = 0x4a004224,
	.cm_autoidle_dpll_ddrphy = 0x4a004228,
	.cm_clksel_dpll_ddrphy = 0x4a00422c,
	.cm_div_m2_dpll_ddrphy = 0x4a004230,
	.cm_div_m4_dpll_ddrphy = 0x4a004238,
	.cm_div_m5_dpll_ddrphy = 0x4a00423c,
	.cm_div_m6_dpll_ddrphy = 0x4a004240,
	.cm_ssc_deltamstep_dpll_ddrphy = 0x4a004248,
	.cm_shadow_freq_config1 = 0x4a004260,
	.cm_mpu_mpu_clkctrl = 0x4a004320,

	/* cm1.dsp */
	.cm_dsp_clkstctrl = 0x4a004400,
	.cm_dsp_dsp_clkctrl = 0x4a004420,

	/* cm1.abe */
	.cm1_abe_clkstctrl = 0x4a004500,
	.cm1_abe_l4abe_clkctrl = 0x4a004520,
	.cm1_abe_aess_clkctrl = 0x4a004528,
	.cm1_abe_pdm_clkctrl = 0x4a004530,
	.cm1_abe_dmic_clkctrl = 0x4a004538,
	.cm1_abe_mcasp_clkctrl = 0x4a004540,
	.cm1_abe_mcbsp1_clkctrl = 0x4a004548,
	.cm1_abe_mcbsp2_clkctrl = 0x4a004550,
	.cm1_abe_mcbsp3_clkctrl = 0x4a004558,
	.cm1_abe_slimbus_clkctrl = 0x4a004560,
	.cm1_abe_timer5_clkctrl = 0x4a004568,
	.cm1_abe_timer6_clkctrl = 0x4a004570,
	.cm1_abe_timer7_clkctrl = 0x4a004578,
	.cm1_abe_timer8_clkctrl = 0x4a004580,
	.cm1_abe_wdt3_clkctrl = 0x4a004588,

	/* cm2.ckgen */
	.cm_clksel_mpu_m3_iss_root = 0x4a008100,
	.cm_clksel_usb_60mhz = 0x4a008104,
	.cm_scale_fclk = 0x4a008108,
	.cm_core_dvfs_perf1 = 0x4a008110,
	.cm_core_dvfs_perf2 = 0x4a008114,
	.cm_core_dvfs_perf3 = 0x4a008118,
	.cm_core_dvfs_perf4 = 0x4a00811c,
	.cm_core_dvfs_current = 0x4a008124,
	.cm_iva_dvfs_perf_tesla = 0x4a008128,
	.cm_iva_dvfs_perf_ivahd = 0x4a00812c,
	.cm_iva_dvfs_perf_abe = 0x4a008130,
	.cm_iva_dvfs_current = 0x4a008138,
	.cm_clkmode_dpll_per = 0x4a008140,
	.cm_idlest_dpll_per = 0x4a008144,
	.cm_autoidle_dpll_per = 0x4a008148,
	.cm_clksel_dpll_per = 0x4a00814c,
	.cm_div_m2_dpll_per = 0x4a008150,
	.cm_div_m3_dpll_per = 0x4a008154,
	.cm_div_m4_dpll_per = 0x4a008158,
	.cm_div_m5_dpll_per = 0x4a00815c,
	.cm_div_m6_dpll_per = 0x4a008160,
	.cm_div_m7_dpll_per = 0x4a008164,
	.cm_ssc_deltamstep_dpll_per = 0x4a008168,
	.cm_ssc_modfreqdiv_dpll_per = 0x4a00816c,
	.cm_emu_override_dpll_per = 0x4a008170,
	.cm_clkmode_dpll_usb = 0x4a008180,
	.cm_idlest_dpll_usb = 0x4a008184,
	.cm_autoidle_dpll_usb = 0x4a008188,
	.cm_clksel_dpll_usb = 0x4a00818c,
	.cm_div_m2_dpll_usb = 0x4a008190,
	.cm_ssc_deltamstep_dpll_usb = 0x4a0081a8,
	.cm_ssc_modfreqdiv_dpll_usb = 0x4a0081ac,
	.cm_clkdcoldo_dpll_usb = 0x4a0081b4,
	.cm_clkmode_dpll_unipro = 0x4a0081c0,
	.cm_idlest_dpll_unipro = 0x4a0081c4,
	.cm_autoidle_dpll_unipro = 0x4a0081c8,
	.cm_clksel_dpll_unipro = 0x4a0081cc,
	.cm_div_m2_dpll_unipro = 0x4a0081d0,
	.cm_ssc_deltamstep_dpll_unipro = 0x4a0081e8,
	.cm_ssc_modfreqdiv_dpll_unipro = 0x4a0081ec,

	/* cm2.core */
	.cm_l3_1_clkstctrl = 0x4a008700,
	.cm_l3_1_dynamicdep = 0x4a008708,
	.cm_l3_1_l3_1_clkctrl = 0x4a008720,
	.cm_l3_2_clkstctrl = 0x4a008800,
	.cm_l3_2_dynamicdep = 0x4a008808,
	.cm_l3_2_l3_2_clkctrl = 0x4a008820,
	.cm_l3_gpmc_clkctrl = 0x4a008828,
	.cm_l3_2_ocmc_ram_clkctrl = 0x4a008830,
	.cm_mpu_m3_clkstctrl = 0x4a008900,
	.cm_mpu_m3_staticdep = 0x4a008904,
	.cm_mpu_m3_dynamicdep = 0x4a008908,
	.cm_mpu_m3_mpu_m3_clkctrl = 0x4a008920,
	.cm_sdma_clkstctrl = 0x4a008a00,
	.cm_sdma_staticdep = 0x4a008a04,
	.cm_sdma_dynamicdep = 0x4a008a08,
	.cm_sdma_sdma_clkctrl = 0x4a008a20,
	.cm_memif_clkstctrl = 0x4a008b00,
	.cm_memif_dmm_clkctrl = 0x4a008b20,
	.cm_memif_emif_fw_clkctrl = 0x4a008b28,
	.cm_memif_emif_1_clkctrl = 0x4a008b30,
	.cm_memif_emif_2_clkctrl = 0x4a008b38,
	.cm_memif_dll_clkctrl = 0x4a008b40,
	.cm_memif_emif_h1_clkctrl = 0x4a008b50,
	.cm_memif_emif_h2_clkctrl = 0x4a008b58,
	.cm_memif_dll_h_clkctrl = 0x4a008b60,
	.cm_c2c_clkstctrl = 0x4a008c00,
	.cm_c2c_staticdep = 0x4a008c04,
	.cm_c2c_dynamicdep = 0x4a008c08,
	.cm_c2c_sad2d_clkctrl = 0x4a008c20,
	.cm_c2c_modem_icr_clkctrl = 0x4a008c28,
	.cm_c2c_sad2d_fw_clkctrl = 0x4a008c30,
	.cm_l4cfg_clkstctrl = 0x4a008d00,
	.cm_l4cfg_dynamicdep = 0x4a008d08,
	.cm_l4cfg_l4_cfg_clkctrl = 0x4a008d20,
	.cm_l4cfg_hw_sem_clkctrl = 0x4a008d28,
	.cm_l4cfg_mailbox_clkctrl = 0x4a008d30,
	.cm_l4cfg_sar_rom_clkctrl = 0x4a008d38,
	.cm_l3instr_clkstctrl = 0x4a008e00,
	.cm_l3instr_l3_3_clkctrl = 0x4a008e20,
	.cm_l3instr_l3_instr_clkctrl = 0x4a008e28,
	.cm_l3instr_intrconn_wp1_clkct = 0x4a008e40,
	.cm_ivahd_clkstctrl = 0x4a008f00,

	/* cm2.ivahd */
	.cm_ivahd_ivahd_clkctrl = 0x4a008f20,
	.cm_ivahd_sl2_clkctrl = 0x4a008f28,

	/* cm2.cam */
	.cm_cam_clkstctrl = 0x4a009000,
	.cm_cam_iss_clkctrl = 0x4a009020,
	.cm_cam_fdif_clkctrl = 0x4a009028,

	/* cm2.dss */
	.cm_dss_clkstctrl = 0x4a009100,
	.cm_dss_dss_clkctrl = 0x4a009120,

	/* cm2.sgx */
	.cm_sgx_clkstctrl = 0x4a009200,
	.cm_sgx_sgx_clkctrl = 0x4a009220,

	/* cm2.l3init */
	.cm_l3init_clkstctrl = 0x4a009300,
	.cm_l3init_hsmmc1_clkctrl = 0x4a009328,
	.cm_l3init_hsmmc2_clkctrl = 0x4a009330,
	.cm_l3init_hsi_clkctrl = 0x4a009338,
	.cm_l3init_hsusbhost_clkctrl = 0x4a009358,
	.cm_l3init_hsusbotg_clkctrl = 0x4a009360,
	.cm_l3init_hsusbtll_clkctrl = 0x4a009368,
	.cm_l3init_p1500_clkctrl = 0x4a009378,
	.cm_l3init_fsusb_clkctrl = 0x4a0093d0,
	.cm_l3init_usbphy_clkctrl = 0x4a0093e0,

	/* cm2.l4per */
	.cm_l4per_clkstctrl = 0x4a009400,
	.cm_l4per_dynamicdep = 0x4a009408,
	.cm_l4per_adc_clkctrl = 0x4a009420,
	.cm_l4per_gptimer10_clkctrl = 0x4a009428,
	.cm_l4per_gptimer11_clkctrl = 0x4a009430,
	.cm_l4per_gptimer2_clkctrl = 0x4a009438,
	.cm_l4per_gptimer3_clkctrl = 0x4a009440,
	.cm_l4per_gptimer4_clkctrl = 0x4a009448,
	.cm_l4per_gptimer9_clkctrl = 0x4a009450,
	.cm_l4per_elm_clkctrl = 0x4a009458,
	.cm_l4per_gpio2_clkctrl = 0x4a009460,
	.cm_l4per_gpio3_clkctrl = 0x4a009468,
	.cm_l4per_gpio4_clkctrl = 0x4a009470,
	.cm_l4per_gpio5_clkctrl = 0x4a009478,
	.cm_l4per_gpio6_clkctrl = 0x4a009480,
	.cm_l4per_hdq1w_clkctrl = 0x4a009488,
	.cm_l4per_hecc1_clkctrl = 0x4a009490,
	.cm_l4per_hecc2_clkctrl = 0x4a009498,
	.cm_l4per_i2c1_clkctrl = 0x4a0094a0,
	.cm_l4per_i2c2_clkctrl = 0x4a0094a8,
	.cm_l4per_i2c3_clkctrl = 0x4a0094b0,
	.cm_l4per_i2c4_clkctrl = 0x4a0094b8,
	.cm_l4per_l4per_clkctrl = 0x4a0094c0,
	.cm_l4per_mcasp2_clkctrl = 0x4a0094d0,
	.cm_l4per_mcasp3_clkctrl = 0x4a0094d8,
	.cm_l4per_mcbsp4_clkctrl = 0x4a0094e0,
	.cm_l4per_mgate_clkctrl = 0x4a0094e8,
	.cm_l4per_mcspi1_clkctrl = 0x4a0094f0,
	.cm_l4per_mcspi2_clkctrl = 0x4a0094f8,
	.cm_l4per_mcspi3_clkctrl = 0x4a009500,
	.cm_l4per_mcspi4_clkctrl = 0x4a009508,
	.cm_l4per_mmcsd3_clkctrl = 0x4a009520,
	.cm_l4per_mmcsd4_clkctrl = 0x4a009528,
	.cm_l4per_msprohg_clkctrl = 0x4a009530,
	.cm_l4per_slimbus2_clkctrl = 0x4a009538,
	.cm_l4per_uart1_clkctrl = 0x4a009540,
	.cm_l4per_uart2_clkctrl = 0x4a009548,
	.cm_l4per_uart3_clkctrl = 0x4a009550,
	.cm_l4per_uart4_clkctrl = 0x4a009558,
	.cm_l4per_mmcsd5_clkctrl = 0x4a009560,
	.cm_l4per_i2c5_clkctrl = 0x4a009568,
	.cm_l4sec_clkstctrl = 0x4a009580,
	.cm_l4sec_staticdep = 0x4a009584,
	.cm_l4sec_dynamicdep = 0x4a009588,
	.cm_l4sec_aes1_clkctrl = 0x4a0095a0,
	.cm_l4sec_aes2_clkctrl = 0x4a0095a8,
	.cm_l4sec_des3des_clkctrl = 0x4a0095b0,
	.cm_l4sec_pkaeip29_clkctrl = 0x4a0095b8,
	.cm_l4sec_rng_clkctrl = 0x4a0095c0,
	.cm_l4sec_sha2md51_clkctrl = 0x4a0095c8,
	.cm_l4sec_cryptodma_clkctrl = 0x4a0095d8,

	/* l4 wkup regs */
	.cm_abe_pll_ref_clksel = 0x4a30610c,
	.cm_sys_clksel = 0x4a306110,
	.cm_wkup_clkstctrl = 0x4a307800,
	.cm_wkup_l4wkup_clkctrl = 0x4a307820,
	.cm_wkup_wdtimer1_clkctrl = 0x4a307828,
	.cm_wkup_wdtimer2_clkctrl = 0x4a307830,
	.cm_wkup_gpio1_clkctrl = 0x4a307838,
	.cm_wkup_gptimer1_clkctrl = 0x4a307840,
	.cm_wkup_gptimer12_clkctrl = 0x4a307848,
	.cm_wkup_synctimer_clkctrl = 0x4a307850,
	.cm_wkup_usim_clkctrl = 0x4a307858,
	.cm_wkup_sarram_clkctrl = 0x4a307860,
	.cm_wkup_keyboard_clkctrl = 0x4a307878,
	.cm_wkup_rtc_clkctrl = 0x4a307880,
	.cm_wkup_bandgap_clkctrl = 0x4a307888,
	.prm_vc_val_bypass = 0x4a307ba0,
	.prm_vc_cfg_channel = 0x4a307ba4,
	.prm_vc_cfg_i2c_mode = 0x4a307ba8,
	.prm_vc_cfg_i2c_clk = 0x4a307bac,
};

struct omap_sys_ctrl_regs const omap4_ctrl = {
	.control_id_code			= 0x4A002204,
	.control_std_fuse_opp_bgap		= 0x4a002260,
	.control_status				= 0x4a0022c4,
	.control_ldosram_iva_voltage_ctrl	= 0x4A002320,
	.control_ldosram_mpu_voltage_ctrl	= 0x4A002324,
	.control_ldosram_core_voltage_ctrl	= 0x4A002328,
	.control_usbotghs_ctrl			= 0x4A00233C,
	.control_padconf_core_base		= 0x4A100000,
	.control_pbiaslite			= 0x4A100600,
	.control_lpddr2io1_0			= 0x4A100638,
	.control_lpddr2io1_1			= 0x4A10063C,
	.control_lpddr2io1_2			= 0x4A100640,
	.control_lpddr2io1_3			= 0x4A100644,
	.control_lpddr2io2_0			= 0x4A100648,
	.control_lpddr2io2_1			= 0x4A10064C,
	.control_lpddr2io2_2			= 0x4A100650,
	.control_lpddr2io2_3			= 0x4A100654,
	.control_efuse_1			= 0x4A100700,
	.control_efuse_2			= 0x4A100704,
	.control_padconf_wkup_base		= 0x4A31E000,
};
