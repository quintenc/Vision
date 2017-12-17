// Threshold operaties
// Quinten Ceelen, Minor Vision & Robotics 2017
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
	// Via de debugging properties moet er een afbeelding meegegeven worden
	if (argc != 2)
	{
		cout << "NB! Geef als command argument volledige padnaam van de imagefile mee" << endl;
		return -1;
	}
	else cout << "De imagefile = " << argv[1] << endl;

	// Maak alle matrixes aan die gebruikt zullen worden
	Mat image;
	Mat binary;
	Mat binaryInverse;
	Mat truncate;
	Mat toZero;
	Mat toZeroInverse;

	// Lees de afbeelding en converteer gelijk naar grijswaarde.
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	threshold(image, binary, 100, 255, CV_THRESH_BINARY);
	threshold(image, binaryInverse, 100, 255, CV_THRESH_BINARY_INV);
	threshold(image, truncate, 100, 255, CV_THRESH_TRUNC);
	threshold(image, toZero, 100, 255, CV_THRESH_TOZERO);
	threshold(image, toZeroInverse, 100, 255, CV_THRESH_TOZERO_INV);

	namedWindow("Default", WINDOW_AUTOSIZE);
	namedWindow("Binary", WINDOW_AUTOSIZE);
	namedWindow("Binary Inverse", WINDOW_AUTOSIZE);
	namedWindow("Truncate", WINDOW_AUTOSIZE);
	namedWindow("To zero", WINDOW_AUTOSIZE);
	namedWindow("To zero Inverse", WINDOW_AUTOSIZE);

	imshow("Default", image);
	imshow("Binary", binary);
	imshow("Binary Inverse", binaryInverse);
	imshow("Truncate", truncate);
	imshow("To zero", toZero);
	imshow("To zero Inverse", toZeroInverse);

	// Wait for a keystroke in the window
	waitKey(0);
}