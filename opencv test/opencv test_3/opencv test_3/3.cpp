#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

template<class T>
T max(vector<T> v) {
    T max = v[0];
    auto first = v.begin();
    auto end = v.end();
    while (first != end) {
        if (max < *first)
            max = *first;
        ++first;
    }
    return max;
}

template<class T>
int searchMember(vector<T> v, T member) {
    int index = 0;
    for (; index < v.size(); ++index) {
        if (member == v[index])
            break;
        if (index == v.size() - 1)
            index = -1;
    }
    return index;
}

class Color {
    const cv::Scalar infColorBGR;
    const cv::Scalar supColorBGR;
    const cv::Scalar drawColorBGR;
    const String text1;
    const String text2;
public:
    vector<Rect> Rectangle;
    Color(cv::Scalar inf, cv::Scalar sup, cv::Scalar draw,String s1,String s2):infColorBGR(inf),supColorBGR(sup),drawColorBGR(draw),text1(s1),text2(s2) {  }
    ~Color() {  }
    void ColorScanf(Mat& src, Mat& img,Mat& task1,Mat& task2);
};
Color Color_Yellow(Scalar(24, 43, 46), Scalar(36, 255, 255), Scalar(0, 255, 255), String("yellow"), String("yellow_max"));
Color Color_Red(Scalar(162, 43, 46), Scalar(180, 255, 255), Scalar(0, 0, 255), String("red"), String("red_max"));
Color Color_Blue(Scalar(80, 45, 46), Scalar(153, 255, 255), Scalar(255, 0, 0), String("blue"), String("blue_max"));

void Color::ColorScanf(Mat& src, Mat& img, Mat& task1, Mat& task2) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> approx;
    vector<double> maxArea;
    Mat color;
    maxArea.clear();

    inRange(src, infColorBGR, supColorBGR, color); // 颜色阈值筛选
    Mat rectKernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    morphologyEx(color, color, MORPH_OPEN, rectKernel); // 开操作
    findContours(color, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    
    for (int i = 0; i < contours.size(); ++i) {
        approxPolyDP(contours[i], approx, 0.05 * arcLength(contours[i], true), true);
        Rect rRect = boundingRect(contours[i]);
        if (contourArea(approx) > 3000) { // 面积筛选
            Mat mean_select = (Mat)mean(img(rRect));
            if (mean_select.at<double>(0) + mean_select.at<double>(1) + mean_select.at<double>(2) < 150)
                continue; // 排除黑色干扰
            maxArea.push_back(contourArea(approx));
            rectangle(task1, Point(rRect.x - 5, rRect.y - 5), Point(rRect.x + rRect.width + 5, rRect.y + rRect.height + 5),
                drawColorBGR, 5, LINE_4, 0);
            Rectangle.push_back(rRect);
            putText(task1, text1, Point(rRect.x + 15, rRect.y - 15), FONT_HERSHEY_COMPLEX_SMALL, 2.1, drawColorBGR, 2, LINE_AA);
        }
    }
    // 挑选最大面积
    int index = searchMember(maxArea, max(maxArea));
    rectangle(task2, Point(Rectangle[index].x - 5, Rectangle[index].y - 5),
        Point(Rectangle[index].x + Rectangle[index].width + 5, Rectangle[index].y + Rectangle[index].height + 5),
        drawColorBGR, 5, LINE_4, 0);
    putText(task2, text2, Point(Rectangle[index].x - 2, Rectangle[index].y - 15),
        FONT_HERSHEY_COMPLEX_SMALL, 1.6, drawColorBGR, 2, LINE_AA);
}

int main(int argc, char* argv[]) {
    Mat img = imread("C:/Users/19398/Desktop/pictures/物体.jpg");
    if (img.empty()) {
        cout << "could not load image...." << endl;
        return -1;
    }

    //namedWindow("物体", WINDOW_FREERATIO);
    //namedWindow("阶段1", WINDOW_FREERATIO);
    //namedWindow("阶段2", WINDOW_FREERATIO);

    imshow("物体", img);

    Mat hsv, task1 = img.clone(), task2 = img.clone();
    cvtColor(img, hsv, COLOR_BGR2HSV);

    Color_Red.ColorScanf(hsv, img, task1, task2);
    Color_Blue.ColorScanf(hsv, img, task1, task2);
    Color_Yellow.ColorScanf(hsv, img, task1, task2);

    imshow("阶段1", task1);
    imshow("阶段2", task2);

    waitKey(0);
    destroyAllWindows();
    return 0;
}