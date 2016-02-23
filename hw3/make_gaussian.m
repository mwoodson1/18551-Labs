function [g_x,g_y] = make_gaussian(k,sigma)
%MAKE_GAUSSIAN Creates a 2D Gaussian filter
%   Detailed explanation goes here
%two 1D Gaussians
g_x=fspecial('gaussian',[1 k],sigma);
g_y=fspecial('gaussian',[k 1],sigma);

end

