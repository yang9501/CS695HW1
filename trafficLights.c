#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define DEBUG 1
#define GPIO_PATH_44 "/sys/class/gpio/gpio44" //Green 1
#define GPIO_PATH_68 "/sys/class/gpio/gpio68" //Yellow 1
#define GPIO_PATH_67 "/sys/class/gpio/gpio67" //Red 1

#define GPIO_PATH_26 "/sys/class/gpio/gpio26" //Green 2
#define GPIO_PATH_46 "/sys/class/gpio/gpio46" //Yellow 2
#define GPIO_PATH_65 "/sys/class/gpio/gpio65" //Red 2

void writeLED(char filename[], char port[], char value[]);
void cycleLights(char greenPort1[], char yellowPort1[], char redPort1[], char greenPort2[], char yellowPort2[], char redPort2[]);

int main() {
	char trafficLight1Ports[3][25] = {GPIO_PATH_44, GPIO_PATH_68, GPIO_PATH_67};
	char trafficLight2Ports[3][25] = {GPIO_PATH_26, GPIO_PATH_46, GPIO_PATH_65};

    #ifdef DEBUG
        printf("DEBUG MODE\n");
    #else
    for (int i = 0; i < 3; i++) {
        writeLED("/direction", trafficLight1Ports[i], "out");
        writeLED("/direction", trafficLight2Ports[i], "out");
    }
    #endif

	while(1) {
		cycleLights(trafficLight1Ports[0], trafficLight1Ports[1], trafficLight1Ports[2], trafficLight2Ports[0], trafficLight2Ports[1], trafficLight2Ports[2]);	
	}

	return 0;
}

void cycleLights(char greenPort1[], char yellowPort1[], char redPort1[], char greenPort2[], char yellowPort2[], char redPort2[]) {
    #ifdef DEBUG
    printf("Green1 on: %s\n", greenPort1);
    printf("Red2 on: %s\n", redPort2);
    #else
    writeLED("/value", greenPort1, "1");
    writeLED("/value", redPort2, "1");
    #endif
	
    sleep(10);

    #ifdef DEBUG
    printf("Green1 off: %s\n", greenPort1);
    printf("Yellow1 on: %s\n", yellowPort1);
    #else
    writeLED("/value", greenPort1, "0");
    writeLED("/value", yellowPort1, "1");
    #endif
	
    sleep(5);

    #ifdef DEBUG
    printf("Yellow1 off: %s\n", yellowPort1);
    printf("Red1 on: %s\n", redPort1);
    printf("Green2 on: %s\n", greenPort2);
    printf("Red2 off: %s\n", redPort2);
    #else
    writeLED("/value", yellowPort1, "0");
    writeLED("/value", redPort1, "1");
    writeLED("/value", greenPort2, "1");
    writeLED("/value", redPort2, "0");
    #endif

    sleep(10);

    #ifdef DEBUG
    printf("Green2 off: %s\n", greenPort2);
    printf("Yellow2 on: %s\n", yellowPort2);
    #else
    writeLED("/value", greenPort2, "0");
    writeLED("/value", yellowPort2, "1");
    #endif

    sleep(5);

    #ifdef DEBUG
    printf("Yellow2 off: %s\n", yellowPort2);
    printf("Red1 off: %s\n", redPort1);
    #else
    writeLED("/value", yellowPort2, "0");
    writeLED("/value", redPort1, "0");
    #endif
}

void writeLED(char filename[], char port[], char value[]) {
	FILE* fp; //create file pointer
	char fullFileName[100]; //store path and filename
	sprintf(fullFileName, "%s%s", port, filename); //write path/name
	fp = fopen(fullFileName, "w+"); //open file for writing
	fprintf(fp, "%s", value); // send value to the file
	fclose(fp); //close the file using the file pointer
}
