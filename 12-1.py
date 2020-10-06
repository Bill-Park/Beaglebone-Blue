from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello_world() :
    return 'Hello World!'
    
# export FLASK_APP=hello.py

# python3 -m flask run --host=0.0.0.0
