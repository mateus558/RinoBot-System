# -*- coding: utf-8 -*-
import sys
from vision import Vision

eye = Vision()

if not eye.open_camera(0):
    sys.exit()
    print "done"

eye.init_record()

while eye.get_new_frame():
    eye.adjust_gamma(0.1)
    eye.show_processed_vision()
    eye.show("gray", eye.to_gray(eye.get_raw_frame()))
    eye.show_raw_vision()
    eye.save_image("teste.png", eye.get_raw_frame())
    eye.record()
print "done"

