#include "fourier_utils.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace cv;

Mat applyDFT(const Mat& img) {
   
    Mat floatImg;
    img.convertTo(floatImg, CV_32F);
   
    Mat planes[] = {Mat::zeros(img.size(), CV_32F), Mat::zeros(img.size(), CV_32F)};
    merge(planes, 2, floatImg);
   
    Mat complexImg;
    dft(floatImg, complexImg);
    return complexImg;
}

Mat inverseDFT(const Mat& complexImg) {
   
    Mat inverse;
    idft(complexImg, inverse);
    split(inverse, planes);

    Mat magnitude = planes[0];
    normalize(magnitude, magnitude, 0, 255, NORM_MINMAX);
    return magnitude;
}

vector<pair<float, float>> autoTuneBands(const Mat& complexImg) {
   
    vector<pair<float, float>> bandList;

   
   
    for (int u = 0; u < complexImg.rows; u++) {
        for (int v = 0; v < complexImg.cols; v++) {
            float magnitude = sqrt(pow(complexImg.at<Vec2f>(u, v)[0], 2) + pow(complexImg.at<Vec2f>(u, v)[1], 2));
            float angle = atan2(complexImg.at<Vec2f>(u, v)[1], complexImg.at<Vec2f>(u, v)[0]);
            bandList.push_back({magnitude, angle});
        }
    }

   
    sort(bandList.begin(), bandList.end(), [](const pair<float, float>& a, const pair<float, float>& b) {
        return a.first > b.first;
    });

    return bandList;
}

Mat applyBandSuppression(const Mat& complexImg, const vector<pair<float, float>>& bandsToSuppress) {
   
    Mat modifiedImg = complexImg.clone();

   
   
    int N = bandsToSuppress.size();
    for (int i = 0; i < N / 10; ++i) {
        int u = int(bandsToSuppress[i].second);
        int v = int(bandsToSuppress[i].first); 
        modifiedImg.at<Vec2f>(u, v)[0] = 0; 
        modifiedImg.at<Vec2f>(u, v)[1] = 0; 
    }

    return modifiedImg;
}
