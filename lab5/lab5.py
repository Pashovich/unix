from flask import Flask
import os

app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():
    return "Куда мы без UNIX?"


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)