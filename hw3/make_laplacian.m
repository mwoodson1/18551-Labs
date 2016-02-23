function [lap] = make_laplacian(alpha)
%MAKE_LOG Creates a Laplacian of Gaussian filter
%   Detailed explanation goes here
lap = fspecial('laplacian', alpha);

end

