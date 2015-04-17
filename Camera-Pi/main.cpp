   /*
 * main.cpp
 *
 *  Created on: 31 mai 2014
 *      Author: Fleuri Adon
 */
#define CV_NO_BACKWARD_COMPATIBILITY

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

#include "Webcam.h"
#include "Detection.h"
#include "Face.h"

Webcam *webcam = new Webcam();

    Mat img;
    Detection *detection = new Detection();
void expression(Rect &rect, Mat img);
int main( int argc, const char** argv )
{
    
    // On va créer ici la fenetre 
    cvNamedWindow( "result", 1 );

	for (;;)
	{
		webcam->getImage(img);
		// Detection faces
		vector<Face*>* faces = detection->detectFaces(img);
		// Ajouter information sur l'image
		for (vector<Face*>::const_iterator face = faces->begin(); face != faces->end(); face++ )
		{
			
			Scalar colorFace = CV_RGB(150,150,150);
			Scalar colorEye = CV_RGB(10,200,10);
			Scalar colorMouth = CV_RGB(200,10,10);
			Scalar colorNose = CV_RGB(10,10,200);
			Rect faceRect = (*face)->getRect();
			rectangle(img,faceRect, colorFace,1); 
			// Yeux
			if ((*face)->hasEyes()) {
				// Oeil droit
				Rect& eye = (*face)->getLeftEye();
				eye.x += faceRect.x;
				eye.y += faceRect.y;
	            rectangle(img, eye, colorEye, 1);
	            // Oeil gauche
	            eye = (*face)->getRightEye();
				eye.x += faceRect.x;
				eye.y += faceRect.y;
	            rectangle(img, eye, colorEye, 1);
			}
			// Bouche
			if ((*face)->hasMouth()) 
				{
				Rect& mouth = (*face)->getMouth();
				mouth.x += faceRect.x;
				mouth.y += faceRect.y;
	            		rectangle(img, mouth, colorMouth, 1);
				expression(mouth,img);
				
				
				
			}
			// Nez
			if ((*face)->hasNose()) {
				Rect& nose = (*face)->getNose();
				nose.x += faceRect.x;
				nose.y += faceRect.y;
	            		rectangle(img, nose, colorNose, 1);
			
			}
		}
		// On  affiche ces resultat dans la fenetre
		cv::imshow("result", img);
		// End
		if( waitKey( 10 ) >= 0 )
			goto _cleanup_;
	}
	// Release resources
	waitKey(0);
_cleanup_:
    cvDestroyWindow("result");
    return 0;
}

void expression(Rect &rect, Mat img)
{
	int nb_pixels_blancs=0;
	int nb_pixels_vert = 0;
	Mat grey;
	cvtColor(img, grey, CV_RGB2GRAY);

	Rect roi = Rect(rect.x,rect.y,rect.width,rect.height);
	Mat bouche = img(roi);

	for(int j = roi.y; j<roi.y + roi.height; j=j+2)
	{
		for(int i = roi.x; i<roi.x+roi.width; i=i+2)
		{
			/*
			uchar intensite = bouche.at<uchar>(j,i);
			if(intensite > 150)
			{
				nb_pixels_blancs++;
			}
			*/
			
			Vec3b intensite = img.at<Vec3b> (j,i);
			
			if(intensite.val[1] > 160)
			{
				nb_pixels_vert++;
			}
				
		
		} 
	}
	cout << "Nombre de pixels verts " << 4*nb_pixels_vert << endl;
	cout << (rect.width*rect.height) << endl;

	if((4*nb_pixels_vert) > (rect.width*rect.height)/45)
	{
		
		cout << " HAPPY " << endl;
		putText(img,"HAPPY", cvPoint(100,40), CV_FONT_HERSHEY_SIMPLEX, 1.0, cvScalar(255));
	}
	else
	{
		cout << " NOT HAPPY" << endl;
		putText(img,"SERIOUS", cvPoint(100,40), CV_FONT_HERSHEY_SIMPLEX, 1.0, cvScalar(255));
	}

}
