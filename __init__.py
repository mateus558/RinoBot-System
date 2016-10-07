# -*- coding: utf-8 -*-
import sys
import os
from vision import Vision


eye = Vision()


def header():
    print "*----------------------------------------------------------* "
    print "*                      RinoBot Vision                      * "
    print "*----------------------------------------------------------* "
    print


def set_color_ranges():
    header()
    while True:
        print "[1] Set ball HSV range"
        print "[2] Set T1R1 HSV range"
        print "[3] Set T1R2 HSV range"
        print "[4] Set T1R3 HSV range"
        print "[5] Set Team 1 HSV range"
        print "[6] Set Team 2 HSV range"
        print "[0] Back"
        o = int(raw_input("> "))
        color_range_opt(o)()


def set_parameters():
    header()
    while True:
        print "[1] Define color ranges"
        print "[2] Set map points"
        print "[3] Set defense area points"
        print "[4] Set attack area points"
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
        print "[2] Set robots channels"
        print "[3] Set robots roles"
        print "[4] Show robots"
        print "[5] Read parameters"
        print "[6] Write parameters"
        #print "[5] Let's play soccer!"
        print "[0] Exit"
        o = int(raw_input("> "))
        switch(o)()


def set_roles():
    clear()
    ID = raw_input("Enter the ID of the robot to set the role: ")
    role = raw_input("Enter the role: ")
    eye.set_role(ID, role)

    print
    y = raw_input("Wish to set another robot?[y|n]: ")
    if y == 'y':
        set_roles()
    else:
        __init__()


def set_channels():
    clear()
    ID = raw_input("Enter the ID of the robot to set the channel: ")
    c = int(raw_input("Enter the channel: "))
    eye.set_channel(ID, c)

    print
    y = raw_input("Wish to set another robot?[y|n]: ")
    if y == 'y':
        set_channels()
    else:
        __init__()


def show_robots():
    clear()
    robots = eye.get_robots()

    for robot in robots:
        print "Robot " + robot.get_ID()
        print "Role: " + robot.get_role()
        #print "Channel: " + robot.get_channel()
        print

    raw_input("Press any key to continue...")
    __init__()

color_range = {0: set_parameters, 1: None}
opt = {0: sys.exit, 1: set_parameters, 2: set_channels, 3: set_roles, 4: show_robots}
param = {0: __init__, 1: set_color_ranges}
clear = lambda: os.system('clear')

__init__()