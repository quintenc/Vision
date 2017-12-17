// Kerstballen tellen met behulp van HSV
// Quinten Ceelen, tijdens Minor Vision & Robotics 2017

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

int main(int argc, char** argv)
{
	// Check of er een bestand is meegegeven als argument, als deze mist sluit het programma.
	if (argc != 2)
	{
		cout << "NB! Geef als command argument volledige padnaam van de imagefile mee" << endl;
		return -1;
	}
	else cout << "De imagefile = " << argv[1] << endl;

	// Lees kleurenafbeelding in
	Mat imageBGR;
	imageBGR = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!imageBGR.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cout << "Imagefile: " << argv[1] << " met succes geopend." << endl;

	// Converteer naar HSV, check voor range van kleuren, isoleer deze kleuren
	Mat imageHSV, imageRed, imageOrange, imageYellow, imageGreen, imageBlue, imageMagenta;

	cvtColor(imageBGR, imageHSV, CV_BGR2HSV);
	

	Scalar lowerRed = Scalar(0, 100, 100);
	Scalar upperRed = Scalar(10, 255, 255);
	Scalar lowerOrange = Scalar(12.5, 100, 100);
	Scalar upperOrange = Scalar(27.5,255,255);
	Scalar lowerYellow = Scalar(28, 100, 100);
	Scalar upperYellow = Scalar(33, 255, 255);
	Scalar lowerGreen = Scalar(40, 100, 100);
	Scalar upperGreen = Scalar(75, 255, 255);
	Scalar lowerBlue = Scalar(100, 100, 100);
	Scalar upperBlue = Scalar(125, 255, 255);
	Scalar lowerMagenta = Scalar(130, 100, 100);
	Scalar upperMagenta = Scalar(155, 255, 255);

	// source, low value, high value, destination 
	inRange(imageHSV, lowerRed, upperRed, imageRed); // red range
	inRange(imageHSV, lowerOrange, upperOrange, imageOrange); // orange range
	inRange(imageHSV, lowerYellow, upperYellow, imageYellow); // yellow range
	inRange(imageHSV, lowerGreen, upperGreen, imageGreen); // green range
	inRange(imageHSV, lowerBlue, upperBlue, imageBlue); // blue range
	inRange(imageHSV, lowerMagenta, upperMagenta, imageMagenta); // magenta range
	
	//erosion 
	Mat morphRed, morphOrange, morphYellow, morphGreen, morphBlue, morphMagenta;

	Mat kernel = Mat::ones(5, 5 , CV_32F);

	morphologyEx(imageRed, morphRed, MORPH_CLOSE, kernel);
	morphologyEx(imageOrange, morphOrange, MORPH_OPEN, kernel);
	morphologyEx(imageYellow, morphYellow, MORPH_OPEN, kernel);
	morphologyEx(imageGreen, morphGreen, MORPH_OPEN, kernel);
	morphologyEx(imageBlue, morphBlue,MORPH_OPEN, kernel);
	morphologyEx(imageMagenta, morphMagenta, MORPH_OPEN, kernel);

	// SimpleBlobDetector parameters
	
	SimpleBlobDetector:: Params params;

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
	cout << "Red blobs: " << keypoints.size() <<endl;
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
	waitKey(0);

}