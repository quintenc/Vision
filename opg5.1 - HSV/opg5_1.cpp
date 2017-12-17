// RGB image omzetten naar HSV, losse kanalen weergeven.
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

	// Lees kleurenafbeelding in

	Mat imageRGB;
	imageRGB = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!imageRGB.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cout << "Imagefile: " << argv[1] << " met succes geopend." << endl;

	// Geef RGB weer
	namedWindow("RGB", WINDOW_GUI_EXPANDED);
	imshow("RGB", imageRGB);

	// Converteer naar HSV, split de kanalen
	Mat imageHSV;
	vector<Mat> channels; //array waarin de kanalen worden opgeslagen

	cvtColor(imageRGB, imageHSV, CV_BGR2HSV);
	split(imageHSV, channels);

	// Geef HSV en losse kanalen weer op scherm
	namedWindow("HSV", WINDOW_GUI_EXPANDED);
	imshow("HSV", imageHSV);

	namedWindow("H", WINDOW_GUI_EXPANDED);
	imshow("H", channels[0]);

	namedWindow("S", WINDOW_GUI_EXPANDED);
	imshow("S", channels[1]);

	namedWindow("V", WINDOW_GUI_EXPANDED);
	imshow("V", channels[2]);

	waitKey(0);

}