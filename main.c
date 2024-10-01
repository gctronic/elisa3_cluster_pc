#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include "elisa3-lib.h"
#ifdef _WIN32
    #include "windows.h"
#endif

#define NUM_ROBOTS 37

void updateRGB(char *red, char *green, char *blue) {
    unsigned int rndNum;
    rndNum = rand()%400;
    if(rndNum < 100) {
        *red = rand()%100;
        *green = rand()%100;
        *blue = 0;
    } else if(rndNum < 200) {
        *red = rand()%100;
        *green = 0;
        *blue = rand()%100;
    } else if(rndNum < 300) {
        *red = 0;
        *green = rand()%100;
        *blue = rand()%100;
    } else {
        *red = rand()%100;
        *green = rand()%100;
        *blue = rand()%100;
    }
}

int main(void) {

    unsigned int k=0;
    time_t start, end, start2, end2;
    unsigned int connectedRobots = 0;
    unsigned int inClustersRobots = 0;
    int robotAddress[NUM_ROBOTS]={3414, 3415, 3307, 3973, 3239, 3413, 3419, 3309, 3235, 3416, 3417, 3412, 3306, 3236, 3281, 3233, 3310, 3338, 3311, 3305, 4073, 3304, 3232, 3342, 3341, 3302, 3345, 3344, 3263, 3343, 3873, 3287, 4479, 3418, 3240, 3420, 3237};
    // received from robot
    unsigned char robFlags[NUM_ROBOTS];
    // sent to robot
    char robRedLed, robGreenLed, robBlueLed;

    srand(time(NULL));

    // init the communication with the robots; set the addresses and number of the robots to control
    startCommunication(robotAddress, NUM_ROBOTS);

    time(&start);
    time(&start2);

    while(1) {

        connectedRobots = 0;
        inClustersRobots = 0;
        for(k=0; k<NUM_ROBOTS; k++) {
            //printf("RFquality(%d) = %f\r\n", k, getRFQuality(robotAddress[k])); // Updated every 5 seconds
            if(getRFQuality(robotAddress[k]) >= 20.0) {
                connectedRobots++;
                robFlags[k] = getFlagRX(robotAddress[k]);
                if((robFlags[k]&0x08) == 0x08) {
                    inClustersRobots++;
                }
            }
        }

        time(&end2);
        if(difftime(end2, start2) >= 1) {
            time(&start2);
            printf("Connected robots: %d\r\n", connectedRobots);
            printf("In clusters robots: %d\r\n", inClustersRobots);
            printf("Color (RGB): %d, %d, %d\r\n\n", robRedLed, robGreenLed, robBlueLed);
        }

        time(&end);
        if(difftime(end, start) >= 1) {
            time(&start);
            updateRGB(&robRedLed, &robGreenLed, &robBlueLed);
            for(k=0; k<NUM_ROBOTS; k++) {
                if((robFlags[k]&0x08) == 0x08) { // Change colors only for robots in clusters
                    setRed(robotAddress[k], robRedLed);
                    setGreen(robotAddress[k], robGreenLed);
                    setBlue(robotAddress[k], robBlueLed);
                } else {
                    setRed(robotAddress[k], 0);
                    setGreen(robotAddress[k], 0);
                    setBlue(robotAddress[k], 0);
                }
            }
        }

    }

    stopCommunication();

	return 0;

}
