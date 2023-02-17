#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define GPIO_PATH "/sys/class/gpio/gpio"

void writeLED(char filename[], char port[], char value[]);
void cycleLights(char greenPort[], char yellowPort[], char redPort[]);

int main() {
	char trafficLight1Ports[3][5] = {"44", "68", "67"};
	char trafficLight2Ports[3][5] = {"26", "46", "65"};
	for(int i = 0; i < 3; i++) {
		writeLED("/direction", trafficLight1Ports[i], "out");
		writeLED("/direction", trafficLight2Ports[i], "out");
	}

	while(1) {
		cycleLights(trafficLight1Ports[0], trafficLight1Ports[1], trafficLight1Ports[2]);	
		cycleLights(trafficLight2Ports[0], trafficLight2Ports[1], trafficLight2Ports[2]);	
	}

	return 0;
}

void cycleLights(char greenPort[], char yellowPort[], char redPort[]) {
	printf("Green on: %s\n", greenPort);
	writeLED("/value", greenPort, "1");
	sleep(20);
	printf("Green off: %s\n", greenPort);
	writeLED("/value", greenPort, "0");
	printf("Yellow on: %s\n", yellowPort);
       	writeLED("/value", yellowPort, "1");
	sleep(5);
	printf("Yellow off: %s\n", yellowPort);
	writeLED("/value", yellowPort, "0");
	printf("Red on: %s\n", redPort);
	writeLED("/value", redPort, "1");
	sleep(25);
	printf("Red off: %s\n", redPort);
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
