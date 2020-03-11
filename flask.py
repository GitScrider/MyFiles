from flask import Flask

app = Flask(__name__)

@app.route("/")
def index():
    return "Test" , 200

if __name == "__main__" :
    app.run()
