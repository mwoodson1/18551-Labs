#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

void createGabKernel(double gaborKernel[][5],double sig, double th)
{
    int ks = 5;
    float pi = M_PI;
    int hks = (ks-1)/2;
    double theta = th*pi/180;
    double psi = 0*pi/180;
    double del = 2.0/(ks-1);
    double lmbd = 0.6;
    double sigma = sig/ks;
    double x_theta;
    double y_theta;
    for (int y=-hks; y<=hks; y++)
    {
        for (int x=-hks; x<=hks; x++)
        {
            x_theta = x*del*cos(theta)+y*del*sin(theta);
            y_theta = -x*del*sin(theta)+y*del*cos(theta);
            gaborKernel[hks+y][hks+x] = (double)exp(-0.5*(pow(x_theta,2)+pow(y_theta,2))/pow(sigma,2))* cos(2*pi*x_theta/lmbd + psi);
        }
    }
}

void createFilter(double gKernel[][5])
{
    // set standard deviation to 1.0
    double sigma = 3.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    double sum = 0.0;

    // generate 5x5 kernel
    for (int x = -2; x <= 2; x++)
    {
        for(int y = -2; y <= 2; y++)
        {
            r = sqrt(x*x + y*y);
            gKernel[x + 2][y + 2] = (exp(-(r*r)/s))/(M_PI * s);
            sum += gKernel[x + 2][y + 2];
        }
    }

    /*/ normalize the Kernel
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            gKernel[i][j] /= sum;
    */
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

int main(int argc, char** argv)
{
    //Read in the image
    if( argc != 2){
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], 0);   // Read the file

    if(! image.data ){
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    //Create filter bank
    double gKernel[5][5];
    createFilter(gKernel);
    double logKernel[5][5] =
    {
      {0.0448,0.0468,0.0564,0.0468,0.0448},
      {0.0468,0.3167,0.7146,0.3167,0.0468},
      {0.0564,0.7146,-4.9048,0.7146,0.0564},
      {0.0468,0.3167,0.7146,0.3167,0.0468},
      {0.0448,0.0468,0.0564,0.0468,0.0448}
    };
    double gaborKernel1[5][5];
    double gaborKernel2[5][5];
    double gaborKernel3[5][5];
    double sig = 1.0;
    double theta1 = 30;
    double theta2 = 45;
    double theta3 = 60;
    createGabKernel(gaborKernel1, sig, theta1);
    createGabKernel(gaborKernel2, sig, theta2);
    createGabKernel(gaborKernel3, sig, theta3);
    Mat gKern = getGaussianKernel(5,3.0,CV_64F);
    Mat lKern = Mat(5,5,CV_64F,logKernel);
    Mat gabKern1 = getGaborKernel(Size(5,5),1.0,30.0,0.6,2.0,0.0);//Mat(5,5,CV_64F,gaborKernel1);
    Mat gabKern2 = getGaborKernel(Size(5,5),1.0,45.0,0.6,2.0,0.0);//Mat(5,5,CV_64F,gaborKernel2);
    Mat gabKern3 = getGaborKernel(Size(5,5),1.0,60.0,0.6,2.0,0.0);//Mat(5,5,CV_64F,gaborKernel3);

    //Get filter reponses
    Mat f1,f2,f3,f4,f5;
    image.convertTo(image,CV_64F);
    GaussianBlur(image, f1, Size(5,5),3.0,3.0,BORDER_DEFAULT);//CV_64F , gKern, Point(-1,-1), 0, BORDER_DEFAULT );
    filter2D(image, f2, CV_64F , lKern, Point(-1,-1), 0, BORDER_DEFAULT );
    filter2D(image, f3, CV_64F , gabKern1, Point(-1,-1), 0, BORDER_DEFAULT );
    filter2D(image, f4, CV_64F , gabKern2, Point(-1,-1), 0, BORDER_DEFAULT );
    filter2D(image, f5, CV_64F , gabKern3, Point(-1,-1), 0, BORDER_DEFAULT );

    //Concatenate features
    Mat f12,f123,f1234,features;
    hconcat(f1.reshape(1,1),f2.reshape(1,1),f12);
    hconcat(f12,f3.reshape(1,1),f123);
    hconcat(f123,f4.reshape(1,1),f1234);
    hconcat(f1234,f5.reshape(1,1),features);

    //Read in hyperplane and bias
    ifstream inpStream;
    inpStream.open("svm_model");

    //Dot product and add bias
    double bias;
    double hyperplane[27200];
    double output = 0.0;
    string line;
    getline(inpStream,line);
    inpStream >> bias;
    getline(inpStream,line);
    getline(inpStream,line);
    getline(inpStream,line);
    for(int i=0;i<27200;i++){
      inpStream >> hyperplane[i];
      output += features.at<double>(i)*hyperplane[i];
    }

    //Print class
    if(output+bias >= 0)
      cout << "Female" << endl;
    else
      cout << "Male" << endl;
}
