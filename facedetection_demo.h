#pragma once
#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;

struct FaceObject {
	cv::Rect_<float> rect;
	float prob;
	Point landmark[5];
};

struct Anchor {
	float cx;
	float cy;
	float s_kx;
	float s_ky;
};

#ifdef NOFACEDETECTION_EXPORTS
#define FACEDETECTION_API __declspec(dllexport)
#else
#define FACEDETECTION_API __declspec(dllimport)
#endif


FACEDETECTION_API int face_detection(cv::Mat img, vector<FaceObject>  &faces, cv::Mat &imgalig, cv::Mat &cvimg);
