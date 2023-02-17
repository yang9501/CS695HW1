#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define GPIO_PATH "/sys/class/gpio/gpio"

void writeLED(char filename[], char port[], char value[]);
void cycleLights(char greenPort1[], char yellowPort1[], char redPort1[], char greenPort2[], char yellowPort2[], char redPort2[]);

int main() {
	char trafficLight1Ports[3][5] = {"44", "68", "67"};
	char trafficLight2Ports[3][5] = {"26", "46", "65"};
	for(int i = 0; i < 3; i++) {
		writeLED("/direction", trafficLight1Ports[i], "out");
		writeLED("/direction", trafficLight2Ports[i], "out");
	}

	while(1) {
		cycleLights(trafficLight1Ports[0], trafficLight1Ports[1], trafficLight1Ports[2], trafficLight2Ports[0], trafficLight2Ports[1], trafficLight2Ports[2]);	
	}

	return 0;
}

void cycleLights(char greenPort1[], char yellowPort1[], char redPort1[], char greenPort2[], char yellowPort2[], char redPort2[]) {
	printf("Green1 on: %s\n", greenPort1);
	writeLED("/value", greenPort1, "1");
	printf("Red2 on: %s\n", redPort2);
	writeLED("/value", redPort2, "1");
	
	sleep(10);
	
	printf("Green1 off: %s\n", greenPort1);
	writeLED("/value", greenPort1, "0");
	printf("Yellow1 on: %s\n", yellowPort1);
       	writeLED("/value", yellowPort1, "1");
	
	sleep(5);
	
	printf("Yellow1 off: %s\n", yellowPort1);
	writeLED("/value", yellowPort1, "0");
	printf("Red1 on: %s\n", redPort1);
	writeLED("/value", redPort1, "1");
	printf("Green2 on: %s\n", greenPort2);
	writeLED("/value", greenPort2, "1");
	printf("Red2 off: %s\n", redPort2);
	writeLED("/value", redPort2, "0");
	

	sleep(10);

	printf("Green2 off: %s\n", greenPort2);
	writeLED("/value", greenPort2, "0");
	printf("Yellow2 on: %s\n", yellowPort2);
	writeLED("/value", yellowPort2, "1");

	sleep(5);
	
	printf("Yellow2 off: %s\n", yellowPort2);
	writeLED("/value", yellowPort2, "0");
	printf("Red1 off: %s\n", redPort1);
	writeLED("/value", redPort1, "0");	
}

void writeLED(char filename[], char port[], char value[]) {
	FILE* fp; //create file pointer
	char fullFileName[100]; //store path and filename
	sprintf(fullFileName, GPIO_PATH "%s%s", port, filename); //write path/name
	fp = fopen(fullFileName, "w+"); //open file for writing
	fprintf(fp, "%s", value); // send value to the file
	fclose(fp); //close the file using the file pointer
}
