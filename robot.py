# -*- coding: utf-8 -*-
#import sys
#import serial
import numpy as np


class Robot:

    def __init__(self):
        self.centroid = np.array([-1, -1])
        self.channel = -1
        self.ID = None
        self.role = None
        self.pos_hist = np.array([])

    def get_centroid(self):
        return self.centroid

    def set_centroid(self, cent):
        self.centroid = cent

    def get_role(self):
        return self.role

    def set_role(self, role):
        self.role = role

    def get_channel(self):
        return self.channel

    def set_channel(self, channel):
        self.channel = channel

    def set_ID(self, ID):
        self.ID = ID

    def get_ID(self):
        return self.ID

    #def insert_pos_to_hist(self, pos):