#include <opencv2/opencv.hpp>
#include <iostream>
#include <io.h>
#include <stdio.h>
#include <direct.h>
#include "facedetection_demo.h"

#pragma comment(lib,"facelib/FaceDetection.lib")
using namespace std;
using namespace cv;


//批量读取图片
void getFiles(string path, vector<string>& files)
{
	//文件句柄  
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int main(int argc, char*argv[]) {

	String rfilePath = "test_images";
	string wfilePath = "test_results/";  //result path
	vector<string> files;
	//读取图片文件
	getFiles(rfilePath, files);
	//读取图片数量
	int size = files.size();
	std::cout << "  -----image_num  is-------  " << size << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::string newpath = files[i];
		int pos1 = files[i].find_first_of('.');
		int pos2 = files[i].find_last_of('\\');
		std::string filename0(files[i].substr(pos2 + 1, pos1 - pos2 - 1));//读取ID
		Mat img = imread(newpath);
		if (img.empty())
		{
			std::cout << "img is empty,please check file path!" << std::endl;
			return -1;
		}
		Mat img_resize;
		Mat img_alig;
		vector<FaceObject> faces;
		int a = 0;
		a = face_detection(img, faces, img_alig, img_resize);
		if (a == -2)
		{
			std::cout << "algorithms  lib decode failed！" << std::endl;
			return -2;
		}
		int face_num = faces.size();
		
		if (faces.size() > 0) {
			std::cout << "image  " << filename0 << "  -----face_num  is-------  " << face_num << std::endl;
			for (int j = 0; j < faces.size(); j++) {
				String wfilePath_1 = wfilePath + "/" + filename0 + "_" + to_string(i) + "_" + ".jpg";
				imwrite(wfilePath_1, img_alig);
				String wfilePath_2 = wfilePath + "/" + filename0 + "_" + to_string(i) + ".jpg";
				imwrite(wfilePath_2, img_resize);
				//imshow("face", img_resize);
				cv::waitKey(10);
			}
		}
		else
		{
			std::cout << "image  " << filename0 << " has no face!" << std::endl;
		}
	}
	std::cout << "all done!" << std::endl;
	return 0;
}