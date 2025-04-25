# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>

cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD pico2)

include(lib/pico-sdk/pico_sdk_init.cmake)

project(cu-ece448)

pico_sdk_init()

add_subdirectory(src)
