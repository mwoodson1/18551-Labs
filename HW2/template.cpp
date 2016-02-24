/*** 18551 Homework 2 Starter Code ******/

// Please add your own comments to the code before you submit 

#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <dirent.h>

using namespace cv;
using namespace std;

void IPCAtrain(char *trainFolderPath, int numTrain);
int IPCAtest(char *imgName);

int main(){
	IPCAtrain(" ", 8);

	char * fileName = (char *)malloc(40);
	fileName = "411";
	int result = IPCAtest(fileName);
	printf("The class is %d\n",result);

	return 0;
}
void IPCAtrain(char* trainFolderPath, int numTrain){
	/* trainFolderPath is the path to the folder containing the training images
	   numTrain is the number of training images per class */

	// Run a loop to iterate over classes (people)
	
	for(int i = 1;i < 5;i++){
		//Run a loop to iterate over images of same person and generate the data matrix for the class 
		//i.e. a matrix in which each column is a vectorized version of the face matrix under consideration

		// Subtract the mean vector from each vector of the data matrix
		Mat A = Mat(128,128,CV_32FC1);
		Mat E = Mat(100,100, CV_32F);
		for(int j = 1; j <= numTrain; j++){
			string filename = "Train_Files/class";
			filename.append(to_string(i));
			filename.append("0");
			filename.append(to_string(j));
			filename.append(".jpg");

		  	printf("%s\n", filename.c_str());
			Mat B(A.rows,A.cols, A.type());
			E = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);

			E.convertTo(B, CV_32FC1);
			A += B;
		}

		Mat mean,EigenValues,EigenVectors,Cov,mean_2;
		mean = A / 8;
        eigen(A,EigenValues,EigenVectors);

		Mat findMeanVec = Mat(1, mean.cols, CV_32F);
		Mat F = Mat(128, 128, CV_32F);
		mean.convertTo(F, CV_32F);	
		for(int k = 0; k < mean.cols; k++){
			float findMean = 0;

			for(int l = 0; l < F.rows; l++){
				findMean += F.at<float>(l, k);
			}
			findMean = findMean / mean.rows;
			findMeanVec.at<float>(0, k) = findMean;

			for(int l = 0; l < F.rows; l++){
				F.at<float>(l, k) -= findMean;
			}
			
		}

		string cov_file = "eigen";
		string mean_file = "mean";
		cov_file.append(to_string(i)).append(".txt");
		mean_file.append(to_string(i)).append(".txt");
	
		// Compute the covariance matrix and generate the eigen vectors using the Gram trick
		calcCovarMatrix(F, Cov, mean_2, CV_COVAR_NORMAL | CV_COVAR_ROWS);
		eigen(Cov, EigenValues, EigenVectors);

		// Store the eigen vectors and the mean vector in a file, which will be accessed by the IPCAtest function
		cv::FileStorage file(mean_file, cv::FileStorage::WRITE);
		cv::FileStorage file2(cov_file, cv::FileStorage::WRITE);
		file << "mean" << findMeanVec; 
		file2 << "eigen" << EigenVectors;
		file.release();
		
	}
	return;
}

int IPCAtest(char *imgName)
{
	/* imgName is the path and filename of the test image */
	// Read the eigen vectors and means for each class from file
	cv::FileStorage e1("eigen1.txt", cv::FileStorage::READ);
	cv::FileStorage e2("eigen2.txt", cv::FileStorage::READ);
	cv::FileStorage e3("eigen3.txt", cv::FileStorage::READ);
	cv::FileStorage e4("eigen4.txt", cv::FileStorage::READ);

		
	cv::FileStorage m1("mean1.txt", cv::FileStorage::READ);
	cv::FileStorage m2("mean2.txt", cv::FileStorage::READ);
	cv::FileStorage m3("mean3.txt", cv::FileStorage::READ);
	cv::FileStorage m4("mean4.txt", cv::FileStorage::READ);

	cv::FileStorage t1(imgName, cv::FileStorage::READ);

	Mat eigen1,eigen2,eigen3,eigen4;
	Mat mean1, mean2, mean3, mean4;	
	Mat t;

	string filename = "Test_Files/class";
	filename.append(imgName);
	filename.append(".jpg");
	printf("%s\n", filename.c_str());

	t = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
	e1["eigen"] >> eigen1; 
	e2["eigen"] >> eigen2; 
	e3["eigen"] >> eigen3; 
	e4["eigen"] >> eigen4;
	m1["mean"] >> mean1;
	m2["mean"] >> mean2;
	m3["mean"] >> mean3;
	m4["mean"] >> mean4;

	e1.release();
	e2.release();
	e3.release();
	e4.release();
	m1.release();
	m2.release();
	m3.release();
	m4.release();
	
	// Compute the reconstruction error between the input test image and the reconstructed image
	// You can use euclidean distance (or any other appropriate distance measure)
	Mat A,EigenValues,EigenVectors;
	t.convertTo(A, CV_32F);	
    eigen(A,EigenValues,EigenVectors);
	float sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
	for(int i = 0; i < EigenVectors.rows; i++){
		sum1 += (eigen1.at<float>(i, 0) - EigenVectors.at<float>(i,0)) * (eigen1.at<float>(i,0) - EigenVectors.at<float>(i,0));
		sum2 += (eigen2.at<float>(i,0) - EigenVectors.at<float>(i,0)) * (eigen2.at<float>(i,0) - EigenVectors.at<float>(i,0));
		sum3 += (eigen3.at<float>(i,0) - EigenVectors.at<float>(i,0)) * (eigen3.at<float>(i,0) - EigenVectors.at<float>(i,0));
		sum4 += (eigen4.at<float>(i,0) - EigenVectors.at<float>(i,0)) * (eigen4.at<float>(i,0) - EigenVectors.at<float>(i,0));
	}	

	// return the class label corresponding to the eigen space which showed minimum reconstruction error 
	if(sum1 < sum2 && sum1 < sum3 && sum1 < sum4)
		return 1;
	else if(sum2 < sum1 && sum2 < sum3 && sum2 < sum4)
		return 2;	
	else if(sum3 < sum1 && sum3 < sum2 && sum3 < sum4)
		return 3;
	else 
		return 4;
	return 0;
}