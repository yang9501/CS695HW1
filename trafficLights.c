#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define GPIO_PATH "/sys/class/gpio/gpio"

void writeLED(char filename[], char port[], char value[]);

int main() {
	writeLED("/direction", "68", "out"); // set direction for pin
	char trafficLight1Ports[] = ["67", "68", "44"];
	char trafficLight2Ports[] = ["26", "46", "65"];
	printf("Beginning to blink LED 5 times.\n");
	for (int i =0; i < 2; i++) {
		writeLED("/value", "68", "1");
		sleep(1);
		writeLED("/value", "68", "0");
		sleep(1);
		printf("Blink %d\n", i);
	} 
	printf("Blinking complete.\n");	
	
	return 0;
}

void cycleLights() {
	writeLED("/value", greenPort, "1");
	sleep(120);
	writeLED("/value", greenPort, "0");
       	writeLED("/value", yellowPort, "1");
	sleep(5);
	writeLED("/value", yellowPort, "0");
	writeLED("/value", redPort, "1");
	sleep(125);
	writeLED("/value", redPort, "0");	
}

void writeLED(char filename[], char port[], char value[]) {
	FILE* fp; //create file pointer
	char fullFileName[100]; //store path and filename
	sprintf(fullFileName, GPIO_PATH "%s%s", port, filename); //write path/name
	fp = fopen(fullFileName, "w+"); //open file for writing
	fprintf(fp, "%s", value); // send value to the file
	fclose(fp); //close the file using the file pointer
}
