from flask import Flask, request, render_template
app = Flask(__name__)

analog_value = 0
# (variable) app: Flask
    
@app.route('/')
def index():
    return render_template('index1.html', value=analog_value)

@app.route('/store', methods=['GET'])
def store_value():
    global analog_value
    value = request.args.get('analog_value', type=int)
    analog_value = value
    return "Value stored succefully"

if __name__ == '__main__':
    app.run(host ='0.0.0.0', port=5000)