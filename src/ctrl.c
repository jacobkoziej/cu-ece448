// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * ctrl.c -- high-frequency control loop
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#include "ctrl.h"

#include <stdbool.h>
#include <stddef.h>

#include <hardware/gpio.h>
#include <pico/time.h>

static repeating_timer_t timer;

bool ctrl_callback(repeating_timer_t *rt)
{
	(void) rt;

	gpio_put(CTRL_PIN, !gpio_get(CTRL_PIN));

	return true;
}

void ctrl_init(void)
{
	gpio_init(CTRL_PIN);
	gpio_set_dir(CTRL_PIN, GPIO_OUT);

	add_repeating_timer_us(CTRL_PERIOD_US, ctrl_callback, NULL, &timer);
}
