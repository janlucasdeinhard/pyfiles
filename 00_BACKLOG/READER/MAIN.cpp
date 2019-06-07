#include <iostream>
#include <exception>
#include <opencv2\opencv.hpp>

#define COLOR_BLACK 0
#define COLOR_WHITE 255

using namespace std;
using namespace cv;

int disp(Mat,char*,bool);

int main(){
	
	Mat img = imread("..\\..\\..\\TF_data\\READER\\img0.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	disp(img,"Full",true);  
	
	int xframesize = 500;
	int yframesize = 500;
	char name[10];
	
	for(int x=0;x<=img.cols;x+=300){
		for(int y=0;y<=img.rows;y+=300){
			Rect roi(x,y,x+xframesize,y+yframesize);
			Mat subimg = img(roi);
			
			sprintf(name,"Cropped x=%d,y=%d",x,y);
			disp(subimg,name,true);
		}
	}
	
	return 0;
}

int disp(Mat img, char * title, bool hold){
	int retval = 0;
	try{
		namedWindow(title,WINDOW_NORMAL);
		resizeWindow(title,300,500);
		imshow(title,img);
	}catch(...){
		retval = -1;
	}
	if(hold) waitKey(0);
	return 0;
}