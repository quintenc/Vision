// Demonstratie: gebruik van callibratie matrices 
// - inlezen van een YML-file met de callibratie data van de camera
// - testen van de callibratie waarden door beelden op te nemen met 
//   de camera, het orginele beeld te tonen en het gecallibreerde beeld.
// Opmerking: met een lens met een kleine brandpuntsafstand, b.v. 6 mm
//            is het effect goed te zien.
// Jan Oostindie, dd 30-9-2015
// aangepast door Quinten Ceelen, tijdens Minor Vision & Robotics 2017

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
	// YML-file met callibratie data openen
	FileStorage fs("C:\\Vision\\logi_calibratie.yml", FileStorage::READ);

	// callibratie data ophalen
	Mat intrinsic, distCoeffs;
	fs["intrinsic"] >> intrinsic;
	fs["distCoeffs"] >> distCoeffs;

	// callibratie matrices tonen op het scherm
	cout << "intrinsic matrix: " << intrinsic << endl;
	cout << "distortion coeffs: " << distCoeffs << endl;

	// sluiten van de YML-file
	fs.release();

	/***** callibratie data gebruiken *****/

	// Now that we have the distortion coefficients, we can undistort the images. 
	// Here's a small loop that will do this: 
	Mat imageUndistorted;

	VideoCapture capture = VideoCapture(1);
	Mat image, grayImage, thresheld, add, edge;
	int t1 = 75;
	int t2 = 100;

	while (1)
	{
		capture >> image;
		undistort(image, imageUndistorted, intrinsic, distCoeffs);

		//imshow("original", image);
		//imshow("undistorted", imageUndistorted);

		cvtColor(imageUndistorted, grayImage, CV_BGR2GRAY);
		//imshow("Original", grayImage);

		GaussianBlur(grayImage, grayImage, Size(9, 9), 2, 2);
		add.create(image.size(), image.type());


		waitKey(0);
	}

	waitKey();
	cin.get();
}
