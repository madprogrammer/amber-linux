/*
 *  linux/arch/arm/mm/proc-amber.S: utility functions for Amber Processor core
 *
 *  Copyright (C) 2003-2006 Hyok S. Choi <hyok.choi@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/linkage.h>
#include <linux/init.h>
#include <asm/assembler.h>
#include <asm/asm-offsets.h>
#include <asm/hwcap.h>
#include <asm/pgtable-hwdef.h>
#include <asm/pgtable.h>
#include <asm/ptrace.h>

#include "proc-macros.S"

	.text
/*
 * cpu_amber_proc_init()
 * cpu_amber_do_idle():
 * cpu_amber_dcache_clean_area()
 * cpu_amber_switch_mm()
 *
 * These are not required.
 */
ENTRY(cpu_amber_proc_init)
ENTRY(cpu_amber_do_idle)
ENTRY(cpu_amber_dcache_clean_area)
ENTRY(cpu_amber_switch_mm)
		ret	lr

/*
 * cpu_amber_proc_fin()
 */
ENTRY(cpu_amber_proc_fin)
		ret	lr

/*
 * Function: cpu_amber_reset(loc)
 * Params  : loc(r0)	address to jump to
 * Purpose : Sets up everything for a reset and jump to the location for soft reset.
 */
		.pushsection	.idmap.text, "ax"
ENTRY(cpu_amber_reset)
		ret	r0
ENDPROC(cpu_amber_reset)
		.popsection

		.type	__amber_setup, #function
__amber_setup:
		ret	lr
		.size	__amber_setup, . - __amber_setup

		__INITDATA

		@ define struct processor (see <asm/proc-fns.h> and proc-macros.S)
		define_processor_functions amber, dabort=nommu_early_abort, pabort=legacy_pabort, nommu=1

		.section ".rodata"

		string	cpu_arch_name, "armv2a"
		string	cpu_elf_name, "v2"
		string	cpu_amber_name, "amber"

		.align

		.section ".proc.info.init", #alloc

.macro amber_proc_info name:req, cpu_val:req, cpu_mask:req, cpu_name:req, \
	extra_hwcaps=0
		.type	__\name\()_proc_info, #object
__\name\()_proc_info:
		.long	\cpu_val
		.long	\cpu_mask
		.long	0
		.long	0
		initfn	__amber_setup, __\name\()_proc_info
		.long	cpu_arch_name
		.long	cpu_elf_name
		.long	HWCAP_SWP | HWCAP_26BIT | ( \extra_hwcaps )
		.long	\cpu_name
		.long	amber_processor_functions
		.long	0
		.long	0
		.long	v4_cache_fns
		.size	__\name\()_proc_info, . - __\name\()_proc_info
.endm

		amber_proc_info amber, 0x41007700, 0xfff8ff00, \
			cpu_amber_name
