#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

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

    // normalize the Kernel
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            gKernel[i][j] /= sum;

}

int main()
{
    //Read in the image
    //TODO

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

    //Get filter reponses

    //Dot product and add bias

    //Print class
}
