from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit
import time
import threading

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

thread = None

temp = None
amps = None
volt = None



@app.route('/data', methods=['POST'])
def receive_temp():

    global temp, amps, volt
    # Receive data from the POST request
    
    data = request.get_json()
    print('Received data:', data)

    temp = data.get('temp')
    amps = data.get('Amps')
    volt = data.get('Volt')

    print(f"Temperature: {temp}, Amps: {amps}")

    return {'status': 'success'}, 200

@app.route('/')
def index():
    return render_template('layout.html')

def background_thread():
    while True:
        voltage = volt if volt is not None else 0
        temperature = temp if temp is not None else 0
        amperage = amps if amps is not None else 0
        socketio.emit('update_data', {
            'voltage': voltage,
            'temperature': temperature,
            'amperage': amperage
        })
        time.sleep(2)

@socketio.on('connect')
def handle_connect():
    global thread
    print('Client connected')
    if thread is None:
        thread = threading.Thread(target=background_thread)
        thread.daemon = True
        thread.start()

if __name__ == '__main__':
    socketio.run(app, debug=True, host='0.0.0.0', port=5000)
