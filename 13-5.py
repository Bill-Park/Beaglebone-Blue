import rcpy.button as rc_button
import rcpy.led as rc_led
import time

while True :
    if rc_button.mode.is_pressed() :
        rc_led.red.on()
    else :
        rc_led.red.off()
        
    if rc_button.pause.is_pressed() :
        rc_led.green.on()
    else :
        rc_led.green.off()