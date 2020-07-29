import cv2
import numpy as np
from math import atan2, sqrt, pi
import math










## read image
grayImage = cv2.imread('olaf.jpg', cv2.IMREAD_GRAYSCALE)

## convert to binary image
ret,binaryImage=cv2.threshold(grayImage, 254, 255, cv2.THRESH_BINARY_INV)

## morphological
kernel = np.ones((3, 3), np.uint8)
opening = cv2.morphologyEx(binaryImage,cv2.MORPH_OPEN,kernel)
opening = cv2.morphologyEx(opening,cv2.MORPH_CLOSE,kernel)
color = cv2.cvtColor(opening, cv2.COLOR_GRAY2BGR)

## find and draw contours



(cnts, _) = cv2.findContours(opening.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#np.asarray(cnts, dtype=np.float32)
#print(type(cnts[0][0]))

#np.reshape(cnts, (2, 1080))
clone = color.copy()

cv2.drawContours(clone, cnts, -1, (0, 0, 255), 2)
cv2.drawContours(opening, cnts, -1, (0, 0, 255), 2)

centroid = clone.copy()

## PCA analysis


for i, c in enumerate(cnts):
    sz=len(c)
    data_pts = np.empty((sz, 2), dtype=np.float64)
    #print(data_pts)
    for i in range(data_pts.shape[0]):
        data_pts[i,0] = c[i,0,0]
        data_pts[i,1] = c[i,0,1]

    mean, eigvec,eigval = cv2.PCACompute2(data_pts, mean=None)
    cntr = (int(mean[0,0]), int(mean[0,1]))
    cv2.circle(clone, cntr, 3, (255, 0, 0), 2)
    

angle = atan2(eigvec[0,1], eigvec[0,0])  
angle=math.degrees(angle)
#print(angle)

a=2*(sqrt((eigval[0])))
print(cntr)
b=2*(sqrt(eigval[1]))




#print(b)
## center of the object, rotational angle, length of the major axis and minor axis


## draw center circle and ellipse
print(cntr)
#cntr=np.array(cntr).astype(int)
a=int(a)
b=int(b)
pca_ellipse= cv2.ellipse(clone, cntr, (a, b), angle,0,360,(0,255,0),5)
#angle, startAngle, endAngle, (0, 0, 255) , 5) 

## show images and write image
#cv2.imshow('Gray image', clone)
#cv2.imshow('Gray image', centroid)
#cv2.imshow('Binary image', binaryImage)

cv2.imshow('Morphological', opening)
cv2.imshow('PCA ellipse', clone)

#cv2.imwrite("PCA_ellipse.jpg", pca_ellipse)

cv2.waitKey(0)
cv2.destroyAllWindows()
