#include <iostream>
#include <exception>
#include <opencv2\opencv.hpp>

#define COLOR_BLACK 0
#define COLOR_WHITE 255
#define WB_THRESHOLD 120

using namespace std;
using namespace cv;

int show_image(Mat);
Mat contrast_img(Mat);
Point find_first_black_pixel(Mat);
Mat erase_pixel(Mat,Point);
Mat erase_rectangle(Mat,Point,Point);
Point draw_rectangle_around_letter(Mat,Point);
float calc_datasum(Mat);
Point box_letter(Mat,Point);

int main(){
	
	int patch_size[2] = {350,350};
	int base_letter_size = 100;
	
	Mat img = imread("DATA\\img0.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	if(img.channels()!=1) throw std::exception("Not a grayscale image!");
	if(show_image(img)!=0) throw std::exception("Could not display the image");  
	img = contrast_img(img);
	if(show_image(img)!=0) throw std::exception("Could not display the image");
	
	Mat img_n = img.clone();
	Point p0 = find_first_black_pixel(img_n);
	while(!(p0.x==-1 && p0.y==-1)){
		Point p1 = box_letter(img_n,p0);
		if(p1.x==-1 && p1.y==-1){
			//No letter, misdetection
			//cout<<"Only a pixel"<<endl;
			img_n = erase_pixel(img_n,p0);
		}else{
			//Erase letter
			cout<<"Erase at "<<p1<<endl;
			Mat img_n_cc = img_n.clone();
			rectangle(img_n_cc,p0,p1,Scalar(0,0,255),10,8);
			if(show_image(img_n_cc)!=0) throw std::exception("Could not display the image");
			img_n = erase_rectangle(img_n,p0,p1);
			//img_n_cc = img_n.clone();
			//if(show_image(img_n_cc)!=0) throw std::exception("Could not display the image");
		}
		p0 = find_first_black_pixel(img_n);
	}
	
	return 0;
}

/////////
/////////

Point box_letter(Mat img, Point p0){
	/*
	---------------
	|
	--------  Q1
	|
	|---Q2---------
	|
	--------  Q3
	|
	---------------
	*/
	Mat img_n = img.clone();
	Point p1 = Point(-1,-1);
	int FRAMESIZE = 100;
	int img_sizeY = img.size().height;
	float data_sum_Q1 = (float)10000;
	float data_sum_Q2 = (float)10000;
	float data_sum_Q3 = (float)10000;
	Point pQ1 = Point(-1,-1);
	Point pQ2a = Point(-1,-1);
	Point pQ2b = Point(-1,-1);
	Point pQ3 = Point(-1,-1);
	if(p0.y-FRAMESIZE>=0){
		pQ1 = Point(p0.x+FRAMESIZE,p0.y-FRAMESIZE);
		Mat imgQ1 = img_n(Rect(p0,pQ1));
		data_sum_Q1 = calc_datasum(imgQ1);
	}
	if(p0.y-0.5*FRAMESIZE>=0 && p0.y-0.5*FRAMESIZE<=img_sizeY){
		Point pQ2a = Point(p0.x,p0.y+0.5*FRAMESIZE);
		Point pQ2b = Point(p0.x+FRAMESIZE,p0.y-0.5*FRAMESIZE);
		Mat imgQ2 = img_n(Rect(pQ2a,pQ2b));
		data_sum_Q2 = calc_datasum(imgQ2);
	}
	if(p0.y+FRAMESIZE<=img_sizeY){
		Point pQ3 = Point(p0.x+FRAMESIZE,p0.y+FRAMESIZE);
		Mat imgQ3 = img_n(Rect(p0,pQ3));
		data_sum_Q3 = calc_datasum(imgQ3);
	}
	float data_sum_min = min(data_sum_Q1,min(data_sum_Q2,data_sum_Q3));
	if(data_sum_min==data_sum_Q1){
		return pQ1;
	}else if(data_sum_min==data_sum_Q2){
		return pQ2b;
	}else if(data_sum_min==data_sum_Q3){
		return pQ3;
	}
	return p1;
}

Point draw_rectangle_around_letter(Mat img, Point p0){
	/*
		  |
	   Q2 | Q1
	  ----p0----
	   Q3 | Q4
		  |
	*/
	Point p1 = Point(-1,-1);
	int FRAMESIZERANGE[2] = {50,500};
	int img_sizeX = img.size().width;
	int img_sizeY = img.size().height;
	float data_sum_Q1,data_sum_Q2,data_sum_Q3,data_sum_Q4;
	if(p0.x+FRAMESIZERANGE[0]<img_sizeX && p0.y-FRAMESIZERANGE[0]>=0){
		Mat img_n = img.clone();
		Point pQ1 = Point(p0.x+FRAMESIZERANGE[0],p0.y-FRAMESIZERANGE[0]);
		Mat imgQ1 = img_n(Rect(p0,pQ1));
		data_sum_Q1 = calc_datasum(imgQ1);
	}
	if(p0.x-FRAMESIZERANGE[0]>=0 && p0.y-FRAMESIZERANGE[0]>=0){
		Mat img_n = img.clone();
		Point pQ2 = Point(p0.x-FRAMESIZERANGE[0],p0.y-FRAMESIZERANGE[0]);
		Mat imgQ2 = img_n(Rect(p0,pQ2));
		data_sum_Q2 = calc_datasum(imgQ2);
	}
	if(p0.x-FRAMESIZERANGE[0]>=0 && p0.y+FRAMESIZERANGE[0]<img_sizeY){
		Mat img_n = img.clone();
		Point pQ3 = Point(p0.x-FRAMESIZERANGE[0],p0.y+FRAMESIZERANGE[0]);
		Mat imgQ3 = img_n(Rect(p0,pQ3));
		data_sum_Q3 = calc_datasum(imgQ3);
	}
	if(p0.x+FRAMESIZERANGE[0]<img_sizeX && p0.y+FRAMESIZERANGE[0]<img_sizeY){
		Mat img_n = img.clone();
		Point pQ4 = Point(p0.x+FRAMESIZERANGE[0],p0.y+FRAMESIZERANGE[0]);
		Mat imgQ4 = img_n(Rect(p0,pQ4));
		data_sum_Q4 = calc_datasum(imgQ4);
	}
	float min_data_sum = min(min(data_sum_Q1,data_sum_Q2),min(data_sum_Q3,data_sum_Q4));
	if(min_data_sum==data_sum_Q1){
		//make p1 such that Q1 rectangle is formed
		return p1;
	}
	if(min_data_sum==data_sum_Q2){
		//make p1 such that Q2 rectangle is formed
		return p1;
	}
	if(min_data_sum==data_sum_Q3){
		//make p1 such that Q3 rectangle is formed
		return p1;
	}
	if(min_data_sum==data_sum_Q4){
		//make p1 such that Q4 rectangle is formed
		return p1;
	}
	return p1;
}

float calc_datasum(Mat img){
	float number_of_pixels = (float)(img.size().width*img.size().height);
	float intensity = 0;
	for(int x=0; x<img.size().width; x++){
		for(int y=0; y<img.size().height; y++){
			Scalar col = (int)img.at<uchar>(Point(x,y));
			intensity += (float)col[0];
		}
	}
	intensity /= number_of_pixels;
	return intensity;
}

Mat erase_rectangle(Mat img,Point p0,Point p1){
	Mat img_n = img.clone();
	if(p1.y>p0.y){
		for(int x=p0.x;x<=p1.x;x++){
			for(int y=p0.y;y<=p1.y;y++){
				img_n.at<uchar>(Point(x,y))=(uchar)COLOR_WHITE;
			}
		}
	}else{
		for(int x=p0.x;x<=p1.x;x++){
			for(int y=p0.y;y>=p1.y;y--){
				img_n.at<uchar>(Point(x,y))=(uchar)COLOR_WHITE;
			}
		}
	}
	
	return img_n;
}

Mat erase_pixel(Mat img,Point p){
	Mat img_n = img.clone();
	img_n.at<uchar>(p)=(uchar)COLOR_WHITE;
	return img_n;
}

int show_image(Mat img){
	if(!img.data){
		cout<<"Image file corrupted or missing"<<endl;
		return 1;
	}
	namedWindow("Display",WINDOW_NORMAL);
	imshow("Display",img);
	waitKey(0);
	destroyWindow("Display");
	return 0;
}

Mat contrast_img(Mat img){
	Mat img_c = img.clone();
	int img_sizeX = img_c.size().width;
	int img_sizeY = img_c.size().height;
	for(int ix=0; ix<img_sizeX; ix++){
		for(int iy=0; iy<img_sizeY; iy++){
			if((int)img.at<uchar>(iy,ix)<WB_THRESHOLD){
				img_c.at<uchar>(iy,ix)=(uchar)COLOR_BLACK;
			}else{
				img_c.at<uchar>(iy,ix)=(uchar)COLOR_WHITE;
			}
		}
	}
	return img_c;
}

Point find_first_black_pixel(Mat img){
	int img_sizeX = img.size().width;
	int img_sizeY = img.size().height;
	Point p = Point(-1,-1);
	for(int ix=0; ix<img_sizeX; ix++){
		for(int iy=0; iy<img_sizeY; iy++){
			Scalar col = (int)img.at<uchar>(Point(ix,iy));
			if(col[0]!=COLOR_WHITE){
				p = Point(ix,iy);
				return p;
			}
		}
	}
	return p;
}


