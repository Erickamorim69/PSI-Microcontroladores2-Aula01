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
        gpio_pin_set_dt(&ledv, 1);
        k_msleep(50);
        gpio_pin_set_dt(&ledv, 0);
        k_msleep(950);
    }
}

K_THREAD_DEFINE(thread_verde, STACK_SIZE, thread_ledv,
                NULL, NULL, NULL,
                PRIORITY, 0, 0);

void thread_ledb() {
    while (1) {
        gpio_pin_set_dt(&ledb, 1);
        k_msleep(50);
        gpio_pin_set_dt(&ledb, 0);
        k_msleep(300);
    }
}

K_THREAD_DEFINE(thread_azul, STACK_SIZE, thread_ledb,
                NULL, NULL, NULL,
                PRIORITY, 0, 0);

int main(void){

    /* A função main somente inicializa os pinos dos leds e garante
     * que estejam funcionando.
     */

	int ret;

	if (!gpio_is_ready_dt(&ledv) || !gpio_is_ready_dt(&ledb)) {
		return 0;
	}

    // GPIO INACTIVE para o led inicializar em 0
	ret = gpio_pin_configure_dt(&ledv, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

    ret = gpio_pin_configure_dt(&ledb, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

    return 0;
}