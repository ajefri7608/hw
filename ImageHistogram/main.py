import numpy as np
import cv2
from pprint import pprint
import matplotlib.pyplot as plt

image=cv2.imread('photo.jpg',cv2.IMREAD_GRAYSCALE)
x=[0]*256
y=[0]*256


#print(x)


#print(image)
#print("AAA")
t=image.flatten().tolist()
#print(type(t))
for i in range(len(x)):
    y[i]=i
    for j in range(len(t)):
        if t[j]==i:
            x[i]+=1
#print(x)
            
            
plt.bar(y,x)
#plt.hist(image.ravel(), 256, [0, 256])


#plt.bar(image)

#np.histogram(image,bins) 

#hist,bins = np.histogram(image,bins)  
#print hist 
#print bins
#plt.hist(image, bins) 
#plt.title("histogram") 
#plt.show()
#cv2.imshow("Output1",image)
plt.savefig("image")
plt.show()
cv2.waitKey(0)

