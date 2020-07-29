# -*- coding: utf-8 -*-
"""
Created on Thu Oct  3 18:00:17 2019

@author: snmg
"""

import cv2
import numpy as np
import math
image=cv2.imread('detention_1.jpg',cv2.IMREAD_GRAYSCALE)









rows,cols =image.shape
c = 255/(np.max(np.log(1 + image)))
print(int(c*np.log(1+image[i][j])))
for i in range(0,rows):
   for j in range(0,cols/2):
       
        transfer_img1[i][j]=255-image[i][j]
        



for i in range(0,rows):
    for j in range(cols/2,cols):
        transfer_img1[i][j]=c*np.log(1+image[i][j])
        


cv2.imshow("Output1",transfer_img1)
cv2.waitKey(0)
cv2.destroyAllWindows()