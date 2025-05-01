// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * ctrl.h -- high-frequency control loop
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#ifndef CTRL_H
#define CTRL_H

#include <stdbool.h>
#include <stdint.h>

#include <pico/time.h>

#define CTRL_PERIOD_US ((int64_t) -25)
#define CTRL_PIN       15

bool ctrl_callback(repeating_timer_t *rt);
void ctrl_init(void);

#endif  /* CTRL_H */
