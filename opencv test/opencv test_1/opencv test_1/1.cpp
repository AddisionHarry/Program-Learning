#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    Mat img = imread("C:/Users/19398/Desktop/pictures/白色十字.jpg");
    if (img.empty()) {
        cout << "could not load image...." << endl;
        return -1;
    }

    //namedWindow("白色十字图片", WINDOW_FREERATIO);
    //namedWindow("h", WINDOW_FREERATIO);
    //namedWindow("s", WINDOW_FREERATIO);
    //namedWindow("v", WINDOW_FREERATIO);
    //namedWindow("s 二值化", WINDOW_FREERATIO);
    namedWindow("边界", WINDOW_FREERATIO);
    //namedWindow("开操作", WINDOW_FREERATIO);

    //imshow("白色十字图片", img);

    Mat hsv, binary ,result;
    cvtColor(img, hsv, COLOR_BGR2HSV);
    vector<Mat> mv;
    split(hsv, mv);
    //imshow("h", mv[0]);
    //imshow("s", mv[1]);
    //imshow("v", mv[2]);

    threshold(mv[1], binary, 63, 255, THRESH_BINARY_INV);
    //imshow("s 二值化", binary);

    Mat rectKernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, - 1));
    morphologyEx(binary, result, MORPH_OPEN, rectKernel);
    //imshow("开操作", result);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;
    findContours(result, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //approxPolyDP(contours[1], approx, 3.1, true);
    //for (int i = 0; i < approx.size() - 1; ++i) {
    //    line(img, approx[i], approx[i + 1], Scalar(0, 0, 255), 2, LINE_AA, 0);
    //}
    //line(img, approx[0], approx[approx.size() - 1], Scalar(0, 0, 255), 2, LINE_AA, 0);
    approxPolyDP(contours[1], approx, 3.1, true);
    drawContours(img, contours, 1, Scalar(0, 0, 255), 2, LINE_AA, hierarchy);
    imshow("边界", img);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
