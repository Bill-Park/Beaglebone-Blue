from flask import Flask
from flask import render_template
from flask import jsonify
import random
import rcpy.button as rc_button

from flask import request
import rcpy.led as rc_led

app = Flask(__name__)

@app.route('/')
def hello_world() :
    return 'Hello World!'
    
@app.route('/page')
def page() :
    return render_template("hi.html", value = "hello.py")

@app.route('/random')
def random_num() :
    return jsonify(random_value = random.random())
    
@app.route('/button')
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

if __name__ == "__main__" :
    app.run(host = "0.0.0.0")