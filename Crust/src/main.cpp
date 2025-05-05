#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

Mat applyDFT(const Mat& img);
Mat inverseDFT(const Mat& complexImg);
Mat applyBandSuppression(const Mat& complexImg, const vector<pair<float, float>>& bandsToSuppress);

vector<pair<float, float>> autoTuneBands(const Mat& complexImg);

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: ./deterrent <image_path>" << endl;
        return -1;
    }

    string imagePath = argv[1];
    Mat img = imread(imagePath, IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Image not found or invalid." << endl;
        return -1;
    }

    resize(img, img, Size(512, 512));
    Mat complexImg = applyDFT(img);
    vector<pair<float, float>> bandsToSuppress = autoTuneBands(complexImg);
    Mat suppressedImg = applyBandSuppression(complexImg, bandsToSuppress);
    Mat result = inverseDFT(suppressedImg);
    imwrite("filtered_output.png", result);
    imshow("Original", img);
    imshow("Filtered", result);
    waitKey(0);
    return 0;
}
