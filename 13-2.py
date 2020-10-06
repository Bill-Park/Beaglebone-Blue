from flask import Flask
from flask import render_template
from flask import jsonify
import random

app = Flask(__name__)

@app.route('/')
def hello_world() :
    return 'Hello World!'
    
@app.route("/page")
def page() :
    return render_template("var.html", value = "value from flask")
    
@app.route("/button")
def button() :
    return jsonify(value = random.random())
    
if __name__ == "__main__" :
    app.run(host = "0.0.0.0")