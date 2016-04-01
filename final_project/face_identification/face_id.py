import cv2, os
import numpy as np
from sklearn.lda import LDA
from sklearn.neighbors import KNeighborsClassifier

datadir = 'data'
X = np.zeros((1,256*256))

n = 0
y = []
for subdir,_,_ in os.walk(datadir):
    if(subdir==datadir):
        continue

    n += 1
    print subdir
    for subdirs,dirs,imgs in os.walk(subdir):
        for img_name in imgs:
            img = cv2.imread(subdir+"/"+img_name)
            img_resize = cv2.resize(img,(256,256))
            gray = cv2.cvtColor(img_resize, cv2.COLOR_BGR2GRAY)

            X = np.concatenate((X,gray.flatten().reshape((1,256*256))),axis=0)
            y.append(n)

X = X[1:,:]
y = np.array(y)
#Dimensionality reduction on the face data
clf = LDA()
clf.fit(X,y)

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(clf.transform(X),y)

import cv2
faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

#Capture video from webcam
video_capture = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    ret, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5
    )

    # Draw a rectangle around the faces
    #predictions = []
    #for (x, y, w, h) in faces:
    #    cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        #test_face = gray[x:x+w,y:y+h]
        #test_face_resize = cv2.resize(test_face,(256,256))
        #prediction = (knn.predict(clf.transform(test_face_resize.reshape(1,256*256))))

        #if prediction == 1:
        #    cv2.putText(frame, "MARKUS",(x,y), cv2.FONT_HERSHEY_SIMPLEX, 2, 155, 10)

    # Display the resulting frame
    cv2.imshow('Video', frame)

    print "getyting here"
    if cv2.waitKey(0):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
