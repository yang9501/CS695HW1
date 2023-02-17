#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define GPIO_PATH "/sys/class/gpio/gpio"

void writeLED(char filename[], char port[], char value[]);

int main() {
	writeLED("/direction", "68", "out"); // set direction for pin
	printf("Beginning to blink LED 5 times.\n");
	for (int i =0; i < 5; i++) {
		writeLED("/value", "68", "1");
		sleep(1);
		writeLED("/value", "68", "0");
		sleep(1);
		printf("Blink %d\n", i);
	}
	printf("Blinking complete.\n");	
	
	return 0;
}

void writeLED(char filename[], char port[], char value[]) {
	FILE* fp; //create file pointer
	char fullFileName[100]; //store path and filename
	sprintf(fullFileName, GPIO_PATH "%s%s", port, filename); //write path/name
	fp = fopen(fullFileName, "w+"); //open file for writing
	fprintf(fp, "%s", value); // send value to the file
	fclose(fp); //close the file using the file pointer
}
