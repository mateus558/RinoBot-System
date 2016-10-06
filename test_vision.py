import sys
from vision import Vision

eye = Vision()

if not eye.open_camera(0):
    sys.exit()
    print "done"

#eye.init_record()
i = 0
while eye.get_new_frame():
    if i == 100:
        break
    eye.adjust_gamma(0.7)
    eye.to_hsv()
    #eye.to_gray()
    #eye.equalize_histogram()
    eye.gauss_blur()
    #frame = eye.get_raw_frame()
    #frame = eye.bilateral_blur(frame)
    eye.show_processed_vision()
    #eye.show("bilateral", frame)
    eye.show()
    #eye.save_image("teste.png", eye.get_raw_frame())
    #eye.record()
    i += 1
print "done"