
#include "ObjectFinder.h"
#include "Histogram1D.h"
#include "ColorHistogram.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	string targetWinName = "Target Image";
	string targetHistWinName = "Target Histogram";
	string screenShotWinName = "Screen Shot";
	string backprojectionResultsWinName = "Backprojection Result";
	
	string targetFile = "screen_shot_target.png";
	string screenShotFile = "screen_shot.png";
	
	// Load screen shot
	cv::Mat screenShot = cv::imread(screenShotFile, CV_LOAD_IMAGE_COLOR);
	
	// Load target image
	cv::Mat target = cv::imread(targetFile, CV_LOAD_IMAGE_COLOR);
	
	if (!screenShot.data || !target.data )
	{
		cerr << "Failed to load image: " << screenShot << " or " << target << endl;
		return -1;
	}

	// Display target window image
	cv::namedWindow(targetWinName);
	cv::imshow(targetWinName, target);

	// Get the Hue histogram
	int minSat = 65;
	ColorHistogram hc;
	cv::Mat colorHist = hc.getHueHistogram(target); //, minSat);

	ObjectFinder finder;
	finder.setHistogram(colorHist);
	finder.setThreshold(0.2f);

	// Convert to HSV space
	cv::Mat hsv;
	cv::cvtColor(screenShot, hsv, CV_BGR2HSV);

	// Split the image
	vector<cv::Mat> vHSV;
	cv::split(hsv, vHSV);

	// Eliminate pixels with low saturation
	cv::threshold(vHSV[1], vHSV[1], minSat, 255, cv::THRESH_BINARY);
	cv::namedWindow("Saturation Threshold with minSat");
	cv::imshow("Saturation Threshold with minSat", vHSV[1]);

	// Get back-projection of hue histogram
	int ch[1] = {0};
	cv::Mat result = finder.find(hsv, 0.0f, 180.0f, ch, 1);

	cv::namedWindow("Result Hue Back-projection");
	cv::imshow("Result Hue Back-projection", result);

	// Eliminate low saturation pixels
	cv::bitwise_and(result, vHSV[1], result);
	cv::namedWindow("Result Hue and");
	cv::imshow("Result Hue and", result);

	// Get back-projection of hue histogram
	finder.setThreshold(-1.0f);
	result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
	cv::bitwise_and(result, vHSV[1], result);
	cv::namedWindow("Result Hue and Raw");
	cv::imshow("Result Hue and Raw", result);

	cv::Rect rect(cv::Point(screenShot.rows/2,screenShot.cols/2),target.size());
	cv::rectangle(screenShot, rect, cv::Scalar(0,0,255));

	cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER, 10, 0.01);
	cout << "meanshift = " << cv::meanShift(result, rect, criteria) << endl;

	cv::rectangle(screenShot, rect, cv::Scalar(0,255,0));

	cv::imshow(screenShotWinName, screenShot);

	cv::waitKey(0);

	return 0;
}