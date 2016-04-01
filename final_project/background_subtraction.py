import numpy as np
import cv2

cap = cv2.VideoCapture('data/768x576.avi')
cv2.namedWindow("Original",1)
bgs = cv2.createBackgroundSubtractorMOG2(detectShadows=False,varThreshold=28)

while(1):
    img = cap.read()[1]
    if img is not None:
        img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        #Compute the sillouhete
        fgmask = bgs.apply(img)
        foreground = cv2.bitwise_and(img,img,mask=fgmask)

        #Compute the contour or edges around the
        im2, contours, hierarchy = cv2.findContours(fgmask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
        cv2.imshow("Original",foreground)

        k = cv2.waitKey(30) & 0xff
        if k == 27:
            break

cap.release()
cv2.destroyAllWindows()
