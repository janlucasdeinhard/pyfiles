#include <iostream>
#include <exception>
#include <opencv2\opencv.hpp>

#include "opennn.h"
#include "data_set.h"

using namespace std;
using namespace cv;

int main(){
	
	printf("\nInitializing Data Set and Neural Net...\n");
	
	DataSet data_set;
	data_set.set_data_file_name("DATA\\dataset.dat");
	data_set.set_separator("Comma");
	data_set.load_data();
	
	printf(data_set);
	
	printf("\nDone!\n");
	return 0;
	
}
