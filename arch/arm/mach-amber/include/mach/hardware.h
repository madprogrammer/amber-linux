/*
 *  This file contains the hardware definitions for Amber SoC.
 *
 *  Copyright (C) 2016 Sergey Anufrienko <sergey.anoufrienko@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __MACH_HARDWARE_H
#define __MACH_HARDWARE_H

/*
 * Memory Map definitions
 */
#define AMBER_UART0_BASE		0x16000000
#define AMBER_UART1_BASE		0x17000000
#define AMBER_TIMER_BASE		0x13000000
#define AMBER_INTERRUPT_BASE	0x14000000
#define AMBER_TEST_BASE			0xF0000000

#if !defined(CONFIG_MMU)
#define IO_ADDRESS(x)	(x)
#endif

/*
 * UART Clock when System clk is 150MHz
 */
#define UART_CLK	48000000

#endif
