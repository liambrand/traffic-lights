/* MBED RTOS Blinky
 * Flash some simple LEDs using the RTOS
 * Thread version
 */

#include <mbed.h>
#include <Semaphore.h>

/* Threads */
Thread trafficLights;
Thread crossingLights;

/* Event Queue */
EventQueue queue(32 * EVENTS_EVENT_SIZE);

/* Semaphores */
Semaphore buttonPressed(1);

/* Traffic Lights */
DigitalOut	trafficRed(LED1, 1);
DigitalOut	trafficGreen(LED2, 1);
DigitalOut	trafficBlue(LED3, 1);

/* Pedestrian Lights */
DigitalOut	crossRed (D5, 1);
DigitalOut	crossGreen (D9, 1);

InterruptIn button(D4);

bool beeping = false;


void trafficSequence(void) {
	buttonPressed.wait();
	while(true) {
		// Amber on for 3 seconds
		trafficGreen = 1;
		trafficBlue = 0;
		wait(3.0);
		
		// Red on for 2 seconds
		trafficBlue = 1;
		trafficRed = 0;
		wait(2.0);
		
		// Red on for 5 seconds with audible tone
		beeping = true;
		wait(5.0);
		
		// Stop beeping
		beeping = false;
		wait(4.0);
		trafficRed = 1;
		trafficGreen = 0;
		wait(5.0);
	}
}

void buttonPress(void) {
	//trafficRed = !trafficRed;
}

int main(void) {
	trafficLights.start(callback(&queue, &EventQueue::dispatch_forever));
	//crossingLights.start(callback(&queue, &EventQueue::dispatch_forever));
	
	button.rise(trafficSequence);
	
	
}

