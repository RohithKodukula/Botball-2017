#ifndef _LEGOBOTVISION_H_
#define _LEGOBOTVISION_H_

void cameraInitialize();
void moveToDistWithKicker(int power, int dist, int channelToLookFor);
int getRightMostBlock(int numChannels);


#endif
