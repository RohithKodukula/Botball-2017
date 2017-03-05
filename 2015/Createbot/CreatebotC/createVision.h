#ifndef _CREATEVISION_H_
#define _CREATEVISION_H_

//camera
void centerCamera(int channel, int object);
int centerCameraFast(int channel);

void cameraInitialize();

void blobTrack(int channel, int object);
int getLargestBlob(int channel);

int cameraSeesBigOrange();
point2 cameraSeesBigOranges();
void moveToBestBlob();

int cameraSeesBigYellow();
int sweepForYellow();

#endif
