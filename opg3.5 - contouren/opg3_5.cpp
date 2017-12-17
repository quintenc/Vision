// Contouren bepalen
// Quinten Ceelen, tijdens Minor Vision & Robotics 2017

#include "opencv2/imgproc/imgproc.hpp" 
#include <opencv2/core/core.hpp>
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

	// Lees de afbeelding in als grijswaarde afbeelding.

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// Afbeelding op het scherm weergeven 
	cout << "Imagefile: " << argv[1] << " met succes geconverteerd naar grijswaarde beeld." << endl;
	
	namedWindow("Grayscale", WINDOW_GUI_EXPANDED);
	imshow("Grayscale", image);

	//Threshold
	Mat thresheld;

	threshold(image, thresheld, 100, 255, CV_THRESH_BINARY);

	namedWindow("Thresheld", WINDOW_GUI_EXPANDED);
	imshow("Thresheld", thresheld);

	//Erosion

	Mat kernel = Mat::ones(5, 5, CV_32F);
	Mat eroded;

	erode(thresheld, eroded, kernel);

	namedWindow("Eroded", WINDOW_GUI_EXPANDED);
	imshow("Eroded", eroded);

	//Subtraction
	Mat subtracted;

	subtract(thresheld, eroded, subtracted);

	namedWindow("Subtracted", WINDOW_GUI_EXPANDED);
	imshow("Subtracted", subtracted);

	waitKey(0);
}