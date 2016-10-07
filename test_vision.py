import sys
from vision import Vision

eye = Vision()

if not eye.open_camera(0):
    sys.exit()
    print "done"

eye.init_record()
i = 0

while eye.get_new_frame():
    if i == 100000:
        break
    eye.show_processed_vision()
    eye.show()
    i += 1

print "done"