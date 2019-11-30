#include <iostream>
#include <exception>
#include <stdarg.h>
#include <opencv2\opencv.hpp>

#define COLOR_BLACK 0
#define COLOR_WHITE 255

#define BUFFERSIZE 5

using namespace std;
using namespace cv;

// Declare functions
list<Mat> read_batch(int);
void show_batch(list<Mat>);

// Main function implementation
int main(){
	for(int cursor=1;cursor<=5*BUFFERSIZE;cursor+=BUFFERSIZE){
		list<Mat> imlist = read_batch(cursor);
		show_batch(imlist);
		waitKey(0);		
	}
	return 0;
}

// Implement functions

list<Mat> read_batch(int cursor){
	string rootpath_pre,rootpath_post;
	list<Mat> imlist = {};
	for(int ctr=0;ctr<BUFFERSIZE;ctr++){
		rootpath_pre = "..\\..\\TF_data\\SAT\\train-jpg\\train_";
		rootpath_post = ".jpg";
		
		Mat c_img = imread(rootpath_pre.append(to_string(cursor+ctr)).append(rootpath_post),1);
		imlist.push_back(c_img);
	}
	return imlist;
}

void show_batch(list<Mat> imlist){
	list<Mat>::iterator it;
	string window_name;
	int ctr = 0;
	for(it=imlist.begin();it!=imlist.end();it++){
		Mat c_img = *it;
		
		window_name = "Image";
		window_name.append(to_string(ctr));
		namedWindow(window_name,WINDOW_NORMAL);
		resizeWindow(window_name,300,500);
		imshow(window_name,c_img);
		
		ctr ++;
	}
	return;
}
