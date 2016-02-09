/* 18551 Digital Communication and Signal Processing  
   Homework 2 : Face Recognition	
   A tutorial on basic matrix operations in openCV
*/

/* This sample code contains basic matrix operations in openCV such as 
	1. Intialising a Matrix
	2. Finding the number of rows and columns in a Matrix
	3. Accessng an element from a Matrix
	4. Accessing a row/column from a Matrix
	5. Transpose of a Matrix
	6. Reshaping a Matrix
	7. Matrix Multiplication
	8. Elementwise Matrix Multiplication
	9. EigenVector Computation of a Matrix
	10. Loading and Displaying an Image
*/


#include <iostream>
#include <opencv.hpp>
#include <string>
#include <fstream>

using namespace cv;

// DisplayMat is an userdefined function which is used to display the elements of a Matrix
void DisplayMat(Mat MatDisp);

int main(){

	float arr[]={1,2,3,4,
			   5,6,7,8,
			   9,10,11,12,
			   13,14,15,16};

	// Initialising the Matrix A with the elements from the array arr 
	Mat MatA = Mat(4,4,CV_32FC1,arr);
	printf("Reading a Matrix from an array \nThe values in the Matrix A are \n");
	DisplayMat(MatA);

	// Finding the number of rows and columns in Matrix A
	int rows = MatA.rows;
	int cols = MatA.cols;
	printf("\nNo. of Rows in Mat A : %d\n",rows);
	printf("no. of Columns in Mat A : %d\n",cols);

	// Accessing an element of Matrix A
	float element = MatA.at<float>(1,2);
	printf("Element of MatA %f\n",element);

	// Accessing a row from the Matrix A
	printf("\nRow 2 of Matrix A is\n");
	Mat MatA_row = MatA.row(1);
	DisplayMat(MatA_row);

	// Finding the transpose of Matrix A
	Mat MatA_transpose;
	transpose(MatA,MatA_transpose);
	printf("\nTranspose of the Matrix A \n");
	DisplayMat(MatA_transpose);
	
	// Reshaping the Matrix A 
	// Format : Mat.reshape(int channel_number,int number_rows)
	// Channel number for grayscale images will be 1
	Mat MatA_reshape = MatA.reshape(1,2);
	printf("\nReshaping the Matrix A \n");
	DisplayMat(MatA_reshape);

	// Matrix Multiplication
	Mat MatA_mul = MatA*MatA;
	printf("\nMultiplication of Matrix A with itself \n");
	DisplayMat(MatA_mul);

	// Elementwise Matrix Multiplication
	Mat MatA_elem_mul;
	printf("\nElementwise Multiplication of Matrix A with itself \n");
	multiply(MatA,MatA,MatA_elem_mul);
	DisplayMat(MatA_elem_mul);

	// Finding EigenVectors of Matrix A
	// Each row will contain a eigenvector of Matrix A
	printf("\nThe EigenVectors of Matrix A are \n");
	Mat EigenValues,EigenVectors;
	eigen(MatA,1,EigenValues,EigenVectors);
	DisplayMat(EigenVectors);

	printf("\nEnter a character to read and display an image\n");
	getchar();
	
	/* Loading and Displaying an image :
	   Incase Visual Studio doesn't support the following code, you can use the uncommented version :
			 Mat MatImage = imread("Class101.jpg");
			 imshow("Read Image",MatImage);
			 waitKey();
			 */
	Mat MatImage = cvLoadImage("Class101.jpg");
	IplImage Image = MatImage;
	cvNamedWindow( "Read Image", CV_WINDOW_AUTOSIZE );
	cvShowImage("Read Image",&Image);
	waitKey();

	getchar();
	return 0;

}

void DisplayMat(Mat MatDisp){
	for (int i=0; i<MatDisp.rows; i++){
		for (int j=0; j<MatDisp.cols; j++){
			printf("%f ",MatDisp.at<float>(i,j));
		}
		printf("\n");
	}
}
