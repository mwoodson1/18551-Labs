%Set filter parameters
k = 5;
sigma_g = 3;
sigma = [3 3 3];
wavelength = 20;
theta = [0 45 90];

%Create Filters
[g_x,g_y] = make_gaussian(k,sigma_g);
lap = make_laplacian(0.2);
[g1,g2,g3] = make_gabor(sigma,theta,k);

img=im2double(imread('cameraman.tif'));
%Go through training images and convolve with filters
img_X=imfilter(img,g_x);
img_XY=imfilter(img_X,g_y);  %DONE

%Train SVM classifier

%Test classifier on test images
clear;
clc;