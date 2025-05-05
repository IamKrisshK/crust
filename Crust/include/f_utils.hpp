#ifndef F_UTILS_HPP
#define F_UTILS_HPP

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

Mat applyDFT(const Mat& img);
Mat inverseDFT(const Mat& complexImg);
vector<pair<float, float>> autoTuneBands(const Mat& complexImg);
Mat applyBandSuppression(const Mat& complexImg, const vector<pair<float, float>>& bandsToSuppress);

#endif // F_UTILS_HPP
