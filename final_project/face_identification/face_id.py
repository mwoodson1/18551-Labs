import cv2, os
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.decomposition import PCA

datadir = 'data'
X = np.zeros((1,128*128))

n = 0
y = []
for subdir,_,_ in os.walk(datadir):
    if(subdir==datadir):
        continue

    n += 1
    for subdirs,dirs,imgs in os.walk(subdir):
        for img_name in imgs:
            img = cv2.imread(subdir+"/"+img_name)
            img_resize = cv2.resize(img,(128,128))
            gray = cv2.cvtColor(img_resize, cv2.COLOR_BGR2GRAY)

            X = np.concatenate((X,gray.reshape((1,128*128))),axis=0)
            y.append(n)

X = X[1:,:]
#Dimensionality reduction on the face data
clf = PCA(n_components=80)
clf.fit(X)

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(clf.transform(X),y)

#Below code simply reads in camera feed and performs face recognition
#and identification.

faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

#Capture video from webcam
video_capture = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    ret, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(gray,scaleFactor=1.3,minNeighbors=5)

    # Draw a rectangle around the faces
    predictions = []
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        test_face = cv2.resize(gray[x:x+w,y:y+h],(128,128))
        prediction = (knn.predict(clf.transform(test_face.reshape(1,128*128))))

        if prediction == 1:
            cv2.putText(frame, "Amy",(x,y), cv2.FONT_HERSHEY_SIMPLEX, 2, 155, 10)
        elif prediction == 2:
            cv2.putText(frame, "Markus",(x,y), cv2.FONT_HERSHEY_SIMPLEX, 2, 155, 10)
        else:
            cv2.putText(frame, "Sally",(x,y), cv2.FONT_HERSHEY_SIMPLEX, 2, 155, 10)

    # Display the resulting frame
    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
