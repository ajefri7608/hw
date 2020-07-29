import numpy as np
import cv2

img = cv2.imread("j.png", 0)
o_img = cv2.imread("opening_j.png", 0)
c_img = cv2.imread("closing_j.png", 0)
kernel = np.array([
    [0, 255, 0],
    [255, 255, 255],
    [0, 255, 0]
], dtype=np.uint8)
col = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])
row = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]])


def dilate_(img, kernel, iterations=1):
    my_img = img.copy()
    
    masked_img = np.pad(img, (1, 1), "constant")
    w_img=np.zeros(masked_img.shape,dtype=np.uint8)
    for iters in range(iterations):
        for i in range(1, masked_img.shape[0] - 1):
            for j in range(1, masked_img.shape[1] - 1):
                and_img=np.bitwise_and(kernel,masked_img[col+i,row+j])
                if((and_img==255).any()):
                    w_img[i,j]=255;
                

                
    return w_img


def erosion_(img, kernel, iterations=1):
    my_img = img.copy()
    masked_img = np.pad(img, (1, 1), "constant")
    w_img=np.zeros(masked_img.shape,dtype=np.uint8)
    for iters in range(iterations):
        for i in range(1, masked_img.shape[0] - 1):
            for j in range(1, masked_img.shape[1] - 1):
                and_img=np.bitwise_and(kernel,masked_img[col+i,row+j])
                if((and_img==kernel).all()):
                    w_img[i,j]=255;
    return w_img


def open_(o_img, kernel, iterations=2):
    open_img=o_img.copy()
    open_img=erosion_(img,kernel)

    open_img=dilate_(img,kernel)
    return open_img

def close_(c_img, kernel, iterations=2):
    open_img=c_img.copy()
    open_img=dilate_(open_img,kernel)
    open_img=dilate_(open_img,kernel)
    open_img=erosion_(open_img,kernel)
    open_img=erosion_(open_img,kernel)

    return open_img



dilation_output = dilate_(img, kernel, iterations=2)
erosion_output = erosion_(img, kernel, iterations=2)
opening_output = open_(o_img, kernel, iterations=2)
closing_output = close_(c_img, kernel, iterations=2)
##
cv2.imshow("my_answer_dilation", dilation_output)
cv2.imshow("my_answer_erosion", erosion_output)
cv2.imshow("my_answer_opening", opening_output)
cv2.imshow("my_answer_closing", closing_output)
##
cv2.imwrite("dilation.jpg", dilation_output)
cv2.imwrite("erosion.jpg", erosion_output)
cv2.imwrite("opening.jpg", opening_output)
cv2.imwrite("closing.jpg", closing_output)
cv2.waitKey(0)
cv2.destroyAllWindows()