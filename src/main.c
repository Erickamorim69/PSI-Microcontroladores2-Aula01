/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0) // LED Verde

/* The devicetree node identifier for the "led1" alias. */
#define LED1_NODE DT_ALIAS(led1) // LED Azul

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec ledv = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec ledb = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&ledv)) {
		return 0;
	}

    if (!gpio_is_ready_dt(&ledb)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&ledv, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

    ret = gpio_pin_configure_dt(&ledb, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&ledv);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		printf("Green LED state: %s\n", led_state ? "ON" : "OFF");
		k_msleep(1000);
	}
	return 0;
}