#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 500

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

void main(void)
{
    int ret;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED device %s is not ready\n", led0.port->name);
        return;
    }
    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED1 device %s is not ready\n", led1.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED1 pin\n", ret);
        return;
    }

    printk("Blinking LED0 (%s pin %d) and LED1 (%s pin %d)\n", 
           led0.port->name, led0.pin, led1.port->name, led1.pin);
    gpio_pin_toggle_dt(&led0); // fazer o led 0 iniciar desligado
    uint32_t step = 0;
    while (1) {
// LED1 alterna o estado a cada passo (500 ms)
        gpio_pin_toggle_dt(&led1);
        k_msleep(10);
        gpio_pin_toggle_dt(&led1);

        // LED0 alterna o estado a cada dois passos (2 * 500 ms = 1000 ms)
        if (step % 2 == 0) {
            gpio_pin_toggle_dt(&led0);
            k_msleep(10);
            gpio_pin_toggle_dt(&led0);
        }

        step++;

        // Atraso de tempo base
        k_msleep(500);


    }
}