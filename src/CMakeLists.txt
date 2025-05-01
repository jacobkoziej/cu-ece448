# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>

add_executable(
	firmware
	ctrl.c
	main.c
)
target_link_libraries(
	firmware
	hardware_adc
	hardware_dma
	hardware_gpio
	pico_runtime
	pico_time
)
pico_add_extra_outputs(firmware)
