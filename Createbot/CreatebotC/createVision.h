#ifndef _CREATEVISION_H_
#define _CREATEVISION_H_

//camera
void centerCamera(int channel, int object);
int centerCameraFast(int channel);

void cameraInitialize();

void blobTrack(int channel, int object);
int getLargestBlob(int channel);

#endif
