#include <iostream>
#include <exception>
#include <opencv2\opencv.hpp>

#define COLOR_BLACK 0
#define COLOR_WHITE 255

using namespace std;
using namespace cv;

int main(){
	
	Mat img = imread("data\\train-jpg\\train_1.jpg",0);
	
	try{
		namedWindow("Image",WINDOW_NORMAL);
		resizeWindow("Image",300,500);
		imshow("Image",img);
	}catch(...){
		throw "Couldn't load image";
	}
	waitKey(0);
	
	return 0;
}
