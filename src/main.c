#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec ledv = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif 

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec ledb = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

void main(void)
{
    int ret;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&ledv)) {
        printk("Error: LED device %s is not ready\n", ledv.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&ledv, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&ledb)) {
        printk("Error: LED device %s is not ready\n", ledv.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&ledb, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    int cont = 0;

    while (1) {

        gpio_pin_toggle_dt(&ledv);

        if(cont == 2){
            gpio_pin_toggle_dt(&ledb);
            cont = 0;
        }

        cont++;
        k_msleep(500);

    }
}