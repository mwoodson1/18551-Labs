%Set filter parameters
k = 5;
sigma_g = 3;
sigma = [1 1 1];
theta = [30 45 60];

%Create Filters
[g_x,g_y] = make_gaussian(k,sigma_g);
lap = make_laplacian(0.2);

img=im2double(imread('04201d182_1.jp2'));
%Go through training images and convolve with filters
img_X=imfilter(img,g_x);
img_XY=imfilter(img_X,g_y);  

%Apply Laplacian filter
lap_filtered = imfilter(img,lap);

%Apply Gabor filter
[g1,g2,g3] = make_gabor(img,sigma,theta);
g1_filt = g1;
g2_filt = g2;
g3_filt = g3;

%Plot example
subplot(2,3,1);
imshow(img)
subplot(2,3,2);
imshow(img_XY);
subplot(2,3,3);
imshow(lap_filtered);
subplot(2,3,4);
imshow(g1_filt);
subplot(2,3,5);
imshow(g2_filt);
subplot(2,3,6);
imshow(g3_filt);

%Loop through male images
files = dir('HW3Images/male/*');
X_male = zeros(51,5*5440);
i=1;
for file = files'
    if(file.name=='.')
        continue
    end
    img = im2double(imread(file.name));
    f1 = reshape(imfilter(imfilter(img,g_x),g_y),1,[]);
    f2 = reshape(imfilter(img,lap),1,[]);
    [g1,g2,g3] = make_gabor(img,sigma,theta);
    f3 = reshape(g1,1,[]);
    f4 = reshape(g2,1,[]);
    f5 = reshape(g3,1,[]);
    
    X_male(i,:) = [f1 f2 f3 f4 f5];
    i = i+1;
end

%Loop through female images
files = dir('HW3Images/female/*');
X_female = zeros(51,5*5440);
i=1;
for file = files'
    if(file.name=='.')
        continue
    end
    img = im2double(imread(file.name));
    f1 = reshape(imfilter(imfilter(img,g_x),g_y),1,[]);
    f2 = reshape(imfilter(img,lap),1,[]);
    [g1,g2,g3] = make_gabor(img,sigma,theta);
    f3 = reshape(g1,1,[]);
    f4 = reshape(g2,1,[]);
    f5 = reshape(g3,1,[]);
    
    X_female(i,:) = [f1 f2 f3 f4 f5];
    i = i+1;
end

%Train SVM classifier
X = [X_male;X_female];
y = zeros(1,size(X,1));
y(51:end) = 1;

model = fitcsvm(X,y,'KernelFunction','rbf','Standardize',true);

printHyperplane('svm_model',model);

%Test classifier on test images
img=im2double(imread('04201d182_1.jp2'));

f1 = reshape(imfilter(imfilter(img,g_x),g_y),1,[]);
f2 = reshape(imfilter(img,lap),1,[]);
[g1,g2,g3] = make_gabor(img,sigma,theta);
f3 = reshape(g1,1,[]);
f4 = reshape(g2,1,[]);
f5 = reshape(g3,1,[]);

newX = [f1 f2 f3 f4 f5];

[label, score] = predict(model,newX)