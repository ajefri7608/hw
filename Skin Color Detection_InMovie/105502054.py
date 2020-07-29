import numpy as np
import cv2

cap = cv2.VideoCapture("Lab4.mp4")
while(cap.isOpened()):
    ret, frame = cap.read()
    if frame is None:
        break

    #frame=cv2.GaussianBlur(frame,(5,5) ,2)
    frame1=cv2.cvtColor(frame, cv2.COLOR_BGR2YCR_CB)
    

    
    Y,Cr,Cb = cv2.split(frame1)
    mask=((Cr>=133)&(Cr<=177))&((Cb>=98)&(Cb<=122))

    mask=mask.astype (np.uint8)
    mask=cv2.erode(mask,(5,5))
    mask=cv2.dilate(mask,(5,5))
    #print(mask)
    contours,_=cv2.findContours(mask,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    #print(contours)
    mask=mask.astype (np.bool)
    frame[~mask]=(0,0,0)
    cv2.drawContours(frame, contours, -1, (0,255,0), 1)
    cv2.imshow("frame3", frame)
    #frame[mask]=False
    #cv2.imshow("frame1", frame)
    #mask=mask.astype (np.uint8)

    
    
    #cv2.imshow("frame1", frame)
    #frame[mask]=0
    
    #cv2.imshow("frame3", frame1)
    
    #kernel = np.ones((5,5),np.uint8)
    #frame=cv2.erode( mask , kernel)
    

    
    
    
    """
    mask=(frame>=98)|(frame<=122)

    kernel = np.ones((5,5),np.uint8)
    mask=cv2.erode( frame , (3,3))
    mask=cv2.dilate( mask , (3,3))

    

    


    cv2.imshow("frame1", Y)
    """
   
 
    if cv2.waitKey(0) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()