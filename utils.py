# -*- coding: utf-8 -*-
import math


def euclidean_dist(p1, p2):
    return math.sqrt((p2[0] - p1[0])*(p2[0] - p1[0]) + (p2[1] - p1[1])*(p2[1] - p1[1]))