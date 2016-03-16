'''
Training:
	For each training video:
		-construct a sequence of 1D-distance signals from person centroids

	Perform PCA on the sequence to reduce dimensionality

Test Pre-process:
	Given a training sequence
		-construct the sequence of 1D-distance signals
		-project onto eigenspace found in training process

Classification:
	Perform KNN, SVM, or any other classification algorithm we would like to try
'''
import numpy as np
from sklearn.decomposition import PCA
from sklearn import svm
from sklearn.neighbors import KNeighborsClassifier

def denoiseSilhouette(img):
	'''
	Denoise the image silhouettes to give a more rounded shape.
	'''
	kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(7,7))
	erosion = cv2.erode(img,kernel,iterations = 2)
	dilation = cv2.dilate(erosion,kernel,iterations = 3)
	closing = cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel)

	return closing

def findMaxContour(img):
	'''
	Find the largest contour in the image which should be the outline
	of the person.
	'''
	img2, contour,hier = cv2.findContours(img,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
	areas = [cv2.contourArea(c) for c in contour]
	cnt=contour[np.argmax(areas)]

	M = cv2.moments(cnt)
	cx = int(M['m10']/M['m00'])
	cy = int(M['m01']/M['m00'])
	return cx, cy, cnt

def toDistSeq(path):
	'''
	Given the path to a folder of images representing frames of a video,
	turn each frame into a 1D distance signal and concatenate into an
	image.
	'''
	pass

class GaitClassifier(object):
	def __init__(self):
		pass

	def train(self,X,y):
		pass

	def predict(self,X):
		pass