// ImageRotation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main()
{
    string image_loc;
    float angle;

    cout << "Enter image location: ";
    cin >> image_loc;
    Mat image = imread(image_loc);

    if (image.empty())
    {
        cout << "ERROR!!!";
        return -1;
    }
    cout << "\nFor clockwise, angle should be positive & for anti clockwise, angle should be negative\n\n";
    cout << "Enter the angle: ";
    cin >> angle;

    string O_Image = "Original Image";
    namedWindow(O_Image, 0);
    imshow(O_Image, image);
    waitKey(0);

    string R_Image = "Rotated Image";
    namedWindow(R_Image, 0);

    int Image_Height = image.rows / 2;
    int Image_Width = image.cols / 2;

    Mat rot_Image;

    Mat rot = getRotationMatrix2D(Point(Image_Width, Image_Height), (-angle), 1);

    Rect2f bbox = RotatedRect(Point2f(), image.size(),(-angle)).boundingRect2f();
    rot.at<double>(0, 2) += bbox.width / 2.0 - image.cols / 2.0;
    rot.at<double>(1, 2) += bbox.height / 2.0 - image.rows / 2.0; 
    warpAffine(image, rot_Image, rot, bbox.size());
    
    imshow(R_Image, rot_Image);
    waitKey(0);
    destroyWindow(O_Image);
    destroyWindow(R_Image);
    return 0;  
}

