#pragma once

#include <opencv2\core\core.hpp>

class ColorHistogram
{
public:
	ColorHistogram(void);
	virtual ~ColorHistogram(void);

	cv::MatND getHistogram(const cv::Mat &image);
	cv::SparseMat getSparseHistogram(const cv::Mat &image);
	cv::MatND getabHistogram(const cv::Mat &image);
	cv::MatND getHueHistogram(const cv::Mat &image);
	cv::Mat colorReduce(const cv::Mat &image, int div=64);

private:
	int histSize[3];
	float hranges[2];
	const float* ranges[3];
	int channels[3];
};

