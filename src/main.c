// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * main.c -- main
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#include <stdbool.h>

#include <hardware/adc.h>
#include <hardware/dma.h>

#define ADC_CHANNEL 0
#define ADC_PIN     26
#define ADC_SAMPLES (1 << 14)

#define ADC_FIFO_EN          true
#define ADC_FIFO_DREQ_EN     true
#define ADC_FIFO_DREQ_THRESH 1
#define ADC_FIFO_ERR_IN_FIFO false
#define ADC_FIFO_BYTE_SHIFT  true

unsigned char adc_buffer[ADC_SAMPLES];

int main(void)
{
	adc_gpio_init(ADC_PIN);

	adc_init();
	adc_select_input(ADC_CHANNEL);
	adc_fifo_setup(
		ADC_FIFO_EN,
		ADC_FIFO_DREQ_EN,
		ADC_FIFO_DREQ_THRESH,
		ADC_FIFO_ERR_IN_FIFO,
		ADC_FIFO_BYTE_SHIFT);

	adc_set_clkdiv(0);

	unsigned dma_channel = dma_claim_unused_channel(true);
	dma_channel_config cfg = dma_channel_get_default_config(dma_channel);

	channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
	channel_config_set_read_increment(&cfg, false);
	channel_config_set_write_increment(&cfg, true);

	channel_config_set_dreq(&cfg, DREQ_ADC);

	dma_channel_configure(
		dma_channel,
		&cfg,
		adc_buffer,
		&adc_hw->fifo,
		ADC_SAMPLES,
		true);

	adc_run(true);

	dma_channel_wait_for_finish_blocking(dma_channel);
	adc_run(false);
	adc_fifo_drain();
}
