// Functionaliteit: Test- en demoprogramma voor labeling functies
//                  uit de library avansvisionlib.  
// Jan Oostindie, dd 17-3-2016
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/flann/flann.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp" 
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	// Open de camera met nummer 1 in lijst (red.: nr 0 was bij mij de camera in de klep van mijn laptop)  
	VideoCapture cap(1);

	// Controle of de camera wordt herkend.
	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	// Breedte en hooogte van de frames die de camera genereert ophalen. 
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	// Window maken waarin de beelden "live" getoond worden
	//namedWindow("Original", CV_WINDOW_AUTOSIZE);

	//namedWindow("Result", CV_WINDOW_AUTOSIZE);
	// Continue loop waarin een beeld wordt opgehaald en wordt getoond in het window
	Mat frame;

	while (1)
	{
		// Lees een nieuw frame
		bool bSuccess = cap.read(frame);

		// Controlleer of het frame goed gelezen is.
		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		// Converteer naar HSV, check voor range van kleuren, isoleer deze kleuren
		Mat imageHSV, imageRed, imageRed2, imageOrange, imageYellow, imageGreen, imageBlue, imageMagenta;

		cvtColor(frame, imageHSV, CV_BGR2HSV);


		Scalar lowerRed = Scalar(0, 100, 100);
		Scalar upperRed = Scalar(10, 255, 255);
		Scalar lowerRed2 = Scalar(169, 100, 100);
		Scalar upperRed2 = Scalar(179, 255, 255);
		Scalar lowerOrange = Scalar(12.5, 100, 100);
		Scalar upperOrange = Scalar(25, 255, 255);
		Scalar lowerYellow = Scalar(27, 100, 100);
		Scalar upperYellow = Scalar(38, 255, 255);
		Scalar lowerGreen = Scalar(40, 100, 100);
		Scalar upperGreen = Scalar(102, 255, 255);
		Scalar lowerBlue = Scalar(105, 100, 100);
		Scalar upperBlue = Scalar(125, 255, 255);
		Scalar lowerMagenta = Scalar(130, 100, 100);
		Scalar upperMagenta = Scalar(165, 255, 255);

		// source, low value, high value, destination 
		inRange(imageHSV, lowerRed, upperRed, imageRed); // red range
		inRange(imageHSV, lowerOrange, upperOrange, imageOrange); // orange range
		inRange(imageHSV, lowerYellow, upperYellow, imageYellow); // yellow range
		inRange(imageHSV, lowerGreen, upperGreen, imageGreen); // green range
		inRange(imageHSV, lowerBlue, upperBlue, imageBlue); // blue range
		inRange(imageHSV, lowerMagenta, upperMagenta, imageMagenta); // magenta range

		//erosion 
		Mat morphRed, morphOrange, morphYellow, morphGreen, morphBlue, morphMagenta;

		Mat kernel = Mat::ones(5, 5, CV_32F);

		morphologyEx(imageRed, morphRed, MORPH_CLOSE, kernel);
		morphologyEx(imageOrange, morphOrange, MORPH_CLOSE, kernel);
		morphologyEx(imageYellow, morphYellow, MORPH_CLOSE, kernel);
		morphologyEx(imageGreen, morphGreen, MORPH_CLOSE, kernel);
		morphologyEx(imageBlue, morphBlue, MORPH_CLOSE, kernel);
		morphologyEx(imageMagenta, morphMagenta, MORPH_CLOSE, kernel);

		// SimpleBlobDetector parameters

		SimpleBlobDetector::Params params;

		params.minDistBetweenBlobs = 10; //Minimum distance between blobs
		params.filterByColor = true;
		params.blobColor = 255;
		params.filterByCircularity = false;
		params.filterByConvexity = false;
		params.filterByInertia = false;

		params.filterByArea = false; // filter by area of the blob
		params.minArea = 10;// Minimum area of the blob
		params.maxArea = 100000; // Maximum area of the blob

		vector<KeyPoint> keypoints; // holds all blobs

		Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

		//detect all blobs
		detector->detect(morphRed, keypoints);
		cout << "Red blobs: " << keypoints.size() << endl;
		keypoints.clear();

		detector->detect(morphOrange, keypoints);
		cout << "Orange blobs: " << keypoints.size() << endl;
		keypoints.clear();

		detector->detect(morphYellow, keypoints);
		cout << "Yellow blobs: " << keypoints.size() << endl;
		keypoints.clear();

		detector->detect(morphGreen, keypoints);
		cout << "Green blobs: " << keypoints.size() << endl;
		keypoints.clear();

		detector->detect(morphBlue, keypoints);
		cout << "Blue blobs: " << keypoints.size() << endl;
		keypoints.clear();

		detector->detect(morphMagenta, keypoints);
		cout << "Magenta blobs: " << keypoints.size() << endl;


		// Geef HSV en losse kanalen weer op scherm
		namedWindow("HSV", WINDOW_GUI_EXPANDED);
		imshow("HSV", imageHSV);

		namedWindow("Red", WINDOW_GUI_EXPANDED);
		imshow("Red", morphRed);
		namedWindow("Orange", WINDOW_GUI_EXPANDED);
		imshow("Orange", morphOrange);
		namedWindow("Yellow", WINDOW_GUI_EXPANDED);
		imshow("Yellow", morphYellow);
		namedWindow("Green", WINDOW_GUI_EXPANDED);
		imshow("Green", morphGreen);
		namedWindow("Blue", WINDOW_GUI_EXPANDED);
		imshow("Blue", morphBlue);
		namedWindow("Magenta", WINDOW_GUI_EXPANDED);
		imshow("Magenta", morphMagenta);

		//  Wacht 30 ms op ESC-toets. Als ESC-toets is ingedrukt verlaat dan de loop
		if (waitKey(1) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
		waitKey(0);
	}

	return 0;
}
