// Kras detecteren met Canny
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

	// variabelen definieren
	Mat image, imageCanny, edges;
	int ratio = 3;						// ratio tussen low en high thresh
	int kernel_size = 3;				// grootte van sobel kernel
	int lowThresh = 100;				// onderwaarde van 100
	int highThresh = lowThresh * ratio; // bovenwaarde 

	namedWindow("Original", WINDOW_FREERATIO);
	namedWindow("Canny", WINDOW_AUTOSIZE);

	///afbeelding inladen
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cout << "Imagefile: " << argv[1] << " met succes geopend." << endl;
	imshow("Original", image);

	//nieuwe afbeelding maken met grootte en type van begin afbeelding
	imageCanny.create(image.size(), image.type());

	// blur uitvoeren op begin afbeelding, zodat detailering wat weg is.
	blur(image, edges, Size(3, 3));

	// canny operatie
	Canny(edges, edges, lowThresh, highThresh, kernel_size);
	// afbeelding welke gebruikt gaat worden voor Canny image volledig zwart maken
	imageCanny = Scalar::all(0);

	// canny resultaat kopieren naar zwarte afbeelding
	image.copyTo(imageCanny, edges);

	// resultaat van operaties weergeven
	imshow("Canny", imageCanny);

	waitKey(0);
}
