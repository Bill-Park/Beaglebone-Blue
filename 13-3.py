import rcpy.button as rc_button
import time

while True :
    print(rc_button.mode.is_pressed(), rc_button.pause.is_pressed())
    time.sleep(0.5)
