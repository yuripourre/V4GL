#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>

#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <linux/videodev2.h>

using namespace std;

class Camera {
	
public:

	unsigned int width;
	unsigned int height;
	unsigned char* dst;
	string deviceName;

	Camera(int w, int h, string deviceName){
		this->width = w;
		this->height = h;
		this->deviceName = deviceName.c_str();
		dst = new unsigned char[width*height*3];
	}
		
	void deviceOpen(void);
	void deviceClose(void);
	void captureStart(void);
	void captureStop(void);
	
	void deviceInit(void);
	void deviceUninit(void);
	
	void mainLoop(void);
	void readFrame(void);
	
	~Camera(){
		delete[] dst;
	}
	
private:
	void imageProcess(const void* p);
	int frameRead(void);
	
	void mmapInit(void);
	void userptrInit(unsigned int buffer_size);
	
};

#endif
