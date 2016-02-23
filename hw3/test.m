img=im2double(imread('cameraman.tif'));

yourFilterSize=[3 5] %3 rows, 5 columns, can be anything



%applying 1D gaussian in X-direction to the original image


%verifying that the result is correct
g_xy=fspecial('gaussian',yourFilterSize);
img_XY2D=imfilter(img,g_xy);
max(max(abs(img_XY-img_XY2D)))  %this should be very small, 
                                %of the order of machine precision
                                %for the result to be correct