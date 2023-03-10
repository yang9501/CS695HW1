#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <sys/utsname.h>
#include <stdint.h>

//comment out to live run
#define DEBUG 1

#define GPIO_PATH_44 "/sys/class/gpio/gpio44" //Green 1
#define GPIO_PATH_68 "/sys/class/gpio/gpio68" //Yellow 1
#define GPIO_PATH_67 "/sys/class/gpio/gpio67" //Red 1

#define GPIO_PATH_26 "/sys/class/gpio/gpio26" //Green 2
#define GPIO_PATH_46 "/sys/class/gpio/gpio46" //Yellow 2
#define GPIO_PATH_65 "/sys/class/gpio/gpio65" //Red 2

//Writes specified value to specified GPIO directory
static void writeLED(char *filename, char *port, char *value);
//Primary light switch logic
static void cycleLights(char *greenPort1, char *yellowPort1, char *redPort1, char *greenPort2, char *yellowPort2, char *redPort2);

int main(void) {
    //arrays containing GPIO port definitions, representing each of the two traffic lights
	char trafficLight1Ports[3][25] = {GPIO_PATH_44, GPIO_PATH_68, GPIO_PATH_67};
	char trafficLight2Ports[3][25] = {GPIO_PATH_26, GPIO_PATH_46, GPIO_PATH_65};

    #ifdef DEBUG
    (void) printf("DEBUG MODE\n");
    struct utsname sysInfo;
    (void) uname(&sysInfo);
    (void) printf("%s\n", sysInfo.sysname);
    (void) printf("%s\n", sysInfo.nodename);
    (void) printf("%s\n", sysInfo.machine);
    #else
    for (int i = 0; i < 3; i++) {
        (void) writeLED("/direction", trafficLight1Ports[i], "out");
        (void) writeLED("/direction", trafficLight2Ports[i], "out");
    }
    #endif

	while(1) {
		cycleLights(trafficLight1Ports[0], trafficLight1Ports[1], trafficLight1Ports[2], trafficLight2Ports[0], trafficLight2Ports[1], trafficLight2Ports[2]);	
	}

	return 0;
}

static void cycleLights(char *greenPort1, char *yellowPort1, char *redPort1, char *greenPort2, char *yellowPort2, char *redPort2) {
    #ifdef DEBUG
    (void) printf("Green1 on: %s\n", greenPort1);
    (void) printf("Red2 on: %s\n", redPort2);
    #else
    (void) writeLED("/value", greenPort1, "1");
    (void) writeLED("/value", redPort2, "1");
    #endif
	
    sleep(10);

    #ifdef DEBUG
    (void) printf("Green1 off: %s\n", greenPort1);
    (void) printf("Yellow1 on: %s\n", yellowPort1);
    #else
    (void) writeLED("/value", greenPort1, "0");
    (void) writeLED("/value", yellowPort1, "1");
    #endif
	
    sleep(5);

    #ifdef DEBUG
    (void) printf("Yellow1 off: %s\n", yellowPort1);
    (void) printf("Red1 on: %s\n", redPort1);
    (void) printf("Green2 on: %s\n", greenPort2);
    (void) printf("Red2 off: %s\n", redPort2);
    #else
    (void) writeLED("/value", yellowPort1, "0");
    (void) writeLED("/value", redPort1, "1");
    (void) writeLED("/value", greenPort2, "1");
    (void) writeLED("/value", redPort2, "0");
    #endif

    sleep(10);

    #ifdef DEBUG
    (void) printf("Green2 off: %s\n", greenPort2);
    (void) printf("Yellow2 on: %s\n", yellowPort2);
    #else
    (void) writeLED("/value", greenPort2, "0");
    (void) writeLED("/value", yellowPort2, "1");
    #endif

    sleep(5);

    #ifdef DEBUG
    (void) printf("Yellow2 off: %s\n", yellowPort2);
    (void) printf("Red1 off: %s\n", redPort1);
    #else
    (void) writeLED("/value", yellowPort2, "0");
    (void) writeLED("/value", redPort1, "0");
    #endif
}

static void writeLED(char *filename, char *port, char *value) {
	FILE* fp; //create file pointer
	char fullFileName[100]; //store path and filename
    (void) sprintf(fullFileName, "%s%s", port, filename); //write path/name
	fp = fopen(fullFileName, "w+"); //open file for writing
    (void) fprintf(fp, "%s", value); // send value to the file
    (void) fclose(fp); //close the file using the file pointer
}
