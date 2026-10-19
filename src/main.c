/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define STACK_SIZE 1024
#define PRIORITY 5

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

void thread_ledv() {
    while (1) {
        gpio_pin_toggle_dt(&ledv);
        k_msleep(1000);
    }
}

K_THREAD_DEFINE(thread_verde, STACK_SIZE, thread_ledv,
                NULL, NULL, NULL,
                PRIORITY, 0, 0);

void thread_ledb() {
    while (1) {
        gpio_pin_toggle_dt(&ledb);
        k_msleep(500);
    }
}

K_THREAD_DEFINE(thread_azul, STACK_SIZE, thread_ledb,
                NULL, NULL, NULL,
                PRIORITY, 0, 0);

int main(void){
	int ret;

	if (!gpio_is_ready_dt(&ledv) || !gpio_is_ready_dt(&ledb)) {
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

    return 1;
}