import numpy as np
import cv2
from PyQt4.QtGui import *
from PyQt4.QtCore import *


class Vision:

    def __init__(self, cam_id=-1):
        self.raw_frame = None
        self.vision_frame = None
        self.cam_id = cam_id
        self.cam = None
        self.writer = None

    def open_camera(self, cid=-1):
        if cid == -1:
            if self.cam_id == -1:
                print "Set a camera id"
                return False
            self.cam = cv2.VideoCapture(self.cam_id)
        else:
            self.cam = cv2.VideoCapture(cid)

        if not self.cam.isOpened():  # lint:ok
            print "Error: Camera busy, can't be opened"

        return self.cam.isOpened()

    def get_new_frame(self):
        okay = False

        if self.cam.isOpened():
            okay, self.raw_frame = self.cam.read()
            self.vision_frame = self.raw_frame.copy()
        else:
            print "Open the camera first"

        return okay

    def adjust_gamma(self, gamma=1.0):
        # build a lookup table mapping the pixel values [0, 255] to
        # their adjusted gamma values
        invGamma = 1.0 / gamma
        table = np.array([((i / 255.0) ** invGamma) * 255
        # apply gamma correction using the lookup table
        for i in np.arange(0, 256)]).astype("uint8")

        self.vision_frame = cv2.LUT(self.vision_frame, table)

    def to_gray(self, img):
        grayImg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        return grayImg

    def key_pressed(self, key=0):
        if key == 27:
            cv2.destroyAllWindows()
            self.cam.release()

    def show(self, name, img):
        img_tag = name
        cv2.imshow(img_tag, img)
        key = cv2.waitKey(2) & 0xFF
        self.key_pressed(key)

    def show_raw_vision(self):
        cv2.imshow("Raw Vision", self.raw_frame)
        key = cv2.waitKey(2) & 0xFF
        self.key_pressed(key)

    def show_processed_vision(self):
        cv2.imshow("Processed Vision", self.vision_frame)
        key = cv2.waitKey(2) & 0xFF
        self.key_pressed(key)

    def init_record(self, name='output.mp4', encoder='mp4v'):
        w = self.cam.get(cv2.CAP_PROP_FRAME_WIDTH)
        h = self.cam.get(cv2.CAP_PROP_FRAME_HEIGHT)
        fourcc = cv2.VideoWriter_fourcc(*encoder)
        self.writer = cv2.VideoWriter(name, fourcc, 15.0, (int(w), int(h)))

    def record(self, frame=None):
        if not frame:
            self.writer.write(self.raw_frame)
            return
        self.writer.write(frame)

    def save_image(self, name='out.png', img=None):
        if img.any():
            cv2.imwrite(name, self.raw_frame)
            return
        else:
            cv2.imwrite(name, img)
            return

    def get_vision_frame(self):
        return self.vision_frame.copy()

    def get_raw_frame(self):
        return self.raw_frame.copy()

    def __del__(self):
        cv2.destroyAllWindows()
        self.cam.release()
