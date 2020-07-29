import cv2
global k
def detectAndDisplay(frame):
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frame_gray = cv2.equalizeHist(frame_gray)
    faces = face_cascade1.detectMultiScale(frame_gray)
    faces1 = face_cascade.detectMultiScale(frame_gray)
    cv2.imshow("Iron Cat Face Detection", frame)      
    print(b)
    if b==115:
        for (x, y, w, h) in faces:
            center = (x + w // 2, y + h // 2)
            frame = cv2.ellipse(frame, center, (w // 2, h // 2), 0, 0, 360, (255, 0, 255), 4)
        cv2.imshow("Iron Cat Face Detection", frame)
    if b==97:
        for (x, y, w, h) in faces1:
            center = (x + w // 2, y + h // 2)
            frame = cv2.ellipse(frame, center, (w // 2, h // 2), 0, 0, 360, (255, 0, 255), 4)
        cv2.imshow("Iron Cat Face Detection", frame)      
        
        
        
        
face_cascade = cv2.CascadeClassifier()
face_cascade1 =cv2.CascadeClassifier()
face_cascade1.load("data/lbpcascade_frontalcatface.xml")
if not face_cascade.load("data/lbpcascade_frontalface_improved.xml"):
    print("Error loading face cascade")
    exit(0)

cap = cv2.VideoCapture("Iron_Cat.mp4")
if not cap.isOpened:
    print("Error opening video capture")
    exit(0)
b=0
while True:


    ret, frame = cap.read()
    if frame is None:
        break
    detectAndDisplay(frame)
    k = cv2.waitKey(10) & 0xFF

    if k == ord('q'):
        break
    elif k == ord('a'):
        b=115;
    elif k == ord('s'):
        b=97;

cap.release()
cv2.destroyAllWindows()