import time
import network
import urequests as requests
from localsettings import LocalSettings
import json
import socket

class PicoNetwork:
    def __init__(self):
        self.connected = None
        ssid = LocalSettings.SSID
        password = LocalSettings.Password

        wlan = network.WLAN(network.STA_IF)
        wlan.active(True)
        wlan.connect(ssid, password)

        # Wait for connect or fail
        max_wait = 10
        while max_wait > 0:
            if wlan.status() < 0 or wlan.status() >= 3:
                break
            max_wait -= 1
            print('waiting for connection...')
            time.sleep(1)

        # Handle connection error
        if wlan.status() != 3:
            print('network connection failed')
            self.connected = False
        else:
            print('The internet is connected')
            status = wlan.ifconfig()
            print( 'ip = ' + status[0] )
            self.connected = True

    def get(self, url):
        try:
            response = requests.get(url)
            return response.text
        except:
            print('Get url failed:', url)

    def put(self, url, headers, data):
        jsonObj = json.dumps(data)
        try:
            response = requests.put(url, data=jsonObj, headers=headers)
        except:
            response = requests.put(url, data=jsonObj, headers=headers)
        status_code = response.status_code
        response.close()
        if (status_code != 200):
            print('put response', status_code)
        return status_code

    def put2(self, url, headers, data):
        try:
            response = requests.put(url, data=data, headers=headers)
        except:
            response = requests.put(url, data=data, headers=headers)
        status_code = response.status_code
        response.close()
        if (status_code != 200):
            print('put2 response', status_code)
        return status_code

    def open_socket(self):
        # Open socket
        addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
        s = socket.socket()
        s.bind(addr)
        s.listen(1)
        print('listening on', addr)
        return s

    def accept(self, s):
        return s.accept()

    def recv(self, cl):
        request = cl.recv(1024)
        request_string = ''.join([chr(int(x)) for x in request])
        return request_string
