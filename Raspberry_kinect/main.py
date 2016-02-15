import freenect
import cv2
import numpy as np

from slam import *




keep_running = True
print "Press esc for close window"

s = Slam()

while keep_running:
    depth, timestamp = freenect.sync_get_depth()

    """img = s.depth_to_image(depth)

    for i in range(0, 640):
        img[240, i] = 0
    
    cv2.imshow('Depth', img)"""

    current_world = np.zeros( (600, 800), dtype=np.uint8 )

    """ Convert from i, j, depth to x, z """
    for i in range(0, 640):
        current_depth = int(round((s.depth_table[depth[240, i]]/10)))

        if current_depth < 600 and current_depth > 0:
            pos_x = 400 + int(round((i-320)*((current_depth)-10)*0.0021))

            if pos_x < 800 and pos_x >= 0:
                current_world[599-current_depth, pos_x] = 125


    """ Detect lines """
    """lines = cv2.HoughLinesP(current_world, 1, np.pi/180, threshold = 30, minLineLength = 10, maxLineGap = 10)

    if lines != None:
        for x1, y1, x2, y2 in lines[0]:
            cv2.line(current_world, (x1, y1) , (x2, y2) , 255, 2)"""


    """ Detect corner (keypoint) """
    """fast = cv2.FastFeatureDetector()#cv2.FAST_FEATURE_DETECTOR_TYPE_9_16)
    kp = fast.detect(current_world, None)
    #print fast.getInt('type'), "\n"
    #test = cv2.drawKeypoints(current_world, kp, color=(255))
    for k in kp:
        x, y = k.pt
        cv2.circle(current_world, (int(x), int(y)), 2, 255)"""

    """ Detect corner with Harris """
    dst = cv2.cornerHarris(current_world,20,11,0.04)
    dst = cv2.dilate(dst,None)
    #current_world[dst>0.7*dst.max()]=255
    cv2.imshow('dst', dst/dst.max()*255)


    cv2.imshow('Current visuable world', current_world)

    if cv2.waitKey(10) == 27:
        keep_running = False
