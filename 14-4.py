from flask import Flask
from flask import render_template
from flask import jsonify
from flask import request
from flask import Response
import random
import rcpy.button as rc_button
import rcpy.led as rc_led
import cv2

app = Flask(__name__)

@app.route('/')
def hello_world() :
    return 'Hello World!'
    
@app.route("/page")
def page() :
    return render_template("var.html", value = "value from flask")
    
@app.route("/button")
def button() :
    return jsonify(
            btn1 = rc_button.mode.is_pressed(), 
            btn2 = rc_button.pause.is_pressed()
        )
    
@app.route("/led", methods=["POST"])
def led() :
    print(request.form['led'])
    led_num = request.form['led']
    if led_num == '1' :
        rc_led.red.toggle()
    elif led_num == '2' :
        rc_led.green.toggle()
    
    return led_num
    
def get_frame() :
    cap = cv2.VideoCapture("/dev/video2")
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
    while True :
        _, frame = cap.read()
        imgencode = cv2.imencode('.jpg', frame)[1]
        stringData = imgencode.tostring()
        yield (b'--frame\r\n'
            b'Content-Type: text/plain\r\n\r\n' + stringData + b'\r\n')
    
    cap.release()
    
@app.route('/frame')
def frame() :
    return Response(get_frame(),
        mimetype='multipart/x-mixed-replace; boundary=frame')


if __name__ == "__main__" :
    app.run(host = "0.0.0.0")