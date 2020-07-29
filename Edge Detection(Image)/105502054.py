# -*- coding: utf-8 -*-
"""
Created on Thu Nov 21 19:27:52 2019

@author: snmg
"""

from scipy import signal
import cv2
import numpy as np
import time
from matplotlib import pyplot as plt
import matplotlib.image as mpimg
from PIL import Image


def sobelx_homemade(arr, ky):
    offset = 1
    sx = np.zeros(arr.shape)
    for y in range(offset, arr.shape[0] - offset):
        for x in range(offset, arr.shape[1] - offset):
            rstart, rend = y-offset, y+offset+1
            cstart, cend = x-offset, x+offset+1
            w = arr[rstart:rend, cstart:cend]
            Ix = ky * w
            sx[y, x] = Ix.sum()
    return sx


    
image1 = cv2.imread('lenna.png',cv2.IMREAD_GRAYSCALE)
image=image1
image=image.astype (np.uint8)
kx = np.array([
    [-1, 0, 1],
    [-2, 0, 2],
    [-1, 0, 1]
], dtype=np.float)

ky = np.array([
    [1, 2, 1], 
    [0, 0, 0], 
    [-1, -2, -1]
], dtype = np.float)

Gx = signal.convolve2d(image, kx, boundary='fill', mode='same')
Gy = signal.convolve2d(image, ky, boundary='fill', mode='same')

# calculate homemade sobel x gradient
Gx = sobelx_homemade(image, kx)
Gy = sobelx_homemade(image, ky)

Gy=np.abs(Gy)
Gy=Gy.astype(np.uint8)
cv2.imshow("imagey",Gy)


Gx=np.abs(Gx)
Gx=Gx.astype(np.uint8)
cv2.imshow("imagex",Gx)

cv2.imshow("image",image)


cv2.waitKey()
cv2.destroyAllWindows()

