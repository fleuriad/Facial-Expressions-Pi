
#include "Webcam.h"
#include "RaspiCamCV.h"

Webcam::Webcam() {
	capture = raspiCamCvCreateCameraCapture(0);

}
Webcam::~Webcam() {
	
}

void Webcam::getImage(Mat& image) 
{
    Mat frame;
    IplImage* iplImg = raspiCamCvQueryFrame(capture);
    frame = iplImg;
    if (frame.empty()) {
    	throw std::string("Error : No frame captured");
    }
    if (iplImg->origin == IPL_ORIGIN_TL) {
        frame.copyTo( image );
    }
    else {
        flip(frame, image, 0);
    }
}
