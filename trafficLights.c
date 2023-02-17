#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define GPIO_PATH "/sys/class/gpio/gpio"

void writeLED(char filename[], char port[], char value[]);

int main() {
	writeLED("/direction", "68", "out"); // set direction for pin
	char trafficLight1Ports[3][5] = ["67", "68", "44"];
	char trafficLight2Ports[3][5] = ["26", "46", "65"];

	while(true) {
		cycleLights(trafficLight1Ports[0], trafficLight1Ports[1], trafficLight1Ports[2]);
		
		cycleLights(trafficLight2Ports[0], trafficLight2Ports[1], trafficLight2Ports[2]);	
	}

	return 0;
}

void cycleLights(char[] greenPort, char[] yellowPort, char[] redPort) {
	writeLED("/value", greenPort, "1");
	sleep(20);
	writeLED("/value", greenPort, "0");
       	writeLED("/value", yellowPort, "1");
	sleep(5);
	writeLED("/value", yellowPort, "0");
	writeLED("/value", redPort, "1");
	sleep(25);
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
