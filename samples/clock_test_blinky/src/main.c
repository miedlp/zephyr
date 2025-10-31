/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <ti/driverlib/dl_gpio.h>
#include <ti/driverlib/m0p/sysctl/dl_sysctl_mspm0g1x0x_g3x0x.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

//	// PA7
//	DL_GPIO_initPeripheralOutputFunction(IOMUX_PINCM8, IOMUX_PINCM14_PF_SYSCTL_CLK_OUT);
//	DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_7);
	// PA9
	DL_GPIO_initPeripheralOutputFunction(IOMUX_PINCM20, IOMUX_PINCM20_PF_SYSCTL_CLK_OUT);
	DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_9);
//	// PA10
//	DL_GPIO_initPeripheralOutputFunction(IOMUX_PINCM21, IOMUX_PINCM21_PF_SYSCTL_CLK_OUT);
//	DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_10);
//	// PA14
//	DL_GPIO_initPeripheralOutputFunction(IOMUX_PINCM36, IOMUX_PINCM36_PF_SYSCTL_CLK_OUT);
//	DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_14);
//	// PA22
//	DL_GPIO_initPeripheralOutputFunction(IOMUX_PINCM47, IOMUX_PINCM47_PF_SYSCTL_CLK_OUT);
//	DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_22);
//	// PA31
//	DL_GPIO_initPeripheralOutputFunction(IOMUX_PINCM6, IOMUX_PINCM6_PF_SYSCTL_CLK_OUT);
//	DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_9);
//	// PB11
//	DL_GPIO_initPeripheralOutputFunction(IOMUX_PINCM28, IOMUX_PINCM28_PF_SYSCTL_CLK_OUT);
//	DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_11);


//	DL_SYSCTL_enableExternalClock(DL_SYSCTL_CLK_OUT_SOURCE_SYSOSC , DL_SYSCTL_CLK_OUT_DIVIDE_DISABLE);
	DL_SYSCTL_enableExternalClock(DL_SYSCTL_CLK_OUT_SOURCE_ULPCLK, DL_SYSCTL_CLK_OUT_DIVIDE_DISABLE);
//	DL_SYSCTL_enableExternalClock(DL_SYSCTL_CLK_OUT_SOURCE_ULPCLK, DL_SYSCTL_CLK_OUT_DIVIDE_10);

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		printf("LED state: %s\n", led_state ? "ON" : "OFF");
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
