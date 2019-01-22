/* MBED RTOS Blinky
 * Flash some simple LEDs using the RTOS
 * Thread version
 */

#include <mbed.h>

DigitalOut   red(LED1,1); /* initialise to 1 = off */

void flash_red(void)
{
	while(true) {
		red = !red;
		wait(0.3);
	}
}

int main(void)
{
	Thread blink;
	blink.start(flash_red);

	blink.join();
}

