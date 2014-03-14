#pragma once

#include <opencv2/core/core.hpp>

class Histogram1D
{
public:
	Histogram1D(void);
	virtual ~Histogram1D(void);

	void setChannel(int c);
	inline int getChannel();
	void setRange(float minValue, float maxValue);
	inline float getMinValue();
	inline float getMaxValue();
	void setNBins(int nbins);
	inline int getNBins();
	cv::MatND getHistogram(const cv::Mat &image);
	cv::Mat getHistogramImage(const cv::Mat &image);
	cv::Mat equalize(const cv::Mat &image);
	cv::Mat stretch(const cv::Mat &image, int minValue=0);
	cv::Mat applyLookUp(const cv::Mat& image, const cv::MatND& lookup);

private:

	int histSize[1];
	float hranges[2];
	const float* ranges[1];
	int channels[1];
};

