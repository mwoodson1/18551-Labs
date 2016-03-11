import matplotlib
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import cv2

def denoiseSilhouette(img):
	kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(7,7))
	erosion = cv2.erode(img,kernel,iterations = 2)
	dilation = cv2.dilate(erosion,kernel,iterations = 3)
	closing = cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel)

	return closing

def findMaxContour(img):
	img2, contour,hier = cv2.findContours(img,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
	areas = [cv2.contourArea(c) for c in contour]
	max_index = np.argmax(areas)
	cnt=contour[max_index]

	M = cv2.moments(cnt)
	cx = int(M['m10']/M['m00'])
	cy = int(M['m01']/M['m00'])
	return cx, cy, cnt

img = cv2.imread('sil10017.pbm',0)

denoised = denoiseSilhouette(img)

cx, cy, cnt = findMaxContour(denoised)

#Find distance betweem center to all contour poiints
print len(cnt)
dists = np.zeros(len(cnt))

drawing_cnt = np.zeros(img.shape)
drawing_cnt[cy,cx] = 255

drawing_cnt[cy+1,cx] = 255
drawing_cnt[cy+1,cx+1] = 255
drawing_cnt[cy+1,cx-1] = 255

drawing_cnt[cy-1,cx] = 255
drawing_cnt[cy-1,cx+1] = 255
drawing_cnt[cy-1,cx-1] = 255
for i in xrange(len(cnt)):
	x = cnt[i][0][0]
	y = cnt[i][0][1]
	dists[i] = np.sqrt(((x-cx)**2)+((y-cy)**2))

	drawing_cnt[y,x] = 255
	cv2.imshow('Temp',drawing_cnt)
	print "Pixel distance to centroid is: ",dists[i]
	cv2.waitKey(10)

cv2.waitKey(0)