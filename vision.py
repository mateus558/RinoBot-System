'''  ***********************************************************************
     *                            RinoBot - Vision                         *
     *                                                                     *
     * Pedro Henrique Teixeira <pedro.teixeira2011@engenharia.ufjf.br>     *
     * Engenharia Elétrica Robótica - UFJF                                 *
     * +55 (32) 99904 - 8695                                               *
     *                                                                     *
     * Mateus Coutinho Marim <mateus.marim@ice.ufjf.br>                    *
     * Ciência da Computação - UFJF                                        *
     * +55 (32) 99162 - 9402                                               *
     *                                                                     *
     ***********************************************************************'''
import numpy as np
import cv2
from robot import Robot
from PyQt4.QtGui import *
from PyQt4.QtCore import *


class Vision:

    def __init__(self, cam_id=-1):
        self.raw_frame = None
        self.vision_frame = None
        self.cam_id = cam_id
        self.cam = None
        self.writer = None
        self.robots = [Robot(), Robot(), Robot()]
        self.robots[0].set_ID("T1R1")
        self.robots[1].set_ID("T1R2")
        self.robots[2].set_ID("T1R3")
        self.default = np.array([[0, 0, 0], [0, 0, 0]])
        self.colors = {"Ball": self.default, "T1": self.default, "T1R1": self.default, "T1R2": self.default, "T1R3": self.default, "T2": self.default}

    def open_camera(self, cid=-1):
        if cid == -1:
            if self.cam_id == -1:
                print "Set a camera id"
                return False
            self.cam = cv2.VideoCapture(self.cam_id)
        else:
            self.cam = cv2.VideoCapture(cid)

        if not self.cam.isOpened():
            print "Error: Camera busy."

        return self.cam.isOpened()

    def set_role(self, ID, role):
        for robot in self.robots:
            if robot.get_ID() == ID:
                robot.set_role(role)
                return
        print "Channel not set: There's no robot with this ID"

    def set_channel(self, ID, channel):
        for robot in self.robots:
            if robot.get_ID() == ID:
                robot.set_channel(channel)
                return
        print "Channel not set: There's no robot with this ID"

    def set_color(self, item, HSVmin, HSVmax):
        self.color[item] = [HSVmin, HSVmax]

    def get_new_frame(self):
        okay = False

        if self.cam.isOpened():
            okay, self.raw_frame = self.cam.read()
            self.vision_frame = self.raw_frame.copy()
        else:
            print "Error: Camera not open."

        return okay

    def bilateral_blur(self, img=None, c1=9, c2=75, c3=75):
        if img is None:
            self.vision_frame = cv2.bilateralFilter(self.vision_frame, c1, c2, c3)
            return
        return cv2.bilateralFilter(img, c1, c2, c3)

    def gauss_blur(self, img=None, kernel=(3, 3)):
        if img is None:
            self.vision_frame = cv2.GaussianBlur(self.vision_frame, kernel, 0)
            return
        return cv2.GaussianBlur(img, kernel, 0)

    def equalize_histogram(self, frame=None):
        clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))

        if frame is None:
            self.vision_frame = clahe.apply(self.vision_frame)
        else:
            return clahe.apply(frame)

    def adjust_gamma(self, gamma=1.0, img=None):
        # build a lookup table mapping the pixel values [0, 255] to
        # their adjusted gamma values
        invGamma = 1.0 / gamma
        table = np.array([((i / 255.0) ** invGamma) * 255
        # apply gamma correction using the lookup table
        for i in np.arange(0, 256)]).astype("uint8")

        if img is None:
            self.vision_frame = cv2.LUT(self.vision_frame, table)
        else:
            return cv2.LUT(img, table)

    def to_gray(self, img=None):
        if img is None:
            self.vision_frame = cv2.cvtColor(self.vision_frame, cv2.COLOR_BGR2GRAY)
            return
        grayImg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        return grayImg

    def to_hsv(self, img=None):
        if img is None:
            self.vision_frame = cv2.cvtColor(self.vision_frame, cv2.COLOR_BGR2HSV)
            return
        hsvImg = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        return hsvImg

    def key_pressed(self, key=0):
        if key == 27:
            cv2.destroyAllWindows()
            self.cam.release()

    def show(self, name="Raw Vision", img=None):
        if img is None:
            cv2.imshow(name, self.raw_frame)
            key = cv2.waitKey(2) & 0xFF
            self.key_pressed(key)
        else:
            cv2.imshow(name, img)
            key = cv2.waitKey(2) & 0xFF
            self.key_pressed(key)

    def show_processed_vision(self):
        cv2.imshow("Processed Vision", self.vision_frame)
        key = cv2.waitKey(2) & 0xFF
        self.key_pressed(key)

    def get_robots(self):
        return self.robots

    def set_vision_frame(self, frame):
        self.vision_frame = frame

    def get_vision_frame(self):
        return self.vision_frame.copy()

    def get_raw_frame(self):
        return self.raw_frame.copy()

    def init_record(self, name='output.mp4', encoder='dm4v'):
        w = self.cam.get(cv2.CAP_PROP_FRAME_WIDTH)
        h = self.cam.get(cv2.CAP_PROP_FRAME_HEIGHT)
        fourcc = cv2.VideoWriter_fourcc(*encoder)
        self.writer = cv2.VideoWriter(name, fourcc, 15.0, (int(w), int(h)))

    def record(self, frame=None):
        if not self.writer:
            print "Error: Video writer not initiated."
        elif frame is None:
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

    def read_parameters(self, fname="parameters.pckl"):
        print "to implement"

    def write_parameters(self, fname="parameters.pckl"):
        print "to implement"

    def __del__(self):
        cv2.destroyAllWindows()
        self.cam.release()
