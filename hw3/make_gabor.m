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


% theta1 = theta(1);
% theta2 = theta(2);
% theta3 = theta(3);
% 
% sigma1 = sigma(1);
% sigma2 = sigma(2);
% sigma3 = sigma(3);
% 
% g1 = zeros(k,k);
% g2 = zeros(k,k);
% g3 = zeros(k,k);
% 
% for x=1:k
%     for y=1:k 
%         x11 = x*cosd(theta1)+y*sind(theta1);
%         x12 = x*cosd(theta2)+y*sind(theta2);
%         x13 = x*cosd(theta3)+y*sind(theta3);
%         
%         y11 = -x*sind(theta1)+y*cosd(theta1);
%         y12 = -x*sind(theta2)+y*cosd(theta2);
%         y13 = -x*sind(theta3)+y*cosd(theta3);
%         
%         g1(x,y) = exp(-(x11^2 + gamma^2 * y11^2/(2 * sigma1^2))) * cosd(2*pi*(x11/lambda)+psi);
%         g2(x,y) = exp(-(x12^2 + gamma^2 * y12^2/(2 * sigma2^2))) * cosd(2*pi*(x12/lambda)+psi);
%         g3(x,y) = exp(-(x13^2 + gamma^2 * y13^2/(2 * sigma3^2))) * cosd(2*pi*(x13/lambda)+psi);
%     end
% end
% 
% g1 = g1/norm(g1);
% g2 = g2/norm(g2);
% g3 = g3/norm(g3);
end

