#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    Mat img = imread("C:/Users/19398/Desktop/pictures/多轮廓.jpg");
    if (img.empty()) {
        cout << "could not load image...." << endl;
        return -1;
    }

    //namedWindow("多轮廓图片", WINDOW_FREERATIO);
    //namedWindow("黑白图片", WINDOW_FREERATIO);
    //namedWindow("正方形", WINDOW_FREERATIO);
    //namedWindow("轮廓", WINDOW_FREERATIO);
    //namedWindow("s 二值化", WINDOW_FREERATIO);
    //namedWindow("边界", WINDOW_FREERATIO);
    //namedWindow("开操作", WINDOW_FREERATIO);

    //imshow("多轮廓图片", img);

    Mat gray,binary,contour = Mat::zeros(img.size(),img.type());

    cvtColor(img, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 52, 255, THRESH_BINARY_INV);
    //imshow("黑白图片", binary);

    double Total_Area = 0, Total_Length = 0,Total_Number = 0;
    vector<vector<Point>> contours;
    vector<Point> approx;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); ++i) {
        String text1("Area:"), text2("Length:"),text3("Number:");
        approxPolyDP(contours[i], approx, 0.01 * arcLength(contours[i], true), true);
        if (approx.size() == 4) {
            text1 += to_string((int)contourArea(approx));
            text2 += to_string((int)arcLength(approx,true));
            text3 += to_string((int)(++Total_Number));
            drawContours(img, contours, i, Scalar(0, 0, 255), 2, LINE_AA, hierarchy);
            putText(img, text3, Point(approx[0].x + 2, approx[0].y + 19), FONT_HERSHEY_COMPLEX_SMALL, 1.2, Scalar(108, 96, 244), 1, LINE_AA);
            putText(img, text1, Point(approx[0].x + 2, approx[0].y + 50), FONT_HERSHEY_COMPLEX_SMALL, 1.2, Scalar(108, 96, 244), 1, LINE_AA);
            putText(img, text2, Point(approx[0].x + 2, approx[0].y + 81), FONT_HERSHEY_COMPLEX_SMALL, 1.2, Scalar(108, 96, 244), 1, LINE_AA);
            Total_Area += contourArea(approx);
            Total_Length += arcLength(approx, true);
        }
    }
    imshow("正方形", img);
    cout << endl << endl << endl << endl << endl << endl <<
        "Total Area of Squares = " << Total_Area << endl <<
        "Total Length of Squares = " << Total_Length << endl <<
        "Total Number = " << Total_Number << endl;

    waitKey(0);
    destroyAllWindows();
    return 0;
}