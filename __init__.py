# -*- coding: utf-8 -*-
import sys
import os
from vision import Vision


def header():
    print "*----------------------------------------------------------* "
    print "*                      RinoBot Vision                      * "
    print "*----------------------------------------------------------* "
    print


def set_color_ranges():
    header()
    while True:
        print "[1] Set ball HSV range"
        print "[0] Back"
        o = int(raw_input("> "))
        color_range_opt(o)()


def set_parameters():
    header()
    while True:
        print "[1] Define color ranges"
        print "[0] Back"
        o = int(raw_input("> "))
        param_opt(o)()


def color_range_opt(x):
    clear()
    return color_range.get(x, 0)


def param_opt(x):
    clear()
    return param.get(x, 0)


def switch(x):
    clear()
    return opt.get(x, 9)


def __init__():
    clear()
    header()
    while True:
        print "[1] Set parameters"
        print "[0] Exit"
        o = int(raw_input("> "))
        switch(o)()

color_range = {0: set_parameters, 1: None}
opt = {0: sys.exit, 1: set_parameters}
param = {0: __init__, 1: set_color_ranges}
clear = lambda: os.system('clear')

__init__()