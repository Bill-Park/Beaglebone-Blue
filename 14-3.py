import cv2

cap = cv2.VideoCapture("/dev/video2")
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)

ret, frame = cap.read()
cv2.imwrite("test.jpg", frame)

cap.release()