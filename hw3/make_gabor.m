function [g1,g2,g3] = make_gabor(img,sigma_arr,theta_arr)
%MAKE_GABOR Creates a bank of 3 Gabor filters
%   Detailed explanation goes here
gamma = 2;
lambda = 0.6;
psi = 0;
pi=180;
[N M] = size(img);

g1 = zeros(N,M);
g2 = zeros(N,M);
g3 = zeros(N,M);

sigma = sigma_arr(1);
theta = theta_arr(1);
for x=1:N
  for y=1:M
      x_theta=img(x,y)*cos(theta)+img(x,y)*sin(theta);
      y_theta=-img(x,y)*sin(theta)+img(x,y)*cos(theta);
      g1(x,y)= exp(-(x_theta.^2/2*sigma^2+ gamma^2*y_theta.^2/2*sigma^2))*cos(2*pi/lambda*x_theta+psi);
  end
end

sigma = sigma_arr(2);
theta = theta_arr(2);
for x=1:N
  for y=1:M
      x_theta=img(x,y)*cos(theta)+img(x,y)*sin(theta);
      y_theta=-img(x,y)*sin(theta)+img(x,y)*cos(theta);
      g2(x,y)= exp(-(x_theta.^2/2*sigma^2+ gamma^2*y_theta.^2/2*sigma^2))*cos(2*pi/lambda*x_theta+psi);
  end
end

sigma = sigma_arr(3);
theta = theta_arr(3);
for x=1:N
  for y=1:M
      x_theta=img(x,y)*cos(theta)+img(x,y)*sin(theta);
      y_theta=-img(x,y)*sin(theta)+img(x,y)*cos(theta);
      g3(x,y)= exp(-(x_theta.^2/2*sigma^2+ gamma^2*y_theta.^2/2*sigma^2))*cos(2*pi/lambda*x_theta+psi);
  end
end

end

