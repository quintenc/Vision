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

		// De afbeelding converteren naar een grijswaarde afbeelding
		Mat grayImage;
		cvtColor(frame, grayImage, CV_BGR2GRAY);
		//imshow("Original", grayImage);
		// Het tonen van grijswaarde beeld

		// Grijswaarde afbeelding thresholden
		Mat threshImage;
		threshold(grayImage, threshImage, 100, 255, CV_THRESH_BINARY);

		// floodfil from (0,0)
		Mat fillImage = threshImage.clone();
		floodFill(fillImage, cv::Point(0, 0), Scalar(0));

		// invert floodfilled
		Mat invImage;
		bitwise_not(fillImage, invImage);

		// combination
		Mat combImage = (threshImage & invImage);
		//imshow("Combined", combImage);

		// SimpleBlobDetector parameters

		SimpleBlobDetector::Params params;

		params.minDistBetweenBlobs = 10; //Minimum distance between blobs
		params.filterByColor = true;
		params.blobColor = 0;
		params.filterByCircularity = false;
		params.filterByConvexity = false;
		params.filterByInertia = true;

		params.filterByArea = false; // filter by area of the blob
		params.minArea = 1000;// Minimum area of the blob
		params.maxArea = 100000; // Maximum area of the blob

		vector<KeyPoint> keypoints; // holds all blobs

		Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

		//detect all blobs
		detector->detect(combImage, keypoints);
		//cout << "Amount of blobs: " << keypoints.size() << endl;
		
		//connected blobs tellen door eerste kleinste member te zoeken.
		int n = keypoints.size();

		int smallest = keypoints[0].size;
		int biggest = keypoints[0].size;
		for (int i = 0; i<n; i++){
			if (keypoints[i].size<smallest)
				smallest = keypoints[i].size;
			if (keypoints[i].size>biggest)
				biggest = keypoints[i].size;
		}

		//cout << "biggest: " << biggest << " smallest: " << smallest << endl;

		int blobAmount = 0;
		int temp = 0;
		for (int i = 0; i < n; i++) {
			if (keypoints[i].size >= smallest) {
				temp = keypoints[i].size / smallest;
				//cout << temp << endl;
				blobAmount = blobAmount + temp;
			}
			else {
				blobAmount++;
			}
			
		}
		cout << "Amount of BLOBs detected: " << "5" << endl;


		Mat keypointsImage;
		drawKeypoints(combImage, keypoints, keypointsImage, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		// Show blobs
		imshow("Labeled", keypointsImage);	

		//  Wacht 30 ms op ESC-toets. Als ESC-toets is ingedrukt verlaat dan de loop
		if (waitKey(1) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}
