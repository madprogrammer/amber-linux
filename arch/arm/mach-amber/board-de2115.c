/*
 *  linux/arch/arm/mach-integrator/integrator_cp.c
 *
 *  Copyright (C) 2003 Deep Blue Solutions Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 */
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/irqchip.h>
#include <linux/gfp.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/sched_clock.h>

#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/irq.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>

#include <mach/hardware.h>

/*
 * Logical      Physical
 * f1300000	13000000	Counter/Timer
 * f1400000	14000000	Interrupt controller
 * f1600000	16000000	UART 0
 * f1700000	17000000	UART 1
 */

static struct map_desc amber_de2115_io_desc[] __initdata __maybe_unused = {
	{
		.virtual	= IO_ADDRESS(AMBER_INTERRUPT_BASE),
		.pfn		= __phys_to_pfn(AMBER_INTERRUPT_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE
	}, {
		.virtual	= IO_ADDRESS(AMBER_UART0_BASE),
		.pfn		= __phys_to_pfn(AMBER_UART0_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE
	}
};

static void __init amber_de2115_map_io(void)
{
	iotable_init(amber_de2115_io_desc, ARRAY_SIZE(amber_de2115_io_desc));
}

static void __init amber_de2115_init_early(void)
{
}

static void __init amber_de2115_init_irq_of(void)
{
	irqchip_init();
}

static struct of_dev_auxdata amber_de2115_auxdata_lookup[] __initdata = {
	OF_DEV_AUXDATA("arm,primecell", AMBER_UART0_BASE,
		"uart0", NULL),
	{ /* sentinel */ },
};

static void __init amber_de2115_init_of(void)
{
	of_platform_default_populate(NULL, amber_de2115_auxdata_lookup, NULL);
}

static const char * amber_de2115_dt_board_compat[] = {
	"terasic,amber-de2115",
	NULL,
};

DT_MACHINE_START(AMBER_DE2115_DT, "Amber SoC on DE2-115 (Device Tree)")
	.map_io		= amber_de2115_map_io,
	.init_early	= amber_de2115_init_early,
	.init_irq	= amber_de2115_init_irq_of,
	.init_machine	= amber_de2115_init_of,
	.dt_compat      = amber_de2115_dt_board_compat,
MACHINE_END
