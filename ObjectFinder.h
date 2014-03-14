#pragma once

#include <opencv2\core\core.hpp>

class ObjectFinder
{
public:
	ObjectFinder(void);
	virtual ~ObjectFinder(void);

	void setThreshold(float t);
	inline float getThreshold();
	void setHistogram(const cv::MatND& h);
	void setHistogram(const cv::SparseMat& h);
	cv::Mat find(const cv::Mat& image);
	cv::Mat find(const cv::Mat& image, float minValue, float maxValue, int *channels, int dim);

private:

	float hranges[2];
	const float* ranges[3];
	int channels[3];

	float threshold;
	cv::MatND histogram;
	cv::SparseMat shistogram;
	bool isSparse;
};

